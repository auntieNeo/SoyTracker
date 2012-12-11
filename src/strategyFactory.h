#ifndef STRATEGY_FACTORY_H_
#define STRATEGY_FACTORY_H_

namespace TripRipper
{
  /**
   * The StrategyFactory class is a singleton factory class that constructs the
   * various strategy classes that TripRipper uses. These strategies can be
   * changed based on user configuration parameters. The three strategy classes
   * that StrategyFactory constructs include KeyspaceMapping,
   * TripcodeAlgorithm, and MatchingAlgorithm.
   */
  class StrategyFactory
  {
    private:
      StrategyFactory();
      ~StrategyFactory();

    public:
      static StrategyFactory *singleton();

      KeyspaceMapping *createKeyspaceMapping(const string &type);
  };
}

#endif
