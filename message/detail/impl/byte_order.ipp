// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_IMPL_BYTE_ORDER_HPP
#define MESSAGE_DETAIL_IMPL_BYTE_ORDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <boost/asio/detail/socket_ops.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

uint32_t network_to_host_long(uint32_t value) {
  // Forward to Boost.Asio implementation
  return boost::asio::detail::socket_ops::network_to_host_long(value);
}

uint32_t host_to_network_long(uint32_t value) {
  // Forward to Boost.Asio implementation
  return boost::asio::detail::socket_ops::host_to_network_long(value);
}

uint16_t network_to_host_short(uint16_t value) {
  // Forward to Boost.Asio implementation
  return boost::asio::detail::socket_ops::network_to_host_short(value);
}

uint16_t host_to_network_short(uint16_t value) {
  // Forward to Boost.Asio implementation
  return boost::asio::detail::socket_ops::host_to_network_short(value);
}

uint64_t network_to_host_long_long(uint64_t value) {
  // Implement on our own, as it does not exist in Boost.Asio, and normally
  // there's no ntohll implementation provided by base libraries.
  unsigned char* value_p = reinterpret_cast<unsigned char*>(&value);
  uint64_t result = (static_cast<uint64_t>(value_p[0]) << 56)
    | (static_cast<uint64_t>(value_p[1]) << 48)
    | (static_cast<uint64_t>(value_p[2]) << 40)
    | (static_cast<uint64_t>(value_p[3]) << 32)
    | (static_cast<uint64_t>(value_p[4]) << 24)
    | (static_cast<uint64_t>(value_p[5]) << 16)
    | (static_cast<uint64_t>(value_p[6]) << 8)
    | static_cast<uint64_t>(value_p[7]);
  return result;
}

uint64_t host_to_network_long_long(uint64_t value) {
  // Implement on our own, as it does not exist in Boost.Asio, and normally
  // there's no ntohll implementation provided by base libraries.
  uint64_t result;
  unsigned char* result_p = reinterpret_cast<unsigned char*>(&result);
  result_p[0] = static_cast<unsigned char>((value >> 56) & 0xFF);
  result_p[1] = static_cast<unsigned char>((value >> 48) & 0xFF);
  result_p[2] = static_cast<unsigned char>((value >> 40) & 0xFF);
  result_p[3] = static_cast<unsigned char>((value >> 32) & 0xFF);
  result_p[4] = static_cast<unsigned char>((value >> 24) & 0xFF);
  result_p[5] = static_cast<unsigned char>((value >> 16) & 0xFF);
  result_p[6] = static_cast<unsigned char>((value >> 8) & 0xFF);
  result_p[7] = static_cast<unsigned char>(value & 0xFF);
  return result;
}

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_DETAIL_IMPL_BYTE_ORDER_HPP

