// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_MSGINT_HPP
#define MESSAGE_DETAIL_MSGINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "message/detail/attribute_base.hpp"
#include "message/detail/message_header.hpp"
#include <string>

namespace stun {
namespace detail {

struct msgint {
#pragma pack(push, 1)
  struct impl_type : public attribute_base::impl_type {
    uint8_t hmac[20]; // HMAC-SHA1 hash
  };
#pragma pack(pop)

  class decoder : public attribute_base::decoder {
   public:
    decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    bool valid() const;
    template<typename char_type>
    bool check(const char_type* first, const char_type* last) const;
    bool check(const std::string &key) const;
   private:
    const message_header::impl_type* hdr_;
    message_header::decoder hdr_decoder_;
    const impl_type* p_;
  };

  class encoder : public attribute_base::encoder {
   public:
    encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr);
    template<typename char_type>
    void sign(const char_type* first, const char_type* last);
    void sign(const std::string& key);
   private:
    const message_header::impl_type* hdr_;
    message_header::decoder hdr_decoder_;
    impl_type* p_;
  };
};

} // namespace detail
} // namespace stun

#include "message/detail/impl/msgint.ipp"

#endif // MESSAGE_DETAIL_MSGINT_HPP

