// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_CRYPTO_IMPL_SHA1_IPP
#define MESSAGE_DETAIL_CRYPTO_IMPL_SHA1_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <cstring>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {
namespace crypto {

// Implementation of SHA1 hash function.
// Original author:  Steve Reid <sreid@sea-to-sky.net>
// Contributions by: James H. Brown <jbrown@burgoyne.com>, Saul Kravitz
// <Saul.Kravitz@celera.com>, and Ralph Giles <giles@ghostscript.com>
// Modified by WaterJuice retaining Public Domain license.
//
// This is free and unencumbered software released into the public domain
// June 2013 waterjuice.org

#define rol(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))

// blk0() and blk() perform the initial expand.
// I got the idea of expanding during the round function from SSLeay
#ifdef WORDS_BIGENDIAN
#define blk0(i) W[i]
#else
#define blk0(i) (W[i] = (rol(W[i],24)&0xFF00FF00) \
    |(rol(W[i],8)&0x00FF00FF))
#endif
#define blk(i) (W[i&15] = rol(W[(i+13)&15]^W[(i+8)&15] \
    ^W[(i+2)&15]^W[i&15],1))

// (R0+R1), R2, R3, R4 are the different operations used in SHA1
#define R0(v,w,x,y,z,i) z+=((w&(x^y))^y)+blk0(i)+0x5A827999ul+rol(v,5);w=rol(w,30);
#define R1(v,w,x,y,z,i) z+=((w&(x^y))^y)+blk(i)+0x5A827999ul+rol(v,5);w=rol(w,30);
#define R2(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0x6ED9EBA1ul+rol(v,5);w=rol(w,30);
#define R3(v,w,x,y,z,i) z+=(((w|x)&y)|(w&x))+blk(i)+0x8F1BBCDCul+rol(v,5);w=rol(w,30);
#define R4(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0xCA62C1D6ul+rol(v,5);w=rol(w,30);

// Hash a single 512-bit block. This is the core of the algorithm.
void sha1::transform(const uint32_t data[16]) {
  uint32_t W[16];
  memcpy(W, data, sizeof(W));

  // Copy state[] to working vars
  uint32_t a = state_[0];
  uint32_t b = state_[1];
  uint32_t c = state_[2];
  uint32_t d = state_[3];
  uint32_t e = state_[4];

  // 4 rounds of 20 operations each. Loop unrolled.
  R0(a,b,c,d,e, 0); R0(e,a,b,c,d, 1); R0(d,e,a,b,c, 2); R0(c,d,e,a,b, 3);
  R0(b,c,d,e,a, 4); R0(a,b,c,d,e, 5); R0(e,a,b,c,d, 6); R0(d,e,a,b,c, 7);
  R0(c,d,e,a,b, 8); R0(b,c,d,e,a, 9); R0(a,b,c,d,e,10); R0(e,a,b,c,d,11);
  R0(d,e,a,b,c,12); R0(c,d,e,a,b,13); R0(b,c,d,e,a,14); R0(a,b,c,d,e,15);
  R1(e,a,b,c,d,16); R1(d,e,a,b,c,17); R1(c,d,e,a,b,18); R1(b,c,d,e,a,19);
  R2(a,b,c,d,e,20); R2(e,a,b,c,d,21); R2(d,e,a,b,c,22); R2(c,d,e,a,b,23);
  R2(b,c,d,e,a,24); R2(a,b,c,d,e,25); R2(e,a,b,c,d,26); R2(d,e,a,b,c,27);
  R2(c,d,e,a,b,28); R2(b,c,d,e,a,29); R2(a,b,c,d,e,30); R2(e,a,b,c,d,31);
  R2(d,e,a,b,c,32); R2(c,d,e,a,b,33); R2(b,c,d,e,a,34); R2(a,b,c,d,e,35);
  R2(e,a,b,c,d,36); R2(d,e,a,b,c,37); R2(c,d,e,a,b,38); R2(b,c,d,e,a,39);
  R3(a,b,c,d,e,40); R3(e,a,b,c,d,41); R3(d,e,a,b,c,42); R3(c,d,e,a,b,43);
  R3(b,c,d,e,a,44); R3(a,b,c,d,e,45); R3(e,a,b,c,d,46); R3(d,e,a,b,c,47);
  R3(c,d,e,a,b,48); R3(b,c,d,e,a,49); R3(a,b,c,d,e,50); R3(e,a,b,c,d,51);
  R3(d,e,a,b,c,52); R3(c,d,e,a,b,53); R3(b,c,d,e,a,54); R3(a,b,c,d,e,55);
  R3(e,a,b,c,d,56); R3(d,e,a,b,c,57); R3(c,d,e,a,b,58); R3(b,c,d,e,a,59);
  R4(a,b,c,d,e,60); R4(e,a,b,c,d,61); R4(d,e,a,b,c,62); R4(c,d,e,a,b,63);
  R4(b,c,d,e,a,64); R4(a,b,c,d,e,65); R4(e,a,b,c,d,66); R4(d,e,a,b,c,67);
  R4(c,d,e,a,b,68); R4(b,c,d,e,a,69); R4(a,b,c,d,e,70); R4(e,a,b,c,d,71);
  R4(d,e,a,b,c,72); R4(c,d,e,a,b,73); R4(b,c,d,e,a,74); R4(a,b,c,d,e,75);
  R4(e,a,b,c,d,76); R4(d,e,a,b,c,77); R4(c,d,e,a,b,78); R4(b,c,d,e,a,79);

  // Add the working vars back into state[]
  state_[0] += a;
  state_[1] += b;
  state_[2] += c;
  state_[3] += d;
  state_[4] += e;
}

#undef rol
#undef blk0
#undef blk
#undef R0
#undef R1
#undef R2
#undef R3
#undef R4

sha1::sha1() {
  // SHA1 initialization constants
  state_[0] = 0x67452301ul;
  state_[1] = 0xEFCDAB89ul;
  state_[2] = 0x98BADCFEul;
  state_[3] = 0x10325476ul;
  state_[4] = 0xC3D2E1F0ul;
  count_[0] = count_[1] = 0;
}

void sha1::update(const void *data, size_t len) {
  size_t i, j;
  const uint8_t *vec = reinterpret_cast<const uint8_t*>(data);

  j = (count_[0] >> 3) & 63;
  if ((count_[0] += len << 3) < (len << 3))
    count_[1]++;
  count_[1] += (len >> 29);
  if ((j + len) > 63) {
    memcpy(&buffer_[j], vec, (i = 64 - j));
    transform(reinterpret_cast<const uint32_t*>(buffer_));
    for (; i + 63 < len; i += 64)
      transform(reinterpret_cast<const uint32_t*>(&vec[i]));
    j = 0;
  } else
    i = 0;
  memcpy(&buffer_[j], &vec[i], len - i);
}

void sha1::final(digest_type &digest) {
  size_t i;
  uint8_t finalcount[8];

  for (i = 0; i < 8; i++) {
    finalcount[i] = (uint8_t) ((count_[(i >= 4 ? 0 : 1)]
                    >> ((3 - (i & 3)) * 8)) & 255); // Endian independent
  }
  update("\x80", 1);
  while ((count_[0] & 504) != 448)
    update("\0", 1);
  update(finalcount, 8); // Should cause a transform()
  for (i = 0; i < 20; i++) {
    digest[i] =
      (uint8_t)((state_[i >> 2] >> ((3 - (i & 3)) * 8)) & 255);
  }
}

} // namespace crypto
} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_DETAIL_CRYPTO_IMPL_SHA1_IPP

