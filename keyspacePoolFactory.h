#ifndef KEYSPACE_POOL_FACTORY_H_
#define KEYSPACE_POOL_FACTORY_H_

namespace TripRipper
{
  class KeyspacePool;

  /**
   * The KeyspacePoolFactory is responsible for constructing KeyspacePool
   * objects from a serial representation of the object. This is important for
   * allowing the root MPI rank to communicate keyspace pools to the
   * TripcodeCrawler object for each rank. Because there can be many different
   * types of keyspace mappings, the particular type of KeyspacePool needs to
   * be communicated in the serial representation. This is an implementation
   * detail shared by both the KeyspacePoolFactory class and the classes that
   * implement KeyspacePool.
   */
  class KeyspacePoolFactory
  {
    private:
      KeyspacePoolFactory();
      ~KeyspacePoolFactory();

    public:
      static KeyspacePoolFactory *singleton();

      KeyspacePool *createKeyspacePool(const unsigned char *data, size_t size);
  }
}

#endif
