// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_ATTRIBUTE_DETAIL_IMPL_FINGERPRINT_HPP
#define MESSAGE_ATTRIBUTE_DETAIL_IMPL_FINGERPRINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <crypto/crc32.hpp>
#include <message/detail/byte_order.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace attribute {
namespace detail {

uint32_t fingerprint::digest(const message_header::impl_type *header) {
  using namespace crypto;
  using namespace ::stun::detail::byte_order;
  size_t n = message_header::size
      + network_to_host_short(header->length)
      - uint32::size;
  crc32::digest_type digest;
  crc32 ctx;
  ctx.update(header, n);
  ctx.final(digest);
  digest ^= xor_fingerprint;
  return digest;
}

fingerprint::decoder::decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr)
  : header_((const message_header::impl_type*)msg_hdr),
    uint32::decoder(msg_hdr, attr_hdr) {
}

bool fingerprint::decoder::check() const {
  return digest(header_) == value();
}

fingerprint::encoder::encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr)
  : header_((message_header::impl_type*)msg_hdr),
    uint32::encoder(msg_hdr, attr_hdr) {
}

void fingerprint::encoder::sign() {
  set_value(digest(header_));
}

} // namespace detail
} // namespace attribute
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_ATTRIBUTE_DETAIL_IMPL_FINGERPRINT_HPP

