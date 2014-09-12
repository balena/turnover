// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_CRYPTO_IMPL_HMAC_IPP
#define MESSAGE_DETAIL_CRYPTO_IMPL_HMAC_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <cstring>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {
namespace crypto {

// Functions to implement RFC-2104.
// Placed into the public domain.

// Encode a string using HMAC - see RFC-2104 for details.
template<typename Digest>
hmac<Digest>::hmac(const void *key, size_t key_len) {
  using namespace std; // For memset and memcpy.
  digest_type tk;
  int i;

  // if key is longer than block_size reset it to key=digest(key)
  if (key_len > block_size) {
    Digest ctx;

    ctx.update(key, key_len);
    ctx.final(tk);

    key = reinterpret_cast<const uint8_t*>(tk);
    key_len = sizeof(tk);
  }

  // the HMAC transform looks like:
  //
  // DIGEST(K XOR opad, DIGEST(K XOR ipad, text))
  //
  // where K is an n byte key
  // ipad is the byte 0x36 repeated block_size
  // opad is the byte 0x5c repeated block_size
  // and text is the data being protected
  //
  // start out by storing key in pads
  memset(k_ipad_, 0, sizeof(k_ipad_));
  memset(k_opad_, 0, sizeof(k_opad_));
  memcpy(k_ipad_, key, key_len);
  memcpy(k_opad_, key, key_len);

  // XOR key with ipad and opad values
  for (i = 0; i < block_size; i++) {
    k_ipad_[i] ^= 0x36;
    k_opad_[i] ^= 0x5c;
  }
                                         // init context for 1st pass
  ctx_.update(k_ipad_, block_size);      // start with inner pad
}

template<typename Digest>
inline void hmac<Digest>::update(const void *data, size_t data_len) {
  ctx_.update(data, data_len);           // then text of datagram
}

template<typename Digest>
inline void hmac<Digest>::final(typename Digest::digest_type &digest) {
  ctx_.final(digest);                    // finish up 1st pass

  // perform outer SHA1
  new (&ctx_) Digest();                  // init context for 2nd pass
  ctx_.update(k_opad_, sizeof(k_opad_)); // start with outer pad
  ctx_.update(digest, sizeof(digest));   // then results of 1st hash
  ctx_.final(digest);                    // finish up 2nd pass
}

} // namespace crypto
} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_DETAIL_CRYPTO_IMPL_HMAC_IPP

