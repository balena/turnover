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

basic_attribute::decoder::decoder(const uint8_t*, const uint8_t* attr_hdr)
  : p_((const impl_type*)attr_hdr) {
}

uint16_t basic_attribute::decoder::type() const {
  using namespace ::stun::detail::byte_order;
  return network_to_host_short(p_->type);
}

uint16_t basic_attribute::decoder::length() const {
  using namespace ::stun::detail::byte_order;
  return network_to_host_short(p_->length);
}

basic_attribute::encoder::encoder(const uint8_t*, uint8_t* attr_hdr)
  : p_((impl_type*)attr_hdr) {
}

void basic_attribute::encoder::set_type(uint16_t type) {
  using namespace ::stun::detail::byte_order;
  p_->type = host_to_network_short(type);
}

void basic_attribute::encoder::set_length(uint16_t length) {
  using namespace ::stun::detail::byte_order;
  p_->length = host_to_network_short(length);
}

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_DETAIL_IMPL_BASIC_ATTRIBUTE_IPP
