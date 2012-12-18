/*******************************************************************************
 * Copyright 2012 Jonathan Glines <auntieNeo@gmail.com>                        *
 *                                                                             *
 * Permission is hereby granted, free of charge, to any person obtaining a     *
 * copy of this software and associated documentation files (the "Software"),  *
 * to deal in the Software without restriction, including without limitation   *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
 * and/or sell copies of the Software, and to permit persons to whom the       *
 * Software is furnished to do so, subject to the following conditions:        *
 *                                                                             *
 * The above copyright notice and this permission notice shall be included in  *
 * all copies or substantial portions of the Software.                         *
 *                                                                             *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
 * DEALINGS IN THE SOFTWARE.                                                   *
 ******************************************************************************/

#include "tripcodeCrawler.h"
#include "common.h"
#include "strategyFactory.h"
#include "keyspacePoolFactory.h"
#include "keyspaceMapping.h"
#include "tripcodeAlgorithm.h"
#include "matchingAlgorithm.h"

#include <mpi.h>

namespace TripRipper
{
  /**
   * The TripcodeCrawler constructor takes as its arguments a number of strings
   * that identify the strategies to be used when searching for tripcodes. These
   * are the same strings that are used for the command line arguments.
   */
  TripcodeCrawler::TripcodeCrawler(const std::string &keyspaceStrategy, const std::string &tripcodeStrategy, const std::string &matchingStrategy) :
    m_keyspaceMapping(NULL),
    m_tripcodeAlgorithm(NULL),
    m_matchingAlgorithm(NULL)
 {
    m_matchingAlgorithm = StrategyFactory::singleton()->createMatchingAlgorithm(matchingStrategy);

    m_tripcodeAlgorithm = StrategyFactory::singleton()->createTripcodeAlgorithm(tripcodeStrategy);
    m_tripcodeAlgorithm->setOutputAlignment(m_matchingAlgorithm->inputAlignment());
    m_tripcodeAlgorithm->setOutputStride(m_matchingAlgorithm->inputStride());

    int worldRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
    if(worldRank == ROOT_RANK)
    {
      m_keyspaceMapping = StrategyFactory::singleton()->createKeyspaceMapping(keyspaceStrategy);
      m_keyspaceMapping->setOutputAlignment(m_tripcodeAlgorithm->inputAlignment());
      m_keyspaceMapping->setOutputStride(m_tripcodeAlgorithm->inputStride());
    }
  }

  TripcodeCrawler::~TripcodeCrawler()
  {
    delete m_matchingAlgorithm;
    delete m_tripcodeAlgorithm;
    delete m_keyspaceMapping;
  }

  /**
   * This method contains most of the MPI code that coordinates the efforts
   * among the crawlers. This method doesn't return until the root MPI process
   * recieves a SIGTERM signal.
   *
   * One of the crawlers is designated the root crawler based on its MPI rank.
   * The root crawler instantiates a KeyspaceMapping object to coordinate the
   * keyspace mapping among the crawlers. In reality the root crawler forks its
   * tripcode generating thread and continues to listen for KeyspacePool
   * requests in the main thread.
   *
   * When the root crawler recieves a SIGTERM signal, it signals all of the
   * crawlers to finish their current pools and optionally serialize the
   * KeyspaceMapping object to disk to allow for the search to be resumed in the
   * future.
   *
   * \fixme Catching the SIGTERM signal in a thread that makes MPI calls might
   * not be safe. See section 2.9.2 of the MPI specification.
   */
  void TripcodeCrawler::run()
  {
    int worldRank, worldSize;
    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

    if(worldRank == ROOT_RANK)
    {
      /// \todo Spawn a thread so the root process can compute tripcodes and
      /// coordinate the threads at the same time.

      while(true)
      {
        MPI_Status status;

        // blocking receive for requests for keyspace pools
        MPI_Recv(NULL, 0, MPI_INT, MPI_ANY_SOURCE, KEYSPACE_REQUEST, MPI_COMM_WORLD, &status);

        /// \todo Need to document the ownership of a lot of these buffers.
        // construct a KeyspacePool object suitable for serialization and
        // transmission
        assert(m_keyspaceMapping != NULL);
        KeyspacePool *keyspacePool = m_keyspaceMapping->getNextPool();
        size_t poolDataSize;
        uint8_t *poolData = keyspacePool->serialize(&poolDataSize);
        // blocking response to keyspace pool request with serialized
        // KeyspacePool object
        MPI_Send(poolData, static_cast<int>(poolDataSize), MPI_BYTE, status.MPI_SOURCE, KEYSPACE_RESPONSE, MPI_COMM_WORLD);
        delete keyspacePool;
        delete poolData;
      }
    }
    else
    {
      while(true)
      {
        MPI_Status status;

        // request a new keyspace pool
        MPI_Send(NULL, 0, MPI_INT, ROOT_RANK, KEYSPACE_REQUEST, MPI_COMM_WORLD);

        // recieve the serialized KeyspacePool object
        MPI_Probe(ROOT_RANK, KEYSPACE_RESPONSE, MPI_COMM_WORLD, &status);
        size_t poolDataSize;
        MPI_Get_count(&status, MPI_BYTE, reinterpret_cast<int*>(poolDataSize));
        uint8_t *poolData = new uint8_t[poolDataSize];
        MPI_Recv(poolData, static_cast<int>(poolDataSize), MPI_BYTE, ROOT_RANK, KEYSPACE_RESPONSE, MPI_COMM_WORLD, &status);
        KeyspacePool *keyspacePool = KeyspacePoolFactory::singleton()->createKeyspacePool(poolData, poolDataSize);
        delete poolData;  /// \todo We might want to explore the speed benefit
        /// of a custom memory allocater here and a few other places.

        TripcodeContainer tripcodes, matches;
        KeyspaceBlock *currentBlock;
        while((currentBlock = keyspacePool->getNextBlock()) != NULL)
        {
          m_tripcodeAlgorithm->computeTripcodes(currentBlock, &tripcodes);
          m_matchingAlgorithm->matchTripcodes(&tripcodes);
          matches.merge(&tripcodes);
        }

        // TODO: send TripcodeSearchResult to ROOT_RANK

        delete keyspacePool;

        // TODO: check for termination signal
      }
    }
  }

  /**
   * This method coordinates the three classes KeyspacePool, TripcodeAlgorithm,
   * and MatchingAlgorithm to perform the actual tripcode search.
   */
  void TripcodeCrawler::doSearch()
  {
  }
}
