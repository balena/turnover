// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_ATTRIBUTE_DETAIL_MSGINT_HPP
#define MESSAGE_ATTRIBUTE_DETAIL_MSGINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/attribute/detail/attribute_base.hpp>
#include <message/detail/message_header.hpp>
#include <string>

#include <message/detail/push_options.hpp>

namespace stun {
namespace attribute {
namespace detail {

struct msgint {
#pragma pack(push, 1)
  struct impl_type : public attribute_base::impl_type {
    uint8_t hmac[20]; // HMAC-SHA1 hash
  };
#pragma pack(pop)
  static const size_t size = sizeof(impl_type);
  typedef ::stun::detail::message_header message_header;

  class decoder : public attribute_base::decoder {
   public:
    MESSAGE_DECL decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    MESSAGE_DECL bool valid() const;
    MESSAGE_DECL bool check(const uint8_t* key, size_t key_len) const;
   private:
    const message_header::impl_type* hdr_;
    ::stun::detail::message_header::decoder hdr_decoder_;
    const impl_type* p_;
  };

  class encoder : public attribute_base::encoder {
   public:
    MESSAGE_DECL encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr);
    MESSAGE_DECL void sign(const uint8_t* key, size_t key_len);
   private:
    const message_header::impl_type* hdr_;
    message_header::decoder hdr_decoder_;
    impl_type* p_;
  };
};

} // namespace detail
} // namespace attribute
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/attribute/detail/impl/msgint.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_ATTRIBUTE_DETAIL_MSGINT_HPP

