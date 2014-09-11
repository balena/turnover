// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_IMPL_MESSAGE_HEADER_IPP
#define MESSAGE_DETAIL_IMPL_MESSAGE_HEADER_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/byte_order.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

message_header::decoder::decoder(const uint8_t* msg_hdr)
  : p_((const impl_type*)msg_hdr) {
}

uint16_t message_header::decoder::type() const {
  return byte_order::network_to_host_short(p_->type);
}

uint16_t message_header::decoder::length() const {
  return byte_order::network_to_host_short(p_->length);
}

uint32_t message_header::decoder::magic() const {
  return byte_order::network_to_host_long(p_->magic);
}

const message_header::tsx_id_type &message_header::decoder::tsx_id() const {
  return p_->tsx_id;
}

message_header::encoder::encoder(uint8_t* msg_hdr)
  : p_((impl_type*)msg_hdr) {
}

void message_header::encoder::set_type(uint16_t type) {
  p_->type = byte_order::host_to_network_short(type);
}

void message_header::encoder::set_length(uint16_t length) {
  p_->length = byte_order::host_to_network_short(length);
}

void message_header::encoder::set_magic(uint32_t magic) {
  p_->magic = byte_order::host_to_network_long(magic);
}

void message_header::encoder::set_tsx_id(const tsx_id_type &tsx_id) {
  p_->tsx_id = tsx_id;
}

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_DETAIL_IMPL_MESSAGE_HEADER_IPP

