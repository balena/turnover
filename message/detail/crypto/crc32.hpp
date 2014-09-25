// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_CRYPTO_CRC32_HPP
#define MESSAGE_DETAIL_CRYPTO_CRC32_HPP

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

class crc32 {
 public:
#if defined(GENERATING_DOCUMENTATION)
  typedef array<uint8_t, 4> bytes_type;
#else
  typedef stun::detail::array<uint8_t, 4> bytes_type;
#endif
  static const size_t block_size = 4;

  MESSAGE_DECL crc32();
  MESSAGE_DECL void update(const void *data, size_t data_len);
  MESSAGE_DECL bytes_type to_bytes();

 private:
  uint32_t crc_;
};

} // namespace crypto
} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/detail/crypto/impl/crc32.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_DETAIL_CRYPTO_CRC32_HPP

