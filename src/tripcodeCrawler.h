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

#ifndef TRIPCODE_CRAWLER_H_
#define TRIPCODE_CRAWLER_H_

namespace TripRipper
{
  class TripcodeCrawler
  {
    public:
      TripcodeCrawler(TripcodeAlgorithm *tripcode, MatchingAlgorithm *matching, KeyspacePool* (*keyspaceCallback)());
      ~TripcodeCrawler();

      void run();
      void doSearch();

      void setKeyspaceMapping();
      KeyspaceMapping *keyspaceMapping() { return m_keyspaceMapping; }

      void setTripcodeAlgorithm();
      TripcodeAlgorithm *tripcodeAlgorithm() { return m_tripcodeAlgorithm; }

      void setMatchingAlgorithm();
      MatchingAlgorithm *matchingAlgorithm() { return m_matchingAlgorithm; }

    private:
      TripcodeAlgorithm *m_tripcodeAlgorithm;
      MatchingAlgorithm *m_matchingAlgorithm;

      KeyspacePool* (*m_keyspaceCallback)();
      KeyspacePool *m_currentPool;
  };
}

#endif
