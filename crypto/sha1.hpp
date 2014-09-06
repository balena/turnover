// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRYPTO_SHA1_HPP
#define CRYPTO_SHA1_HPP

#include <cstdint>
#include <cstdlib>

namespace crypto {

class sha1 {
 public:
  typedef uint8_t digest_type[20];

  sha1();
  ~sha1();

  void update(const void *data, size_t data_len);
  void final(digest_type &digest);

 private:
  uint32_t state_[5];
  uint32_t count_[2];
  uint8_t buffer_[64];

  void transform(const uint32_t data[16]);
};

} // namespace crypto

#include "crypto/sha1.ipp"

#endif // CRYPTO_SHA1_HPP
