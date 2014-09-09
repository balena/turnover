// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_BYTE_ORDER_HPP
#define MESSAGE_DETAIL_BYTE_ORDER_HPP

#include <boost/asio/detail/socket_ops.hpp>
#include <cstdint>

namespace stun {
namespace detail {

uint32_t network_to_host_long(uint32_t value) {
  return boost::asio::detail::socket_ops::network_to_host_long(value);
}

uint32_t host_to_network_long(uint32_t value) {
  return boost::asio::detail::socket_ops::host_to_network_long(value);
}

uint16_t network_to_host_short(uint16_t value) {
  return boost::asio::detail::socket_ops::network_to_host_short(value);
}

uint16_t host_to_network_short(uint16_t value) {
  return boost::asio::detail::socket_ops::host_to_network_short(value);
}

uint64_t network_to_host_long_long(uint64_t value) {
  return (((uint64_t)host_to_network_long((uint32_t)value)) << 32)
         | host_to_network_long((uint32_t)(value >> 32));
}

uint64_t host_to_network_long_long(uint64_t value) {
  return network_to_host_long_long(value);
}

} // namespace detail
} // namespace stun

#endif // MESSAGE_DETAIL_BYTE_ORDER_HPP
