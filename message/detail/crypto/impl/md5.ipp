// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_CRYPTO_IMPL_MD5_IPP
#define MESSAGE_DETAIL_CRYPTO_IMPL_MD5_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <cstring>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {
namespace crypto {

/*
 * This is an OpenSSL-compatible implementation of the RSA Data Security, Inc.
 * MD5 Message-Digest Algorithm (RFC 1321).
 *
 * Homepage:
 * http://openwall.info/wiki/people/solar/software/public-domain-source-code/md5
 *
 * Author:
 * Alexander Peslyak, better known as Solar Designer <solar at openwall.com>
 *
 * This software was written by Alexander Peslyak in 2001.  No copyright is
 * claimed, and the software is hereby placed in the public domain.
 * In case this attempt to disclaim copyright and place the software in the
 * public domain is deemed null and void, then the software is
 * Copyright (c) 2001 Alexander Peslyak and it is hereby released to the
 * general public under the following terms:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted.
 *
 * There's ABSOLUTELY NO WARRANTY, express or implied.
 *
 * (This is a heavily cut-down "BSD license".)
 *
 * This differs from Colin Plumb's older public domain implementation in that
 * no exactly 32-bit integer data type is required (any 32-bit or wider
 * unsigned integer data type will do), there's no compile-time endianness
 * configuration, and the function prototypes match OpenSSL's.  No code from
 * Colin Plumb's implementation has been reused; this comment merely compares
 * the properties of the two independent implementations.
 *
 * The primary goals of this implementation are portability and ease of use.
 * It is meant to be fast, but not as fast as possible.  Some known
 * optimizations are not included to reduce source code size and avoid
 * compile-time configuration.
 */

/*
 * The basic MD5 functions.
 *
 * F and G are optimized compared to their RFC 1321 definitions for
 * architectures that lack an AND-NOT instruction, just like in Colin Plumb's
 * implementation.
 */
#define F(x, y, z)     ((z) ^ ((x) & ((y) ^ (z))))
#define G(x, y, z)     ((y) ^ ((z) & ((x) ^ (y))))
#define H(x, y, z)     (((x) ^ (y)) ^ (z))
#define H2(x, y, z)    ((x) ^ ((y) ^ (z)))
#define I(x, y, z)     ((y) ^ ((x) | ~(z)))

/*
 * The MD5 transformation for all four rounds.
 */
#define STEP(f, a, b, c, d, x, t, s) \
  (a) += f((b), (c), (d)) + (x) + (t); \
  (a) = (((a) << (s)) | (((a) & 0xffffffff) >> (32 - (s)))); \
  (a) += (b);

/*
 * SET reads 4 input bytes in little-endian byte order and stores them
 * in a properly aligned word in host byte order.
 *
 * The check for little-endian architectures that tolerate unaligned
 * memory accesses is just an optimization.  Nothing will break if it
 * doesn't work.
 */
#if defined(__i386__) || defined(__x86_64__) || defined(__vax__)
#define SET(n) \
  (*(MD5_u32plus *)&ptr[(n) * 4])
#define GET(n) \
  SET(n)
#else
#define SET(n) \
  (block_[(n)] = \
  (MD5_u32plus)ptr[(n) * 4] | \
  ((MD5_u32plus)ptr[(n) * 4 + 1] << 8) | \
  ((MD5_u32plus)ptr[(n) * 4 + 2] << 16) | \
  ((MD5_u32plus)ptr[(n) * 4 + 3] << 24))
#define GET(n) \
  (block_[(n)])
#endif

/*
 * This processes one or more 64-byte data blocks, but does NOT update
 * the bit counters.  There are no alignment requirements.
 */
const void *md5::body(const void *data, size_t size) {
  const uint8_t *ptr;
  MD5_u32plus a, b, c, d;
  MD5_u32plus saved_a, saved_b, saved_c, saved_d;

  ptr = (const uint8_t *)data;

  a = a_;
  b = b_;
  c = c_;
  d = d_;

  do {
    saved_a = a;
    saved_b = b;
    saved_c = c;
    saved_d = d;

/* Round 1 */
    STEP(F, a, b, c, d, SET(0), 0xd76aa478, 7)
    STEP(F, d, a, b, c, SET(1), 0xe8c7b756, 12)
    STEP(F, c, d, a, b, SET(2), 0x242070db, 17)
    STEP(F, b, c, d, a, SET(3), 0xc1bdceee, 22)
    STEP(F, a, b, c, d, SET(4), 0xf57c0faf, 7)
    STEP(F, d, a, b, c, SET(5), 0x4787c62a, 12)
    STEP(F, c, d, a, b, SET(6), 0xa8304613, 17)
    STEP(F, b, c, d, a, SET(7), 0xfd469501, 22)
    STEP(F, a, b, c, d, SET(8), 0x698098d8, 7)
    STEP(F, d, a, b, c, SET(9), 0x8b44f7af, 12)
    STEP(F, c, d, a, b, SET(10), 0xffff5bb1, 17)
    STEP(F, b, c, d, a, SET(11), 0x895cd7be, 22)
    STEP(F, a, b, c, d, SET(12), 0x6b901122, 7)
    STEP(F, d, a, b, c, SET(13), 0xfd987193, 12)
    STEP(F, c, d, a, b, SET(14), 0xa679438e, 17)
    STEP(F, b, c, d, a, SET(15), 0x49b40821, 22)

/* Round 2 */
    STEP(G, a, b, c, d, GET(1), 0xf61e2562, 5)
    STEP(G, d, a, b, c, GET(6), 0xc040b340, 9)
    STEP(G, c, d, a, b, GET(11), 0x265e5a51, 14)
    STEP(G, b, c, d, a, GET(0), 0xe9b6c7aa, 20)
    STEP(G, a, b, c, d, GET(5), 0xd62f105d, 5)
    STEP(G, d, a, b, c, GET(10), 0x02441453, 9)
    STEP(G, c, d, a, b, GET(15), 0xd8a1e681, 14)
    STEP(G, b, c, d, a, GET(4), 0xe7d3fbc8, 20)
    STEP(G, a, b, c, d, GET(9), 0x21e1cde6, 5)
    STEP(G, d, a, b, c, GET(14), 0xc33707d6, 9)
    STEP(G, c, d, a, b, GET(3), 0xf4d50d87, 14)
    STEP(G, b, c, d, a, GET(8), 0x455a14ed, 20)
    STEP(G, a, b, c, d, GET(13), 0xa9e3e905, 5)
    STEP(G, d, a, b, c, GET(2), 0xfcefa3f8, 9)
    STEP(G, c, d, a, b, GET(7), 0x676f02d9, 14)
    STEP(G, b, c, d, a, GET(12), 0x8d2a4c8a, 20)

/* Round 3 */
    STEP(H, a, b, c, d, GET(5), 0xfffa3942, 4)
    STEP(H2, d, a, b, c, GET(8), 0x8771f681, 11)
    STEP(H, c, d, a, b, GET(11), 0x6d9d6122, 16)
    STEP(H2, b, c, d, a, GET(14), 0xfde5380c, 23)
    STEP(H, a, b, c, d, GET(1), 0xa4beea44, 4)
    STEP(H2, d, a, b, c, GET(4), 0x4bdecfa9, 11)
    STEP(H, c, d, a, b, GET(7), 0xf6bb4b60, 16)
    STEP(H2, b, c, d, a, GET(10), 0xbebfbc70, 23)
    STEP(H, a, b, c, d, GET(13), 0x289b7ec6, 4)
    STEP(H2, d, a, b, c, GET(0), 0xeaa127fa, 11)
    STEP(H, c, d, a, b, GET(3), 0xd4ef3085, 16)
    STEP(H2, b, c, d, a, GET(6), 0x04881d05, 23)
    STEP(H, a, b, c, d, GET(9), 0xd9d4d039, 4)
    STEP(H2, d, a, b, c, GET(12), 0xe6db99e5, 11)
    STEP(H, c, d, a, b, GET(15), 0x1fa27cf8, 16)
    STEP(H2, b, c, d, a, GET(2), 0xc4ac5665, 23)

/* Round 4 */
    STEP(I, a, b, c, d, GET(0), 0xf4292244, 6)
    STEP(I, d, a, b, c, GET(7), 0x432aff97, 10)
    STEP(I, c, d, a, b, GET(14), 0xab9423a7, 15)
    STEP(I, b, c, d, a, GET(5), 0xfc93a039, 21)
    STEP(I, a, b, c, d, GET(12), 0x655b59c3, 6)
    STEP(I, d, a, b, c, GET(3), 0x8f0ccc92, 10)
    STEP(I, c, d, a, b, GET(10), 0xffeff47d, 15)
    STEP(I, b, c, d, a, GET(1), 0x85845dd1, 21)
    STEP(I, a, b, c, d, GET(8), 0x6fa87e4f, 6)
    STEP(I, d, a, b, c, GET(15), 0xfe2ce6e0, 10)
    STEP(I, c, d, a, b, GET(6), 0xa3014314, 15)
    STEP(I, b, c, d, a, GET(13), 0x4e0811a1, 21)
    STEP(I, a, b, c, d, GET(4), 0xf7537e82, 6)
    STEP(I, d, a, b, c, GET(11), 0xbd3af235, 10)
    STEP(I, c, d, a, b, GET(2), 0x2ad7d2bb, 15)
    STEP(I, b, c, d, a, GET(9), 0xeb86d391, 21)

    a += saved_a;
    b += saved_b;
    c += saved_c;
    d += saved_d;

    ptr += 64;
  } while (size -= 64);

  a_ = a;
  b_ = b;
  c_ = c;
  d_ = d;

  return ptr;
}

#undef F
#undef G
#undef H
#undef H2
#undef I
#undef STEP
#undef SET
#undef GET

md5::md5() {
  a_ = 0x67452301;
  b_ = 0xefcdab89;
  c_ = 0x98badcfe;
  d_ = 0x10325476;

  lo_ = 0;
  hi_ = 0;
}

void md5::update(const void *data, size_t size) {
  using namespace std; // For memcpy.
  MD5_u32plus saved_lo;
  size_t used, available;

  saved_lo = lo_;
  if ((lo_ = (saved_lo + size) & 0x1fffffff) < saved_lo)
    hi_++;
  hi_ += size >> 29;

  used = saved_lo & 0x3f;

  if (used) {
    available = 64 - used;

    if (size < available) {
      memcpy(&buffer_[used], data, size);
      return;
    }

    memcpy(&buffer_[used], data, available);
    data = (const uint8_t *)data + available;
    size -= available;
    body(buffer_, 64);
  }

  if (size >= 64) {
    data = body(data, size & ~(uint32_t)0x3f);
    size &= 0x3f;
  }

  memcpy(buffer_, data, size);
}

md5::bytes_type md5::to_bytes() {
  using namespace std; // For memset.
  size_t used, available;

  used = lo_ & 0x3f;

  buffer_[used++] = 0x80;

  available = 64 - used;

  if (available < 8) {
    memset(&buffer_[used], 0, available);
    body(buffer_, 64);
    used = 0;
    available = 64;
  }

  memset(&buffer_[used], 0, available - 8);

  lo_ <<= 3;
  buffer_[56] = (uint8_t)lo_;
  buffer_[57] = (uint8_t)(lo_ >> 8);
  buffer_[58] = (uint8_t)(lo_ >> 16);
  buffer_[59] = (uint8_t)(lo_ >> 24);
  buffer_[60] = (uint8_t)hi_;
  buffer_[61] = (uint8_t)(hi_ >> 8);
  buffer_[62] = (uint8_t)(hi_ >> 16);
  buffer_[63] = (uint8_t)(hi_ >> 24);

  body(buffer_, 64);

  bytes_type digest;
  digest[0] = (uint8_t)a_;
  digest[1] = (uint8_t)(a_ >> 8);
  digest[2] = (uint8_t)(a_ >> 16);
  digest[3] = (uint8_t)(a_ >> 24);
  digest[4] = (uint8_t)b_;
  digest[5] = (uint8_t)(b_ >> 8);
  digest[6] = (uint8_t)(b_ >> 16);
  digest[7] = (uint8_t)(b_ >> 24);
  digest[8] = (uint8_t)c_;
  digest[9] = (uint8_t)(c_ >> 8);
  digest[10] = (uint8_t)(c_ >> 16);
  digest[11] = (uint8_t)(c_ >> 24);
  digest[12] = (uint8_t)d_;
  digest[13] = (uint8_t)(d_ >> 8);
  digest[14] = (uint8_t)(d_ >> 16);
  digest[15] = (uint8_t)(d_ >> 24);
  return digest;
}

} // namespace crypto
} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_DETAIL_CRYPTO_IMPL_MD5_IPP

