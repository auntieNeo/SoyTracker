#ifndef OPENSSL_TRIPCODE_H_
#define OPENSSL_TRIPCODE_H_

namespace TripRipper
{
  class OpenSSLTripcode : public TripcodeAlgorithm
  {
    public:
      OpenSSLTripcode();
      ~OpenSSLTripcode();
  };
}

#endif
