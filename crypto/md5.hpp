// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TURNOVER_MD5_HPP
#define TURNOVER_MD5_HPP

#include <cstdint>
#include <cstdlib>

namespace crypto {

class md5 {
 public:
  typedef uint8_t digest_type[16];

  md5();
  ~md5();

  void update(const void *data, size_t size);
  void final(digest_type &digest);

 private:
  typedef uint32_t MD5_u32plus;

  MD5_u32plus lo_, hi_;
  MD5_u32plus a_, b_, c_, d_;
  uint8_t buffer_[64];
  MD5_u32plus block_[16];

  const void *body(const void *data, size_t size);
};

} // namespace crypto

#include "crypto/md5.ipp"

#endif // TURNOVER_MD5_HPP
