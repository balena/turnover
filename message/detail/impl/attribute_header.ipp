// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_IMPL_BASIC_ATTRIBUTE_IPP
#define MESSAGE_DETAIL_IMPL_BASIC_ATTRIBUTE_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/byte_order.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

attribute_header::decoder::decoder(const uint8_t *attribute_start)
  : attribute_header_(reinterpret_cast<const impl_type*>(attribute_start)) {
}

uint16_t attribute_header::decoder::type() const {
  return network_to_host_short(attribute_header_->type);
}

uint16_t attribute_header::decoder::length() const {
  return network_to_host_short(attribute_header_->length);
}

attribute_header::encoder::encoder(uint8_t* attribute_start)
  : attribute_header_(reinterpret_cast<impl_type*>(attribute_start)) {
}

void attribute_header::encoder::set_type(uint16_t type) {
  attribute_header_->type = host_to_network_short(type);
}

void attribute_header::encoder::set_length(uint16_t length) {
  attribute_header_->length = host_to_network_short(length);
}

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_DETAIL_IMPL_BASIC_ATTRIBUTE_IPP

