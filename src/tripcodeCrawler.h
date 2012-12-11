#ifndef TRIPCODE_CRAWLER_H_
#define TRIPCODE_CRAWLER_H_

namespace TripRipper
{
  class TripcodeCrawler
  {
    public:
      TripcodeCrawler();
      ~TripcodeCrawler();

    private:
      KeyspaceMapping *m_keyspaceMapping;
      TripcodeAlgorithm *m_tripcodeAlgorithm;
      MatchingAlgorithm *m_matchingAlgorithm;
  };
}

#endif
