// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_CRYPTO_HMAC_HPP
#define MESSAGE_DETAIL_CRYPTO_HMAC_HPP

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

template<typename Digest>
class hmac {
 public:
  typedef typename Digest::bytes_type bytes_type;
  static const size_t block_size = Digest::block_size;

  MESSAGE_DECL hmac(const void *key, size_t key_len);
  MESSAGE_DECL void update(const void *data, size_t data_len);
  MESSAGE_DECL bytes_type to_bytes();

 private:
  Digest ctx_;
  uint8_t k_ipad_[block_size];
  uint8_t k_opad_[block_size];
};

} // namespace crypto
} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/detail/crypto/impl/hmac.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_DETAIL_CRYPTO_HMAC_HPP

