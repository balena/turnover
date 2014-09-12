// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_IMPL_ENDPOINT_HPP
#define MESSAGE_DETAIL_IMPL_ENDPOINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/byte_order.hpp>
#include <cstring>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

endpoint::decoder::decoder(const uint8_t* data, size_t data_len)
    : data_(reinterpret_cast<const impl_type*>(data)),
      data_len_(data_len) {
}

bool endpoint::decoder::valid() const {
  return data_len_ == size_of(data_->family);
}

endpoint::address_type endpoint::decoder::address() const {
  using namespace std; // For memcpy.
  using boost::asio::ip::address_v4;
  using boost::asio::ip::address_v6;
  switch (data_->family) {
    case 1: {
      address_v4::bytes_type bytes;
      memcpy(bytes.data(), data_->addr.v4, sizeof(data_->addr.v4));
      return address_type(address_v4(bytes));
    }
    case 2: {
      address_v6::bytes_type bytes;
      memcpy(bytes.data(), data_->addr.v6, sizeof(data_->addr.v6));
      return address_type(address_v6(bytes));
    }
  }
  return address_type();
}

uint16_t endpoint::decoder::port() const {
  return network_to_host_short(data_->port);
}

endpoint::encoder::encoder(uint8_t* data)
    : data_(reinterpret_cast<impl_type*>(data)) {
  data_->unused = 0;
}

void endpoint::encoder::set_address(const address_type &address) {
  using namespace std; // For memcpy.
  if (address.is_v4()) {
    data_->family = 1;
    memcpy(&data_->addr.v4, address.to_v4().to_bytes().data(),
      sizeof(data_->addr.v4));
  } else {
    data_->family = 2;
    memcpy(&data_->addr.v6, address.to_v6().to_bytes().data(),
      sizeof(data_->addr.v6));
  }
}

void endpoint::encoder::set_port(uint16_t port) {
  data_->port = host_to_network_short(port);
}

size_t endpoint::size_of(uint8_t family) {
  // common part: unused + family + port
  size_t common_part = 4;
  if (family == 1) {
    return common_part + 4;
  } else if (family == 2) {
    return common_part + 16;
  } else {
    return 0;
  }
}

size_t endpoint::size_of(const address_type &address) {
  // common part: unused + family + port
  if (address.is_v4()) {
    return size_of(1);
  } else {
    return size_of(2);
  }
}

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_ATTRIBUTE_DETAIL_IMPL_ENDPOINT_HPP

