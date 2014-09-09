// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_IMPL_ATTRIBUTE_BASE_IPP
#define MESSAGE_DETAIL_IMPL_ATTRIBUTE_BASE_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "message/detail/byte_order.hpp"

namespace stun {
namespace detail {

attribute_base::decoder::decoder(const uint8_t*, const uint8_t* attr_hdr)
  : p_((const impl_type*)attr_hdr) {
}

uint16_t attribute_base::decoder::type() const {
  return network_to_host_short(p_->type);
}

uint16_t attribute_base::decoder::length() const {
  return network_to_host_short(p_->length);
}

attribute_base::encoder::encoder(const uint8_t*, uint8_t* attr_hdr)
  : p_((impl_type*)attr_hdr) {
}

void attribute_base::encoder::set_type(uint16_t type) {
  p_->type = host_to_network_short(type);
}

void attribute_base::encoder::set_length(uint16_t length) {
  p_->length = host_to_network_short(length);
}

} // namespace detail
} // namespace stun

#endif // MESSAGE_DETAIL_IMPL_ATTRIBUTE_BASE_IPP

