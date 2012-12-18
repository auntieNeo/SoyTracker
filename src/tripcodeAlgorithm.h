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

#ifndef TRIPCODE_ALGORITHM_H_
#define TRIPCODE_ALGORITHM_H_

#include "common.h"

/**
 * \page tripripper_architecture TripRipper Architecture
 *
 * \section tripcode_searching Tripcode Searching
 * \subsection 
 *
 * \section tripcode_algorithm Tripcode Algorithm
 * There are various different implementations of the tripcode algorithm,
 * depending on the version of the image board software used or the particular
 * image board site. Most popular sites include a seperate, secure tripcode
 * algorithm that uses a secret salt to prevent users from searching the
 * tripcode keyspace locally. However, nearly every imageboard uses the same
 * algorithm for their insecure tripcodes, the algorithm that originated from
 * Futaba Channel. This algorithm can be searched rather efficiently, and is
 * described here.
 *
 * First, the the password is extracted from the end of the E-mail field, past
 * the # symbol.
 *
 * The characters "H.." are appended to the password, such that it is at least 3
 * characters long. This step can be ignored when searching the keyspace, since
 * the password is ultimately truncated to 8 characters when it is fed into
 * crypt(3) anyway. This stems from the fact that crypt(3) is implemented with
 * DES, which only has a 56 bit keyspace, or (7 * 8) bits.
 *
 * Note that due to the tripcode's origin on Japanese imageboards, the 7-bit
 * Japanese encoding JIS X 0201 can also be used for tripcode passwords, which
 * includes ASCII and halfwidth katakana, among other things. How well this
 * works on modern image boards depends on whether or not their implementation
 * of the tripcode algorithm was implemented with this in mind.
 *
 * The salt is taken from the second two characters in the password.
 *
 * The password and salt are then fed to the standard Unix crypt(3) function.
 * The last 10 characters from the returned string constitute the tripcode.
 *
 * \subsection tripcode_performance Performance Considerations
 * The glib implementation of crypt(3) is very slow, but much faster
 * implementations of the algorithm can be used. OpenSSL has an optimal
 * implementation, and John the Ripper has several SIMD implementations for
 * different architectures. There are Intel AVX implementations floating around
 * as well. GPU processing is probably the most efficient method for consumer
 * hardware.
 *
 * \section implementer_guide Guide for Implementing Algorithm
 * TripRipper's architecture is designed to allow for different implementations
 * of the steps in this algorithm to 
 * the tripcode brute-force search algorithm to be swapped out independently of
 * other stages. This is useful for taking advantage of the 
 *
 * On the other hand, this architecture complicates some of the implementation
 * details that implementations face, particularly when communicating data.
 *
 * \subsection packed_key Packed Key Format
 *
 * \subsection packed_tripcode Packed Tripcode Format
 */

namespace TripRipper
{
  class KeyBlock;

  /**
   * The abstract TripcodeAlgorithm class describes 
   */
  class TripcodeAlgorithm
  {
    public:
      TripcodeAlgorithm();
      virtual ~TripcodeAlgorithm();

      /**
       * The outputAlignment property specifies how the output from a
       * TripcodeAlgorithm object is to be aligned. Implementing classes must
       * place the first byte of the output at an address evenly divisable by
       * the outputAlignment. Additionally, the last byte of the output must be
       * at an address directly before an address evenly divisable by the
       * outputAlignment. If the output must be padded to fulfill this last
       * requirement, implementors can simply duplicate any of the results in
       * the output, to avoid returning erroneous results.
       */
      size_t outputAlignment() const { return m_outputAlignment; }
      /**
       * Sets the outputAlignment property. See outputAlignment().
       */
      void setOutputAlignment(size_t alignment) { m_outputAlignment = alignment; }

      /**
       * The outputStride property specifies the number of bytes that occur
       * between 
       */
      size_t outputStride() const { return m_outputStride; }
      /**
       * Sets the outputStride property. See outputStride().
       */
      void setOutputStride(size_t stride) { m_outputStride = stride; }

      virtual size_t inputAlignment() const = 0;
      virtual size_t inputStride() const = 0;
      virtual bool inputPackHighBit() const = 0;

      virtual void computeTripcodes(const KeyBlock *keys, TripcodeContainer *results) = 0;

    private:
      size_t m_outputAlignment, m_outputStride;
  };
}

#endif 
