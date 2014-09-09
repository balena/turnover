// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAILS_IP_ADDRESS_HPP
#define MESSAGE_DETAILS_IP_ADDRESS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/ip/address.hpp>

#include "message/detail/attribute_base.hpp"

namespace stun {
namespace detail {

struct ip_address {
#pragma pack(push, 1)
  struct impl_type : public attribute_base::impl_type {
    uint8_t unused;
    uint8_t family; // IPv4 = 1, IPv6 = 2
    uint16_t port;
    union {
      uint8_t v4[4];
      uint8_t v6[16];
    } addr;
  };
#pragma pack(pop)

  typedef boost::asio::ip::address address_type;

  class decoder : public attribute_base::decoder {
   public:
    typedef ip_address::address_type address_type;
    decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    bool valid() const;
    address_type address() const;
    uint16_t port() const;
   private:
    const impl_type* p_;
  };

  class encoder : public attribute_base::encoder {
   public:
    typedef ip_address::address_type address_type;
    encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr);
    void set_address(const address_type &address);
    void set_port(uint16_t port);
   private:
    impl_type* p_;
  };
};

} // namespace detail
} // namespace stun

#include "message/detail/impl/ip_address.ipp"

#endif // MESSAGE_DETAILS_IP_ADDRESS_HPP

