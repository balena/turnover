// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_BASIC_ATTRIBUTE_HPP
#define MESSAGE_DETAIL_BASIC_ATTRIBUTE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <cstdint>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

struct attribute_header {
#pragma pack(push, 1)
  struct impl_type {
    uint16_t type;       // attribute type
    uint16_t length;     // length, no padding
  };
#pragma pack(pop)
  static const size_t size = sizeof(impl_type);

  class decoder {
   public:
    MESSAGE_DECL decoder(const uint8_t *attribute_start);
    MESSAGE_DECL uint16_t type() const;
    MESSAGE_DECL uint16_t length() const;
   private:
    const impl_type *attribute_header_;
  };

  class encoder {
   public:
    MESSAGE_DECL encoder(uint8_t *attribute_start);
    MESSAGE_DECL void set_type(uint16_t type);
    MESSAGE_DECL void set_length(uint16_t length);
   private:
    impl_type* attribute_header_;
  };
};

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/detail/impl/attribute_header.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_DETAIL_BASIC_ATTRIBUTE_HPP

