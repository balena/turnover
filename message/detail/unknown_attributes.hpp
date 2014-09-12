// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_UNKNOWN_ATTRIBUTES_HPP
#define MESSAGE_DETAIL_UNKNOWN_ATTRIBUTES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

struct unknown_attributes {
#pragma pack(push, 1)
  struct impl_type {
    uint16_t attrs[1];   // list of 16-bit values
  };
#pragma pack(pop)

  class decoder {
   public:
    MESSAGE_DECL decoder(const uint8_t* data, size_t data_len);
    MESSAGE_DECL bool valid() const;
    MESSAGE_DECL size_t size() const;
    MESSAGE_DECL uint16_t operator[](size_t n) const;
   private:
    const impl_type* data_;
    size_t data_len_;
  };

  class encoder {
   public:
    MESSAGE_DECL encoder(uint8_t* data);
    MESSAGE_DECL void assign(const uint16_t *codes, size_t count);
   private:
    impl_type* data_;
  };

  MESSAGE_DECL static size_t size_of(size_t count);
};

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/detail/impl/unknown_attributes.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_DETAIL_UNKNOWN_ATTRIBUTES_HPP

