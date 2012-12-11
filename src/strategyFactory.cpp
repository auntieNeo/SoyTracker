#include "strategyFactory.h"

namespace TripRipper
{
  StratgyFactory::StrategyFactory()
  {
  }

  StratgyFactory::~StrategyFactory()
  {
  }

  StrategyFactory *StrategyFactory::singleton()
  {
    static StrategyFactory instance;
    return &instance;
  }
}
