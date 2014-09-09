// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRYPTO_CRC32_HPP
#define CRYPTO_CRC32_HPP

#include <cstdint>
#include <cstdlib>

namespace crypto {

class crc32 {
 public:
  typedef uint8_t digest_type[4];
  static const size_t block_size = 4;

  crc32();
  ~crc32();

  void update(const void *data, size_t data_len);
  void final(digest_type &digest);

 private:
  uint32_t crc_;
};

} // namespace crypto

#include "crypto/crc32.ipp"

#endif // CRYPTO_CRC32_HPP
