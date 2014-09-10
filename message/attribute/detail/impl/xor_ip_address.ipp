// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_ATTRIBUTE_IMPL_XOR_IP_ADDRESS_HPP
#define MESSAGE_DETAIL_ATTRIBUTE_IMPL_XOR_IP_ADDRESS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/byte_order.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace attribute {
namespace detail {

xor_ip_address::decoder::decoder(const uint8_t* msg_hdr,
    const uint8_t* attr_hdr)
  : attribute_base::decoder(msg_hdr, attr_hdr),
    p_((const message_header::impl_type*)attr_hdr),
    base_(msg_hdr, attr_hdr) {
}

bool xor_ip_address::decoder::valid() const {
  return base_.valid();
}

xor_ip_address::address_type xor_ip_address::decoder::address() const {
  using boost::asio::ip::address_v4;
  using boost::asio::ip::address_v6;
  address_type result(base_.address());
  if (result.is_v4()) {
    address_v4::bytes_type bytes(result.to_v4().to_bytes());
    uint8_t *p = bytes.data();
    *((uint32_t*)p) ^= p_->magic;
    result = address_type(address_v4(bytes));
  } else {
    address_v6::bytes_type bytes(result.to_v6().to_bytes());
    uint8_t *p = bytes.data();
    *((uint32_t*)p) ^= p_->magic;
    p += sizeof(uint32_t);
    // rest of IPv6 address has to be XOR'ed with the transaction id
    *p++ ^= p_->tsx_id.u8[0];  *p++ ^= p_->tsx_id.u8[1];
    *p++ ^= p_->tsx_id.u8[2];  *p++ ^= p_->tsx_id.u8[3];
    *p++ ^= p_->tsx_id.u8[4];  *p++ ^= p_->tsx_id.u8[5];
    *p++ ^= p_->tsx_id.u8[6];  *p++ ^= p_->tsx_id.u8[7];
    *p++ ^= p_->tsx_id.u8[8];  *p++ ^= p_->tsx_id.u8[9];
    *p++ ^= p_->tsx_id.u8[10]; *p++ ^= p_->tsx_id.u8[11];
    result = address_type(address_v6(bytes));
  }
  return result;
}

uint16_t xor_ip_address::decoder::port() const {
  using namespace ::stun::detail::byte_order;
  return base_.port() ^ (uint16_t)(network_to_host_long(p_->magic) >> 16);
}

xor_ip_address::encoder::encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr)
  : attribute_base::encoder(msg_hdr, attr_hdr),
    p_((message_header::impl_type*)msg_hdr),
    base_(msg_hdr, attr_hdr) {
}

void xor_ip_address::encoder::set_address(const address_type &address) {
  using boost::asio::ip::address_v4;
  using boost::asio::ip::address_v6;
  address_type input;
  if (address.is_v4()) {
    address_v4::bytes_type bytes(address.to_v4().to_bytes());
    uint8_t *p = bytes.data();
    *((uint32_t*)p) ^= p_->magic;
    base_.set_address(address_v4(bytes));
  } else {
    address_v6::bytes_type bytes(address.to_v6().to_bytes());
    uint8_t *p = bytes.data();
    *((uint32_t*)p) ^= p_->magic;
    p += sizeof(uint32_t);
    // rest of IPv6 address has to be XOR'ed with the transaction id
    *p++ ^= p_->tsx_id.u8[0];  *p++ ^= p_->tsx_id.u8[1];
    *p++ ^= p_->tsx_id.u8[2];  *p++ ^= p_->tsx_id.u8[3];
    *p++ ^= p_->tsx_id.u8[4];  *p++ ^= p_->tsx_id.u8[5];
    *p++ ^= p_->tsx_id.u8[6];  *p++ ^= p_->tsx_id.u8[7];
    *p++ ^= p_->tsx_id.u8[8];  *p++ ^= p_->tsx_id.u8[9];
    *p++ ^= p_->tsx_id.u8[10]; *p++ ^= p_->tsx_id.u8[11];
    base_.set_address(address_v6(bytes));
  }
}

void xor_ip_address::encoder::set_port(uint16_t port) {
  using namespace ::stun::detail::byte_order;
  base_.set_port(port ^ (uint16_t)(network_to_host_long(p_->magic) >> 16));
}

} // namespace detail
} // namespace attribute
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_DETAIL_ATTRIBUTE_IMPL_XOR_IP_ADDRESS_HPP

