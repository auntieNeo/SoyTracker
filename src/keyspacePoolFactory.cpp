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

#include "keyspacePoolFactory.h"
#include "keyspaceMapping.h"
#include "linearKeyspace.h"
#include "common.h"

#include <arpa/inet.h>

namespace TripRipper
{
  KeyspacePoolFactory::KeyspacePoolFactory()
  {
  }

  KeyspacePoolFactory::~KeyspacePoolFactory()
  {
  }

  KeyspacePoolFactory *KeyspacePoolFactory::singleton()
  {
    static KeyspacePoolFactory instance;
    return &instance;
  }

  KeyspacePool *KeyspacePoolFactory::createKeyspacePool(const uint8_t *data, size_t size)
  {
    uint32_t type = ntohl(*reinterpret_cast<const uint32_t*>(data));
    size_t dataIndex = sizeof(uint32_t);
    switch(static_cast<KeyspaceMapping::Type>(type))
    {
      case KeyspaceMapping::LINEAR:
        {
          LinearKeyspace();
        }
        break;
      default:
        exit(EXIT_FAILURE);
    }
  }
}
