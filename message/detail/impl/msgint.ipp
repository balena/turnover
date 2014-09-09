// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_IMPL_MSGINT_HPP
#define MESSAGE_DETAIL_IMPL_MSGINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "message/detail/int_types.hpp"
#include "message/detail/byte_order.hpp"
#include "message/attribute/type.hpp"

#include "crypto/sha1.hpp"
#include "crypto/hmac.hpp"

#include <cstring>

namespace stun {
namespace detail {

msgint::decoder::decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr)
  : attribute_base::decoder(msg_hdr, attr_hdr),
    hdr_((const message_header::impl_type*)msg_hdr),
    hdr_decoder_(msg_hdr),
    p_((const impl_type*)attr_hdr) {
}

bool msgint::decoder::valid() const {
  return length() == sizeof(p_->hmac);
}

template<typename char_type>
bool msgint::decoder::check(const char_type* first,
    const char_type* last) const {
  using namespace std; // For memcmp.
  typedef crypto::hmac<crypto::sha1> hmac_sha1;
  const uint8_t *p = (const uint8_t*)hdr_;
  const uint8_t *p_end = p + hdr_decoder_.length() - sizeof(impl_type);
  uint16_t message_length;
  hmac_sha1::digest_type digest;
  const uint32::impl_type* fprint =
    (const uint32::impl_type*)(p_end - sizeof(uint32::impl_type));
  if ((const uint8_t *)fprint == ((const uint8_t *)&p_[1]) &&
      network_to_host_short(fprint->type) == attribute::type::fingerprint) {
    message_length = host_to_network_short(
      hdr_decoder_.length() - sizeof(uint32::impl_type));
    p_end -= sizeof(uint32::impl_type);
  } else {
    message_length = hdr_->length;
  }
  hmac_sha1 ctx(first, (last - first) * sizeof(char_type));
  ctx.update(hdr_, sizeof(hdr_->type));
  ctx.update(&message_length, sizeof(hdr_->length));
  p += sizeof(hdr_->type) + sizeof(hdr_->length);
  ctx.update(p, p_end - p);
  ctx.final(digest);
  return memcmp(digest, p_->hmac, sizeof(digest)) == 0 ? true : false;
}

bool msgint::decoder::check(const std::string &key) const {
  return check(key.data(), key.data() + key.length());
}

msgint::encoder::encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr)
  : attribute_base::encoder(msg_hdr, attr_hdr),
    hdr_((message_header::impl_type*)msg_hdr),
    hdr_decoder_(msg_hdr),
    p_((impl_type*)attr_hdr) {
}

template<typename char_type>
void msgint::encoder::sign(const char_type* first, const char_type* last) {
  typedef crypto::hmac<crypto::sha1> hmac_sha1;
  uint8_t *p = (uint8_t *)hdr_;
  uint8_t *p_end = p + hdr_decoder_.length() - sizeof(impl_type);
  hmac_sha1 ctx(first, (last - first) * sizeof(char_type));
  ctx.update(p, p_end - p);
  ctx.final(p_->hmac);
}

void msgint::encoder::sign(const std::string& key) {
  sign(key.data(), key.data() + key.length());
}

} // namespace detail
} // namespace stun

#endif // MESSAGE_DETAIL_IMPL_MSGINT_HPP

