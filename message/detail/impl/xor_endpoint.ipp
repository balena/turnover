// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_ATTRIBUTE_IMPL_XOR_ENDPOINT_HPP
#define MESSAGE_DETAIL_ATTRIBUTE_IMPL_XOR_ENDPOINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/byte_order.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

xor_endpoint::decoder::decoder(const uint8_t* message_header,
    const uint8_t* data, size_t data_len)
    : endpoint::decoder(data, data_len),
      message_header_(reinterpret_cast<const header_type*>(message_header)) {
}

xor_endpoint::address_type xor_endpoint::decoder::address() const {
  return mask(message_header_, endpoint::decoder::address());
}

uint16_t xor_endpoint::decoder::port() const {
  return mask(message_header_, endpoint::decoder::port());
}

xor_endpoint::encoder::encoder(const uint8_t* message_header, uint8_t* data)
    : endpoint::encoder(data),
      message_header_(reinterpret_cast<const header_type*>(message_header)) {
}

void xor_endpoint::encoder::set_address(const address_type &address) {
  endpoint::encoder::set_address(mask(message_header_, address));
}

void xor_endpoint::encoder::set_port(uint16_t port) {
  endpoint::encoder::set_port(mask(message_header_, port));
}

xor_endpoint::address_type
    xor_endpoint::mask(const header_type* message_header,
        const address_type &address) {
  using boost::asio::ip::address_v4;
  using boost::asio::ip::address_v6;
  if (address.is_v4()) {
    address_v4::bytes_type bytes(address.to_v4().to_bytes());
    uint8_t *p = bytes.data();
    *((uint32_t*)p) ^= message_header->magic;
    return address_type(address_v4(bytes));
  } else {
    address_v6::bytes_type bytes(address.to_v6().to_bytes());
    uint8_t *p = bytes.data();
    *((uint32_t*)p) ^= message_header->magic;
    p += sizeof(uint32_t);
    const uint8_t *q = message_header->tsx_id.u8;
    // rest of IPv6 address has to be XOR'ed with the transaction id
    *p++ ^= q[0]; *p++ ^= q[1]; *p++ ^= q[2];  *p++ ^= q[3];
    *p++ ^= q[4]; *p++ ^= q[5]; *p++ ^= q[6];  *p++ ^= q[7];
    *p++ ^= q[8]; *p++ ^= q[9]; *p++ ^= q[10]; *p++ ^= q[11];
    return address_type(address_v6(bytes));
  }
}

uint16_t xor_endpoint::mask(const header_type* message_header, uint16_t port) {
  return port ^ (uint16_t)(network_to_host_long(message_header->magic) >> 16);
}

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_DETAIL_ATTRIBUTE_IMPL_XOR_ENDPOINT_HPP

