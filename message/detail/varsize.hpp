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

#include "message/detail/attribute_base.hpp"
#include <string>

namespace stun {
namespace detail {

struct string {
#pragma pack(push, 1)
  struct impl_type : public attribute_base::impl_type {
    uint8_t value[1];    // variable size value
  };
#pragma pack(pop)

  class decoder : public attribute_base::decoder {
   public:
    decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    bool valid() const { return true; }
    std::string to_string() const;
   private:
    const impl_type* p_;
  };

  class encoder : public attribute_base::encoder {
   public:
    encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr);
    template<typename Iter>
    void set_value(Iter first, Iter last);
    void set_value(const std::string& value);
   private:
    impl_type* p_;
  };
};

struct data {
  typedef string::impl_type impl_type;

  class decoder : public attribute_base::decoder {
   public:
    decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    bool valid() const { return true; }
    const uint8_t *data() const;
    size_t size() const;
   private:
    const impl_type* p_;
  };

  class encoder : public attribute_base::encoder {
   public:
    encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr);
    template<typename Iter>
    void set_value(Iter first, Iter last);
    void set_value(const uint8_t* data, size_t data_len);
   private:
    impl_type* p_;
  };
};

} // namespace detail
} // namespace stun

#include "message/detail/impl/varsize.ipp"

#endif // MESSAGE_DETAIL_VARSIZE_HPP

