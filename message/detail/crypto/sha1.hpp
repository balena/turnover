// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_CRYPTO_SHA1_HPP
#define MESSAGE_DETAIL_CRYPTO_SHA1_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <cstdint>
#include <cstdlib>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {
namespace crypto {

class sha1 {
 public:
  typedef uint8_t digest_type[20];
  static const size_t block_size = 64;

  MESSAGE_DECL sha1();

  MESSAGE_DECL void update(const void *data, size_t data_len);
  MESSAGE_DECL void final(digest_type &digest);

 private:
  uint32_t state_[5];
  uint32_t count_[2];
  uint8_t buffer_[64];

  MESSAGE_DECL void transform(const uint32_t data[16]);
};

} // namespace crypto
} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/detail/crypto/impl/sha1.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_DETAIL_CRYPTO_SHA1_HPP

