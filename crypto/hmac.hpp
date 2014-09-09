// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRYPTO_HMAC_HPP
#define CRYPTO_HMAC_HPP

#include <cstdint>
#include <cstdlib>

namespace crypto {

template<typename Digest>
class hmac {
 public:
  typedef typename Digest::digest_type digest_type;
  static const size_t block_size = Digest::block_size;

  hmac(const void *key, size_t key_len);
  ~hmac();

  void update(const void *data, size_t data_len);
  void final(digest_type &digest);

 private:
  Digest ctx_;
  uint8_t k_ipad_[block_size];
  uint8_t k_opad_[block_size];
};

} // namespace crypto

#include "crypto/hmac.ipp"

#endif // CRYPTO_HMAC_HPP
