#include "keyspacePoolFactory.h"
#include "keyspaceMapping.h"

namespace TripRipper
{
  KeyspacePoolFactory::KeyspacePoolFactory()
  {
  }

  KeyspacePoolFactory::~KeyspacePoolFactory()
  {
  }

  KeyspacePool *KeyspacePoolFactory::singleton()
  {
    static KeyspacePool instance;
    return &instance;
  }

  KeyspacePool *createKeyspacePool(const unsigned char *data, size_t size)
  {
    switch(static_cast<KeyspaceMapping::Type>(*data))
    {
      case Linear:
        break;
      default:
        exit(EXIT_FAILURE);
    }
  }
}
