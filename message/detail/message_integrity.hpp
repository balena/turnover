// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_MESSAGE_INTEGRITY_HPP
#define MESSAGE_DETAIL_MESSAGE_INTEGRITY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/message_header.hpp>
#include <string>
#include <cstring>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

struct message_integrity {
#pragma pack(push, 1)
  struct impl_type {
    uint8_t hmac[20]; // HMAC-SHA1 hash
  };
#pragma pack(pop)
  static const size_t size = sizeof(impl_type);
  typedef message_header::impl_type header_type;

  class decoder {
   public:
    MESSAGE_DECL decoder(const uint8_t* message_header, const uint8_t* data,
        size_t data_len);
    MESSAGE_DECL bool valid() const;
    MESSAGE_DECL bool check(const uint8_t* key, size_t key_len) const;
    bool check(const char* key) const {
      using namespace std; // For strlen
      return check(reinterpret_cast<const uint8_t*>(key), strlen(key));
    }
    bool check(const std::string& key) const {
      return check(reinterpret_cast<const uint8_t*>(key.data()), key.size());
    }
   private:
    const header_type* message_header_;
    const impl_type* data_;
    size_t data_len_;
  };

  class encoder {
   public:
    MESSAGE_DECL encoder(const uint8_t* message_header, uint8_t* data);
    MESSAGE_DECL void sign(const uint8_t* key, size_t key_len);
   private:
    const header_type* message_header_;
    impl_type* data_;
  };
};

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/detail/impl/message_integrity.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_DETAIL_MESSAGE_INTEGRITY_HPP

