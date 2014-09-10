// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_ATTRIBUTE_DETAILS_IP_ADDRESS_HPP
#define MESSAGE_ATTRIBUTE_DETAILS_IP_ADDRESS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <boost/asio/ip/address.hpp>

#include <message/attribute/detail/attribute_base.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace attribute {
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
    MESSAGE_DECL decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    MESSAGE_DECL bool valid() const;
    MESSAGE_DECL address_type address() const;
    MESSAGE_DECL uint16_t port() const;
   private:
    const impl_type* p_;
  };

  class encoder : public attribute_base::encoder {
   public:
    typedef ip_address::address_type address_type;
    MESSAGE_DECL encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr);
    MESSAGE_DECL void set_address(const address_type &address);
    MESSAGE_DECL void set_port(uint16_t port);
   private:
    impl_type* p_;
  };
};

} // namespace detail
} // namespace attribute
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/attribute/detail/impl/ip_address.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_ATTRIBUTE_DETAILS_IP_ADDRESS_HPP

