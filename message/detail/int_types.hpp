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

#include <message/detail/config.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

struct uint8 {
#pragma pack(push, 1)
  struct impl_type {
    uint8_t value;       // single 8-bit value
    uint8_t unused[3];
  };
#pragma pack(pop)
  static const size_t size = sizeof(impl_type);

  class decoder {
   public:
    MESSAGE_DECL decoder(const uint8_t* data, size_t data_len);
    MESSAGE_DECL bool valid() const;
    MESSAGE_DECL uint8_t value() const;
   private:
    const impl_type* data_;
    size_t data_len_;
  };

  class encoder {
   public:
    MESSAGE_DECL encoder(uint8_t* data);
    MESSAGE_DECL void set_value(uint8_t value);
   private:
    impl_type* data_;
  };
};

struct uint8_pad {
  typedef uint8::impl_type impl_type;
  static const size_t size = sizeof(impl_type);

  class decoder {
   public:
    MESSAGE_DECL decoder(const uint8_t* data, size_t data_len);
    MESSAGE_DECL bool valid() const;
    MESSAGE_DECL uint8_t value() const;
   private:
    const impl_type* data_;
    size_t data_len_;
  };

  class encoder {
   public:
    MESSAGE_DECL encoder(uint8_t* data, uint8_t pad = 0);
    MESSAGE_DECL void set_value(uint8_t value);
   private:
    impl_type* data_;
  };
};

struct uint16 {
#pragma pack(push, 1)
  struct impl_type {
    uint16_t value;      // single 16-bit value
    uint8_t unused[2];
  };
#pragma pack(pop)
  static const size_t size = sizeof(impl_type);

  class decoder {
   public:
    MESSAGE_DECL decoder(const uint8_t* data, size_t data_len);
    MESSAGE_DECL bool valid() const;
    MESSAGE_DECL uint16_t value() const;
   private:
    const impl_type* data_;
    size_t data_len_;
  };

  class encoder {
   public:
    MESSAGE_DECL encoder(uint8_t* data);
    MESSAGE_DECL void set_value(uint16_t value);
   private:
    impl_type* data_;
  };
};

struct uint16_pad {
  typedef uint16::impl_type impl_type;
  static const size_t size = sizeof(impl_type);

  class decoder {
   public:
    MESSAGE_DECL decoder(const uint8_t* data, size_t data_len);
    MESSAGE_DECL bool valid() const;
    MESSAGE_DECL uint16_t value() const;
   private:
    const impl_type* data_;
    size_t data_len_;
  };

  class encoder {
   public:
    MESSAGE_DECL encoder(uint8_t* data, uint8_t pad = 0);
    MESSAGE_DECL void set_value(uint16_t value);
   private:
    impl_type* data_;
  };
};

struct uint32 {
#pragma pack(push, 1)
  struct impl_type {
    uint32_t value;      // single 32-bit value
  };
#pragma pack(pop)
  static const size_t size = sizeof(impl_type);

  class decoder {
   public:
    MESSAGE_DECL decoder(const uint8_t* data, size_t data_len);
    MESSAGE_DECL bool valid() const;
    MESSAGE_DECL uint32_t value() const;
   private:
    const impl_type* data_;
    size_t data_len_;
  };

  class encoder {
   public:
    MESSAGE_DECL encoder(uint8_t* data);
    MESSAGE_DECL void set_value(uint32_t value);
   private:
    impl_type* data_;
  };
};

struct uint64 {
#pragma pack(push, 1)
  struct impl_type {
    uint64_t value;      // single 32-bit value
  };
#pragma pack(pop)
  static const size_t size = sizeof(impl_type);

  class decoder {
   public:
    MESSAGE_DECL decoder(const uint8_t* data, size_t data_len);
    MESSAGE_DECL bool valid() const;
    MESSAGE_DECL uint64_t value() const;
   private:
    const impl_type* data_;
    size_t data_len_;
  };

  class encoder {
   public:
    MESSAGE_DECL encoder(uint8_t* data);
    MESSAGE_DECL void set_value(uint64_t value);
   private:
    impl_type* data_;
  };
};

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/detail/impl/int_types.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_DETAIL_INT_TYPES_HPP

