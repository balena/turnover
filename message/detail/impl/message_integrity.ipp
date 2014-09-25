// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_IMPL_MESSAGE_INTEGRITY_HPP
#define MESSAGE_DETAIL_IMPL_MESSAGE_INTEGRITY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/attribute/type.hpp>
#include <message/detail/int_types.hpp>
#include <message/detail/byte_order.hpp>
#include <message/detail/message_header.hpp>
#include <message/detail/attribute_header.hpp>

#include <message/detail/crypto/sha1.hpp>
#include <message/detail/crypto/hmac.hpp>

#include <cstring>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

message_integrity::decoder::decoder(const uint8_t* message_header, const uint8_t* data,
    size_t data_len)
  : message_header_(reinterpret_cast<const header_type*>(message_header)),
    data_(reinterpret_cast<const impl_type*>(data)),
    data_len_(data_len) {
}

bool message_integrity::decoder::valid() const {
  return data_len_ == sizeof(impl_type);
}

bool message_integrity::decoder::check(const uint8_t* key, size_t key_len) const {
  using namespace std; // For memcmp.
  using namespace ::stun::attribute;
  typedef attribute_header::impl_type attribute_type;
  typedef crypto::hmac<crypto::sha1> hmac_sha1;
  const uint8_t *p = reinterpret_cast<const uint8_t*>(message_header_);
  const uint8_t *p_end = p + network_to_host_short(message_header_->length);
  uint16_t message_length;
  if ((p_end - size) == reinterpret_cast<const uint8_t*>(data_)) {
    // OK, this is the last attribute, keep length in network byte order
    message_length = message_header_->length;
    // End is before MESSAGE-INTEGRITY
    p_end -= attribute_header::size + size;
  } else {
    // Check if the next attribute is a fingerprint, and if it's the last one
    const attribute_type* fingerprint =
        reinterpret_cast<const attribute_type*>(p_end -
            (attribute_header::size + uint32::size));
    if (fingerprint == reinterpret_cast<const attribute_type*>(&data_[1]) &&
        network_to_host_short(fingerprint->type) == type::fingerprint) {
      // Consider the message length as being the size before adding
      // the fingerprint attribute, but in network byte order
      message_length = network_to_host_short(message_header_->length) -
          sizeof(uint32::impl_type);
      message_length = host_to_network_short(message_length);
      // End is before MESSAGE-INTEGRITY and FINGERPRINT
      p_end -= attribute_header::size + size
          + attribute_header::size + uint32::size;
    } else {
      // Fail miserably...
      return false;
    }
  }
  hmac_sha1::bytes_type digest;
  hmac_sha1 ctx(key, key_len);
  ctx.update(&message_header_->type, sizeof(message_header_->type));
  ctx.update(&message_length, sizeof(message_length));
  p += sizeof(message_header_->type) + sizeof(message_length);
  ctx.update(p, p_end - p);
  digest = ctx.to_bytes();
  return memcmp(digest.data(), data_->hmac, digest.size()) == 0 ? true : false;
}

message_integrity::encoder::encoder(const uint8_t* message_header, uint8_t* data)
  : message_header_(reinterpret_cast<const header_type*>(message_header)),
    data_(reinterpret_cast<impl_type*>(data)) {
}

void message_integrity::encoder::sign(const uint8_t* key, size_t key_len) {
  typedef crypto::hmac<crypto::sha1> hmac_sha1;
  hmac_sha1 ctx(key, key_len);
  ctx.update(message_header_, message_header::size
      + network_to_host_short(message_header_->length)
          - (attribute_header::size + size));
  hmac_sha1::bytes_type digest;
  digest = ctx.to_bytes();
  memcpy(data_->hmac, digest.data(), digest.size());
}

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_DETAIL_IMPL_MESSAGE_INTEGRITY_HPP

