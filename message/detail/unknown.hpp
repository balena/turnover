// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_UNKNOWN_HPP
#define MESSAGE_DETAIL_UNKNOWN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/basic_attribute.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

struct unknown {
#pragma pack(push, 1)
  struct impl_type : public basic_attribute::impl_type {
    uint16_t attrs[1];   // list of 16-bit values
  };
#pragma pack(pop)

  class decoder : public basic_attribute::decoder {
   public:
    MESSAGE_DECL decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    bool valid() const { return true; }
    MESSAGE_DECL size_t size() const;
    MESSAGE_DECL uint16_t operator[](size_t n) const;
   private:
    const impl_type* p_;
  };

  class encoder : public basic_attribute::encoder {
   public:
    MESSAGE_DECL encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr);
    MESSAGE_DECL void set_unknown(const uint16_t *codes, size_t count);
   private:
    impl_type* p_;
  };
};

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/detail/impl/unknown.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_DETAIL_UNKNOWN_HPP

