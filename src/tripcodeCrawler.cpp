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

namespace TripRipper
{
  TripcodeCrawler::TripcodeCrawler(TripcodeAlgorithm *tripcode, MatchingAlgorithm *matching, KeyspacePool *(*keyspaceCallback)()) :
    m_tripcodeAlgorithm(tripcode),
    m_matchingAlgorithm(matching),
    m_keyspaceCallback(keyspaceCallback),
    m_currentPool(NULL)
  {

  }

  /**
   * This method contains most of the MPI code that coordinates the efforts
   * among the crawlers. This method doesn't return until the root MPI process
   * recieves a SIGTERM signal.
   *
   * One of the crawlers is designated the root crawler based on its MPI rank.
   * The root crawler instantiates a KeyspaceMapping object to coordinate the
   * keyspace mapping among the crawlers.
   *
   * When the root crawler recieves a SIGTERM signal, it signals all of the
   * crawlers to finish their current pools and optionally serialize the
   * KeyspaceMapping object to disk to allow for the search to be resumed in the
   * future.
   */
  void TripcodeCrawler::run()
  {
    int worldRank, worldSize;
    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

    if(worldRank == 0)
    {
    }
    else
    {
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
