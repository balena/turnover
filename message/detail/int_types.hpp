// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_INT_TYPES_HPP
#define MESSAGE_DETAIL_INT_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "message/detail/attribute_base.hpp"

namespace stun {
namespace detail {

struct uint8 {
#pragma pack(push, 1)
  struct impl_type : public attribute_base::impl_type {
    uint8_t value;       // single 8-bit value
    uint8_t unused[3];
  };
#pragma pack(pop)

  class decoder : public attribute_base::decoder {
   public:
    decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    bool valid() const;
    uint8_t value() const;
   private:
    const impl_type* p_;
  };

  class encoder : public attribute_base::encoder {
   public:
    encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr);
    void set_value(uint8_t value);
   private:
    impl_type* p_;
  };
};

struct uint8_pad {
  typedef uint8::impl_type impl_type;

  class decoder : public attribute_base::decoder {
   public:
    decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    bool valid() const;
    uint8_t value() const;
   private:
    const impl_type* p_;
  };

  class encoder : public attribute_base::encoder {
   public:
    encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr, uint8_t pad = 0);
    void set_value(uint8_t value);
   private:
    impl_type* p_;
  };
};

struct uint16 {
#pragma pack(push, 1)
  struct impl_type : public attribute_base::impl_type {
    uint16_t value;      // single 16-bit value
    uint8_t unused[2];
  };
#pragma pack(pop)

  class decoder : public attribute_base::decoder {
   public:
    decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    bool valid() const;
    uint16_t value() const;
   private:
    const impl_type* p_;
  };

  class encoder : public attribute_base::encoder {
   public:
    encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr);
    void set_value(uint16_t value);
   private:
    impl_type* p_;
  };
};

struct uint16_pad {
  typedef uint16::impl_type impl_type;

  class decoder : public attribute_base::decoder {
   public:
    decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    bool valid() const;
    uint16_t value() const;
   private:
    const impl_type* p_;
  };

  class encoder : public attribute_base::encoder {
   public:
    encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr, uint8_t pad = 0);
    void set_value(uint16_t value);
   private:
    impl_type* p_;
  };
};

struct uint32 {
#pragma pack(push, 1)
  struct impl_type : public attribute_base::impl_type {
    uint32_t value;      // single 32-bit value
  };
#pragma pack(pop)

  class decoder : public attribute_base::decoder {
   public:
    decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    bool valid() const;
    uint32_t value() const;
   private:
    const impl_type* p_;
  };

  class encoder : public attribute_base::encoder {
   public:
    encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr);
    void set_value(uint32_t value);
   private:
    impl_type* p_;
  };
};

struct uint64 {
#pragma pack(push, 1)
  struct impl_type : public attribute_base::impl_type {
    uint64_t value;      // single 32-bit value
  };
#pragma pack(pop)

  class decoder : public attribute_base::decoder {
   public:
    decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr);
    bool valid() const;
    uint64_t value() const;
   private:
    const impl_type* p_;
  };

  class encoder : public attribute_base::encoder {
   public:
    encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr);
    void set_value(uint64_t value);
   private:
    impl_type* p_;
  };
};

} // namespace detail
} // namespace stun

#include "message/detail/impl/int_types.ipp"

#endif // MESSAGE_DETAIL_INT_TYPES_HPP

