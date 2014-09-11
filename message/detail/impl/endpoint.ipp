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

endpoint::decoder::decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr)
  : p_((impl_type*)attr_hdr),
    basic_attribute::decoder(msg_hdr, attr_hdr) {
}

bool endpoint::decoder::valid() const {
  using namespace ::stun::detail::byte_order;
  switch (p_->family) {
    case 1:
      return length() == sizeof(p_->unused) + sizeof(p_->family) +
          sizeof(p_->port) + sizeof(p_->addr.v4);
    case 2:
      return length() == sizeof(p_->unused) + sizeof(p_->family) +
          sizeof(p_->port) + sizeof(p_->addr.v6);
  }
  return false;
}

endpoint::address_type endpoint::decoder::address() const {
  using namespace std; // For memcpy.
  using boost::asio::ip::address_v4;
  using boost::asio::ip::address_v6;
  switch (p_->family) {
    case 1: {
      address_v4::bytes_type bytes;
      memcpy(bytes.data(), p_->addr.v4, sizeof(p_->addr.v4));
      return address_type(address_v4(bytes));
    }
    case 2: {
      address_v6::bytes_type bytes;
      memcpy(bytes.data(), p_->addr.v6, sizeof(p_->addr.v6));
      return address_type(address_v6(bytes));
    }
  }
  return address_type();
}

uint16_t endpoint::decoder::port() const {
  using namespace ::stun::detail::byte_order;
  return network_to_host_short(p_->port);
}

endpoint::encoder::encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr)
  : p_((impl_type*)attr_hdr),
    basic_attribute::encoder(msg_hdr, attr_hdr) {
  p_->unused = 0;
}

void endpoint::encoder::set_address(const address_type &address) {
  using namespace std; // For memcpy.
  if (address.is_v4()) {
    p_->family = 1;
    memcpy(&p_->addr.v4, address.to_v4().to_bytes().data(),
      sizeof(p_->addr.v4));
    set_length(sizeof(p_->unused) + sizeof(p_->family)
      + sizeof(p_->port) + sizeof(p_->addr.v4));
  } else {
    p_->family = 2;
    memcpy(&p_->addr.v6, address.to_v6().to_bytes().data(),
      sizeof(p_->addr.v6));
    set_length(sizeof(p_->unused) + sizeof(p_->family)
      + sizeof(p_->port) + sizeof(p_->addr.v6));
  }
}

void endpoint::encoder::set_port(uint16_t port) {
  using namespace ::stun::detail::byte_order;
  p_->port = host_to_network_short(port);
}

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_ATTRIBUTE_DETAIL_IMPL_ENDPOINT_HPP

