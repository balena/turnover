// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_ERROR_CODE_HPP
#define MESSAGE_DETAIL_ERROR_CODE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/basic_attribute.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

struct error_code {
#pragma pack(push, 1)
  struct impl_type : public basic_attribute::impl_type {
    uint16_t unused;
    uint8_t err_class;   // code / 100
    uint8_t err_code;    // code % 100
    char err_reason[1];
  };
#pragma pack(pop)

  class decoder : public basic_attribute::decoder {
   public:
    MESSAGE_DECL decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    MESSAGE_DECL bool valid() const;
    int status_code() const { return error_class() * 100 + error_code(); }
    MESSAGE_DECL int error_class() const;
    MESSAGE_DECL int error_code() const;
    MESSAGE_DECL std::string reason_phrase() const;
   private:
    const impl_type* p_;
  };

  class encoder : public basic_attribute::encoder {
   public:
    MESSAGE_DECL encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr);
    MESSAGE_DECL void set_status_code(int status);
    MESSAGE_DECL void set_reason_phrase(const char* s, size_t len,
        uint8_t pad);
   private:
    impl_type* p_;
  };
};

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/detail/impl/error_code.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_DETAIL_ERROR_CODE_HPP

