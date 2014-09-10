// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_ATTRIBUTE_DETAIL_VARSIZE_HPP
#define MESSAGE_ATTRIBUTE_DETAIL_VARSIZE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/attribute/detail/attribute_base.hpp>
#include <string>

#include <message/detail/push_options.hpp>

namespace stun {
namespace attribute {
namespace detail {

struct varsize {
#pragma pack(push, 1)
  struct impl_type : public attribute_base::impl_type {
    uint8_t value[1];    // variable size value
  };
#pragma pack(pop)

  class decoder : public attribute_base::decoder {
   public:
    MESSAGE_DECL decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    MESSAGE_DECL bool valid() const { return true; }
    MESSAGE_DECL const uint8_t *data() const;
    MESSAGE_DECL size_t size() const;
    MESSAGE_DECL std::string to_string() const;
   private:
    const impl_type* p_;
  };

  class encoder : public attribute_base::encoder {
   public:
    MESSAGE_DECL encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr);
    MESSAGE_DECL void assign(const uint8_t *data, size_t data_len,
        uint8_t pad);
   private:
    impl_type* p_;
  };
};

} // namespace detail
} // namespace atttribute
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/attribute/detail/impl/varsize.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_ATTRIBUTE_DETAIL_VARSIZE_HPP

