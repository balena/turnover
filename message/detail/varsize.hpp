// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_VARSIZE_HPP
#define MESSAGE_DETAIL_VARSIZE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/basic_attribute.hpp>
#include <string>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

struct varsize {
#pragma pack(push, 1)
  struct impl_type : public basic_attribute::impl_type {
    uint8_t value[1];    // variable size value
  };
#pragma pack(pop)

  class decoder : public basic_attribute::decoder {
   public:
    MESSAGE_DECL decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    MESSAGE_DECL bool valid() const { return true; }
    MESSAGE_DECL const uint8_t *data() const;
    MESSAGE_DECL size_t size() const;
    MESSAGE_DECL std::string to_string() const;
   private:
    const impl_type* p_;
  };

  class encoder : public basic_attribute::encoder {
   public:
    MESSAGE_DECL encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr);
    MESSAGE_DECL void assign(const uint8_t *data, size_t data_len,
        uint8_t pad);
   private:
    impl_type* p_;
  };
};

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/detail/impl/varsize.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_DETAIL_VARSIZE_HPP

