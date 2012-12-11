#ifndef KEYSPACE_MAPPING_H_
#define KEYSPACE_MAPPING_H_

namespace TripRipper
{

  class KeyspaceMapping
  {
    public:
      const enum Type { Linear };

      KeyspaceMapping();
      virtual ~KeyspaceMapping();

      KeyspacePool *getPool();
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
      KeyspacePool();
  };
}

#endif
