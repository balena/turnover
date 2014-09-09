// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_ATTRIBUTE_BASE_HPP
#define MESSAGE_DETAIL_ATTRIBUTE_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <cstdint>

namespace stun {
namespace detail {

struct attribute_base {
#pragma pack(push, 1)
  struct impl_type {
    uint16_t type;       // attribute type
    uint16_t length;     // length, no padding
  };
#pragma pack(pop)
  static const size_t size = sizeof(impl_type);

  class decoder {
   public:
    decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    uint16_t type() const;
    uint16_t length() const;
   private:
    const impl_type* p_;
  };

  class encoder {
   public:
    encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr);
    void set_type(uint16_t type);
    void set_length(uint16_t length);
   private:
    impl_type* p_;
  };
};

} // namespace detail
} // namespace stun

#include "message/detail/impl/attribute_base.ipp"

#endif // MESSAGE_DETAIL_ATTRIBUTE_BASE_HPP

