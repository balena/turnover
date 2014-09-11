// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_ATTRIBUTE_DETAIL_ENDPOINT_HPP
#define MESSAGE_ATTRIBUTE_DETAIL_ENDPOINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <boost/asio/ip/address.hpp>

#include <message/detail/basic_attribute.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

struct endpoint {
#pragma pack(push, 1)
  struct impl_type : public basic_attribute::impl_type {
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

  class decoder : public basic_attribute::decoder {
   public:
    typedef endpoint::address_type address_type;
    MESSAGE_DECL decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    MESSAGE_DECL bool valid() const;
    MESSAGE_DECL address_type address() const;
    MESSAGE_DECL uint16_t port() const;
   private:
    const impl_type* p_;
  };

  class encoder : public basic_attribute::encoder {
   public:
    typedef endpoint::address_type address_type;
    MESSAGE_DECL encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr);
    MESSAGE_DECL void set_address(const address_type &address);
    MESSAGE_DECL void set_port(uint16_t port);
   private:
    impl_type* p_;
  };
};

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/detail/impl/endpoint.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_ATTRIBUTE_DETAIL_ENDPOINT_HPP

