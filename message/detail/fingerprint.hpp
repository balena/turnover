// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_FINGERPRINT_HPP
#define MESSAGE_DETAIL_FINGERPRINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/message_header.hpp>
#include <message/detail/int_types.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

struct fingerprint {
  typedef uint32::impl_type impl_type;
  typedef message_header::impl_type header_type;

  static const uint32_t xor_fingerprint = 0x5354554euL;

  class decoder : public uint32::decoder {
   public:
    MESSAGE_DECL decoder(const uint8_t* message_header,
        const uint8_t* data, size_t data_len);
    MESSAGE_DECL bool check() const;
   private:
    const header_type* message_header_;
  };

  class encoder : public uint32::encoder {
   public:
    MESSAGE_DECL encoder(const uint8_t* message_header, uint8_t* data);
    MESSAGE_DECL void sign();
   private:
    const header_type* message_header_;
  };

  MESSAGE_DECL static uint32_t digest(const header_type *header);
};

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/detail/impl/fingerprint.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_DETAIL_FINGERPRINT_HPP

