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

#include "strategyFactory.h"
#include "linearKeyspace.h"
#include "openSSLTripcode.h"
#include "strcmpMatching.h"

namespace TripRipper
{
  KeyspaceMapping *createLinearKeyspace()
  {
    return new LinearKeyspace;
  }

  TripcodeAlgorithm *createOpenSSLTripcode()
  {
    return new OpenSSLTripcode;
  }

  MatchingAlgorithm *createStrcmpMatching()
  {
    return new StrcmpMatching;
  }

  StrategyFactory::StrategyFactory()
  {
    // populate m_keyspaceMappingCreators
    m_keyspaceMappingCreators.insert(std::pair<std::string, KeyspaceMapping*(*)()>("linear", createLinearKeyspace));

    // populate m_tripcodeAlgorithmCreators
    m_tripcodeAlgorithmCreators.insert(std::pair<std::string, TripcodeAlgorithm*(*)()>("openssl", createOpenSSLTripcode));

    // populate m_matchingAlgorithmCreators
    m_matchingAlgorithmCreators.insert(std::pair<std::string, MatchingAlgorithm*(*)()>("strcmp", createStrcmpMatching));
  }

  StrategyFactory::~StrategyFactory()
  {
  }

  StrategyFactory *StrategyFactory::singleton()
  {
    static StrategyFactory instance;
    return &instance;
  }

  KeyspaceMapping *StrategyFactory::createKeyspaceMapping(const std::string &type)
  {
    std::map<std::string, KeyspaceMapping *(*)()>::iterator i = m_keyspaceMappingCreators.find(type);
    assert(i != m_keyspaceMappingCreators.end()); // FIXME: Handle this error properly. This is part of the external interface.
    return ((*i).second)();
  }

  TripcodeAlgorithm *StrategyFactory::createTripcodeAlgorithm(const std::string &type)
  {
    std::map<std::string, TripcodeAlgorithm *(*)()>::iterator i = m_tripcodeAlgorithmCreators.find(type);
    assert(i != m_tripcodeAlgorithmCreators.end()); // FIXME: Handle this error properly. This is part of the external interface.
    return ((*i).second)();
  }

  MatchingAlgorithm *StrategyFactory::createMatchingAlgorithm(const std::string &type)
  {
    std::map<std::string, MatchingAlgorithm *(*)()>::iterator i = m_matchingAlgorithmCreators.find(type);
    assert(i != m_matchingAlgorithmCreators.end()); // FIXME: Handle this error properly. This is part of the external interface.
    return ((*i).second)();
  }
}
