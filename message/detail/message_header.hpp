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

#include <cstdint>

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
    decoder(const uint8_t* msg_hdr);
    uint16_t type() const;
    uint16_t length() const;
    uint32_t magic() const;
    const tsx_id_type &tsx_id() const;
   private:
    const impl_type* p_;
  };

  class encoder {
   public:
    encoder(uint8_t* msg_hdr);
    void set_type(uint16_t type);
    void set_length(uint16_t length);
    void set_magic(uint32_t magic);
    void set_tsx_id(const tsx_id_type &tsx_id);
   private:
    impl_type* p_;
  };
};

} // namespace detail
} // namespace stun

#include "message/detail/impl/message_header.ipp"

#endif // MESSAGE_DETAIL_MESSAGE_HEADER_HPP

