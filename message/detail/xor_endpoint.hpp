// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_XOR_ENDPOINT_HPP
#define MESSAGE_DETAIL_XOR_ENDPOINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/message_header.hpp>
#include <message/detail/endpoint.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

struct xor_endpoint {
  typedef endpoint::impl_type impl_type;
  typedef endpoint::address_type address_type;
  typedef message_header::impl_type header_type;

  class decoder : public endpoint::decoder {
   public:
    MESSAGE_DECL decoder(const uint8_t* message_header,
        const uint8_t* data, size_t data_len);
    bool valid() const { return endpoint::decoder::valid(); }
    MESSAGE_DECL address_type address() const;
    MESSAGE_DECL uint16_t port() const;
   private:
    const header_type* message_header_;
  };

  class encoder : public endpoint::encoder {
   public:
    MESSAGE_DECL encoder(const uint8_t* message_header, uint8_t* data);
    MESSAGE_DECL void set_address(const address_type &address);
    MESSAGE_DECL void set_port(uint16_t port);
   private:
    const header_type* message_header_;
  };

  MESSAGE_DECL static address_type mask(const header_type* message_header,
      const address_type &address);
  MESSAGE_DECL static uint16_t mask(const header_type* message_header,
      uint16_t port);

  static size_t size_of(const address_type &address) {
    return endpoint::size_of(address);
  }
};

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/detail/impl/xor_endpoint.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_DETAIL_XOR_ENDPOINT_HPP

