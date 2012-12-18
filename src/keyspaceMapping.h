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

#ifndef KEYSPACE_MAPPING_H_
#define KEYSPACE_MAPPING_H_

#include "common.h"

namespace TripRipper
{
  class KeyspacePool;

  /**
   * The KeyspaceMapping class is an abstract class that defines a mapping
   * (hopefully a bijective one) from a set of KeyspacePool objects onto the
   * tripcode keyspace. Essentially this defines the order in which the keyspace
   * is searched, and how many keys are in each KeyspacePool object.
   *
   * Another benefit provided by this architecture is that KeyspaceMapping
   * objects can be serialized and stored so that searches can be suspended and
   * subsequently resumed at a later time.
   */
  class KeyspaceMapping
  {
    public:
      enum Type { LINEAR = 1 };

      KeyspaceMapping();
      virtual ~KeyspaceMapping();

      void setOutputAlignment(size_t alignment) { m_outputAlignment = alignment; }
      size_t outputAlignment() const { return m_outputAlignment; }
      void setOutputStride(size_t stride) { m_outputStride = stride; }
      size_t outputStride() const { return m_outputStride; }

      virtual uint64_t totalPools() = 0;
      virtual uint64_t poolsLeft() = 0;
      virtual size_t poolSize() = 0;
      virtual KeyspacePool *getNextPool() = 0;

      virtual void serialize(unsigned char *buffer, size_t size, bool &done) const = 0;
      virtual void deserialize(const unsigned char *buffer, size_t size, bool &done) = 0;

    private:
      size_t m_outputAlignment, m_outputStride;
  };

  /**
   * The KeyspacePool needs to be sent over the wire to each TripcodeCrawler,
   * so implementing classes need to be able to create a serialized
   * representation of their instances. These serialized representations need
   * to be readable by the KeyspacePoolFactory class.
   */
  class KeyspacePool
  {
    public:
      KeyspacePool(uint64_t identifier);
      virtual ~KeyspacePool();

      uint64_t identifier() const { return m_identifier; };

      virtual size_t blockSize() = 0;
      virtual size_t blockAlignment() = 0;
      virtual unsigned char *getNextBlock() = 0;

      virtual uint8_t *serialize(size_t *size) const = 0;
      virtual void deserialize(const uint8_t *buffer, size_t size) = 0;

    private:
      uint64_t m_identifier;
  };

  class KeyBlock
  {
    public:
      KeyBlock();
      virtual ~KeyBlock();
  };
}

#endif
