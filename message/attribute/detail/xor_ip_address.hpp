// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_ATTRIBUTE_DETAIL_XOR_IP_ADDRESS_HPP
#define MESSAGE_ATTRIBUTE_DETAIL_XOR_IP_ADDRESS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/message_header.hpp>
#include <message/attribute/detail/ip_address.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace attribute {
namespace detail {

struct xor_ip_address {
  typedef ip_address::impl_type impl_type;
  typedef ip_address::address_type address_type;
  typedef ::stun::detail::message_header message_header;

  class decoder : public attribute_base::decoder {
   public:
    typedef ip_address::address_type address_type;
    MESSAGE_DECL decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    MESSAGE_DECL bool valid() const;
    MESSAGE_DECL address_type address() const;
    MESSAGE_DECL uint16_t port() const;
   private:
    const message_header::impl_type* p_;
    ip_address::decoder base_;
  };

  class encoder : public attribute_base::encoder {
   public:
    typedef ip_address::address_type address_type;
    MESSAGE_DECL encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr);
    MESSAGE_DECL void set_address(const address_type &address);
    MESSAGE_DECL void set_port(uint16_t port);
   private:
    message_header::impl_type* p_;
    ip_address::encoder base_;
  };
};

} // namespace detail
} // namespace attribute
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/attribute/detail/impl/xor_ip_address.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_ATTRIBUTE_DETAIL_XOR_IP_ADDRESS_HPP
