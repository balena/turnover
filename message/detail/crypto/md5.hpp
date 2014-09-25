// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_CRYPTO_MD5_HPP
#define MESSAGE_DETAIL_CRYPTO_MD5_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <cstdint>
#include <cstdlib>
#include <message/detail/array.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {
namespace crypto {

class md5 {
 public:
#if defined(GENERATING_DOCUMENTATION)
  typedef array<uint8_t, 16> bytes_type;
#else
  typedef stun::detail::array<uint8_t, 16> bytes_type;
#endif
  static const size_t block_size = 64;

  MESSAGE_DECL md5();
  MESSAGE_DECL void update(const void *data, size_t size);
  MESSAGE_DECL bytes_type to_bytes();

 private:
  typedef uint32_t MD5_u32plus;

  MD5_u32plus lo_, hi_;
  MD5_u32plus a_, b_, c_, d_;
  MD5_u32plus block_[16];
  uint8_t buffer_[64];

  MESSAGE_DECL const void *body(const void *data, size_t size);
};

} // namespace crypto
} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/detail/crypto/impl/md5.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_DETAIL_CRYPTO_MD5_HPP

