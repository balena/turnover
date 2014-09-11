// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_ATTRIBUTE_DETAIL_IMPL_UNKNOWN_HPP
#define MESSAGE_ATTRIBUTE_DETAIL_IMPL_UNKNOWN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/byte_order.hpp>
#include <message/attribute/detail/padding.hpp>
#include <cstring>

#include <message/detail/push_options.hpp>

namespace stun {
namespace attribute {
namespace detail {

unknown::decoder::decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr)
  : p_((impl_type*)attr_hdr),
    attribute_base::decoder(msg_hdr, attr_hdr) {
}

size_t unknown::decoder::size() const {
  return length() / sizeof(uint16_t);
}

uint16_t unknown::decoder::operator[](size_t n) const {
  using namespace ::stun::detail::byte_order;
  return network_to_host_short(p_->attrs[n]);
}

unknown::encoder::encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr)
  : p_((impl_type*)attr_hdr),
    attribute_base::encoder(msg_hdr, attr_hdr) {
}

void unknown::encoder::set_unknown(const uint16_t *codes, size_t count) {
  using namespace ::stun::detail::byte_order;
  for (size_t i = 0; i < count; i++)
    p_->attrs[i] = host_to_network_short(codes[i]);
  set_length(count * sizeof(uint16_t));
}

} // namespace detail
} // namespace attribute
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_ATTRIBUTE_DETAIL_IMPL_UNKNOWN_HPP

