// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_IMPL_FINGERPRINT_HPP
#define MESSAGE_DETAIL_IMPL_FINGERPRINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/crypto/crc32.hpp>
#include <message/detail/attribute_header.hpp>
#include <message/detail/byte_order.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

fingerprint::decoder::decoder(const uint8_t* message_header,
    const uint8_t* data, size_t data_len)
  : uint32::decoder(data, data_len),
    message_header_(reinterpret_cast<const header_type*>(message_header)) {
}

bool fingerprint::decoder::check() const {
  return digest(message_header_) == value();
}

fingerprint::encoder::encoder(const uint8_t* message_header, uint8_t* data)
  : uint32::encoder(data),
    message_header_(reinterpret_cast<const header_type*>(message_header)) {
}

void fingerprint::encoder::sign() {
  set_value(digest(message_header_));
}

uint32_t fingerprint::digest(const header_type *header) {
  using namespace crypto;
  size_t n = message_header::size
      + network_to_host_short(header->length)
      - (attribute_header::size + uint32::size);
  crc32::bytes_type digest;
  crc32 ctx;
  ctx.update(header, n);
  digest = ctx.to_bytes();
  *(uint32_t*)digest.data() ^= xor_fingerprint;
  return *(uint32_t*)digest.data();
}

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_DETAIL_IMPL_FINGERPRINT_HPP

