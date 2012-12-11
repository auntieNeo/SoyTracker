#ifndef TRIPCODE_ALGORITHM_H_
#define TRIPCODE_ALGORITHM_H_

/**
 * \page tripcode_algorithm Tripcode Algorithm Description
 *
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
 * The glib implementation of crypt(3) is very slow, but much faster
 * implementations of the algorithm can be used. OpenSSL has an optimal
 * implementation, and John the Ripper has several SIMD implementations for
 * different architectures. There are Intel AVX implementations floating around
 * as well. GPU processing is probably the most efficient method for consumer
 * hardware.
 */

namespace TripRipper
{
  class TripcodeAlgorithm
  {
    public:
      TripcodeAlgorithm();
      virtual ~TripcodeAlgorithm();
  };
}

#endif 
