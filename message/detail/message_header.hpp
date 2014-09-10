// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_MESSAGE_HEADER_HPP
#define MESSAGE_DETAIL_MESSAGE_HEADER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <cstdint>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

struct message_header {
#pragma pack(push, 1)
  union tsx_id_type {
    uint8_t u8[12];
    uint16_t u16[6];
    uint32_t u32[3];
  };
  struct impl_type {
    uint16_t type;       // message type
    uint16_t length;     // message length
    uint32_t magic;      // magic cookie
    tsx_id_type tsx_id;  // transaction id
  };
#pragma pack(pop)
  static const size_t size = sizeof(impl_type);

  class decoder {
   public:
    MESSAGE_DECL decoder(const uint8_t* msg_hdr);
    MESSAGE_DECL uint16_t type() const;
    MESSAGE_DECL uint16_t length() const;
    MESSAGE_DECL uint32_t magic() const;
    MESSAGE_DECL const tsx_id_type &tsx_id() const;
   private:
    const impl_type* p_;
  };

  class encoder {
   public:
    MESSAGE_DECL encoder(uint8_t* msg_hdr);
    MESSAGE_DECL void set_type(uint16_t type);
    MESSAGE_DECL void set_length(uint16_t length);
    MESSAGE_DECL void set_magic(uint32_t magic);
    MESSAGE_DECL void set_tsx_id(const tsx_id_type &tsx_id);
   private:
    impl_type* p_;
  };
};

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/detail/impl/message_header.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_DETAIL_MESSAGE_HEADER_HPP

