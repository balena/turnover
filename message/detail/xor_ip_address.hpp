// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAILS_XOR_IP_ADDRESS_HPP
#define MESSAGE_DETAILS_XOR_IP_ADDRESS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "message/detail/message_header.hpp"
#include "message/detail/ip_address.hpp"

namespace stun {
namespace detail {

struct xor_ip_address {
  typedef ip_address::impl_type impl_type;
  typedef ip_address::address_type address_type;

  class decoder : public attribute_base::decoder {
   public:
    typedef ip_address::address_type address_type;
    decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    bool valid() const;
    address_type address() const;
    uint16_t port() const;
   private:
    const message_header::impl_type* p_;
    ip_address::decoder base_;
  };

  class encoder : public attribute_base::encoder {
   public:
    typedef ip_address::address_type address_type;
    encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr);
    void set_address(const address_type &address);
    void set_port(uint16_t port);
   private:
    message_header::impl_type* p_;
    ip_address::encoder base_;
  };
};

} // namespace detail
} // namespace stun

#include "message/detail/impl/xor_ip_address.ipp"

#endif // MESSAGE_DETAILS_XOR_IP_ADDRESS_HPP

