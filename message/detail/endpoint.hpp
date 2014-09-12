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

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

struct endpoint {
#pragma pack(push, 1)
  struct impl_type {
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

  class decoder {
   public:
    MESSAGE_DECL decoder(const uint8_t* data, size_t data_len);
    MESSAGE_DECL bool valid() const;
    MESSAGE_DECL address_type address() const;
    MESSAGE_DECL uint16_t port() const;
   private:
    const impl_type* data_;
    size_t data_len_;
  };

  class encoder {
   public:
    MESSAGE_DECL encoder(uint8_t* data);
    MESSAGE_DECL void set_address(const address_type &address);
    MESSAGE_DECL void set_port(uint16_t port);
   private:
    impl_type* data_;
  };

  MESSAGE_DECL static size_t size_of(uint8_t family);
  MESSAGE_DECL static size_t size_of(const address_type &address);
};

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/detail/impl/endpoint.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_ATTRIBUTE_DETAIL_ENDPOINT_HPP

