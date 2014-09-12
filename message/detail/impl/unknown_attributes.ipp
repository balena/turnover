// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_IMPL_UNKNOWN_ATTRIBUTES_HPP
#define MESSAGE_DETAIL_IMPL_UNKNOWN_ATTRIBUTES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/byte_order.hpp>
#include <message/detail/padding.hpp>
#include <cstring>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

unknown_attributes::decoder::decoder(const uint8_t* data, size_t data_len)
  : data_(reinterpret_cast<const impl_type*>(data)),
    data_len_(data_len) {
}

bool unknown_attributes::decoder::valid() const {
  return (data_len_ % sizeof(uint16_t)) == 0;
}

size_t unknown_attributes::decoder::size() const {
  return data_len_ / sizeof(uint16_t);
}

uint16_t unknown_attributes::decoder::operator[](size_t n) const {
  return network_to_host_short(data_->attrs[n]);
}

unknown_attributes::encoder::encoder(uint8_t* data)
  : data_(reinterpret_cast<impl_type*>(data)) {
}

void unknown_attributes::encoder::assign(const uint16_t *codes, size_t count) {
  for (size_t i = 0; i < count; i++)
    data_->attrs[i] = host_to_network_short(codes[i]);
}

size_t unknown_attributes::size_of(size_t count) {
  return count * sizeof(uint16_t);
}

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_DETAIL_IMPL_UNKNOWN_ATTRIBUTES_HPP

