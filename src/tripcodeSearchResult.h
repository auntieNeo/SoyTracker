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

#ifndef TRIPCODE_SEARCH_RESULT_H_
#define TRIPCODE_SEARCH_RESULT_H_

#include <vector>
#include <utility>

namespace TripRipper
{
  /**
   * The TripcodeSearchResult class models results from a search for tripcodes.
   * That is, TripcodeSearchResult stores tripcodes that passed the matching
   * algorithm along with their corresponding passwords.
   *
   * TripcodeSearchResult objects are serializable for transmission from
   * TripcodeCrawler workers to the root process.
   *
   * TripcodeSearchResult objects can be merged together to form a single list
   * of results with merge().
   *
   * TripcodeSearchResult provides a verify() method for verifying the
   * tripcodes with a known-working tripcode algorithm.
   */
  class TripcodeSearchResult
  {
    public:
      TripcodeSearchResult();
      ~TripcodeSearchResult();

      void serialize(unsigned char *buffer, size_t size, bool &done);
      void deserialize(const unsigned char *buffer, size_t size, bool &done);

      void merge(const TripcodeSearchResult &source);

      bool verify();

    private:
      std::vector<std::pair<std::string, std::string>> m_tripcodes;
  };
}

#endif
