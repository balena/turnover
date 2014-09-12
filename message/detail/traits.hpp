// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_TRAITS_HPP
#define MESSAGE_DETAIL_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/attribute/type.hpp>
#include <message/detail/empty.hpp>
#include <message/detail/int_types.hpp>
#include <message/detail/varsize.hpp>
#include <message/detail/endpoint.hpp>
#include <message/detail/xor_endpoint.hpp>
#include <message/detail/error_code.hpp>
#include <message/detail/fingerprint.hpp>
#include <message/detail/message_integrity.hpp>
#include <message/detail/unknown_attributes.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

template<uint16_t T>
struct traits;

#define MESSAGE_ATTRIBUTE_SPECIAL(d, a) // defined below

#define MESSAGE_ATTRIBUTE_EMPTY(d, a) \
template<> \
struct traits<attribute::type::d> { \
  typedef empty::decoder decoding_type; \
  decoding_type decode(const uint8_t*, const uint8_t*, size_t data_len) { \
    return decoding_type(data_len); \
  } \
};

#define MESSAGE_ATTRIBUTE_DATA(d, a) \
template<> \
struct traits<attribute::type::d> { \
  typedef varsize::decoder decoding_type; \
  decoding_type decode(const uint8_t*, const uint8_t* data, \
      size_t data_len) { \
    return decoding_type(data, data_len); \
  } \
};

#define MESSAGE_ATTRIBUTE_STRING(d, a) MESSAGE_ATTRIBUTE_DATA(d, a)

#define MESSAGE_ATTRIBUTE_SOCKADDR(d, a) \
template<> \
struct traits<attribute::type::d> { \
  typedef endpoint::decoder decoding_type; \
  decoding_type decode(const uint8_t*, const uint8_t* data, \
      size_t data_len) { \
    return decoding_type(data, data_len); \
  } \
};

#define MESSAGE_ATTRIBUTE_XOR_SOCKADDR(d, a) \
template<> \
struct traits<attribute::type::d> { \
  typedef xor_endpoint::decoder decoding_type; \
  decoding_type decode(const uint8_t* message_header, const uint8_t* data, \
      size_t data_len) { \
    return decoding_type(message_header, data, data_len); \
  } \
};

#define MESSAGE_ATTRIBUTE_UINT8(d, a) \
template<> \
struct traits<attribute::type::d> { \
  typedef uint8::decoder decoding_type; \
  decoding_type decode(const uint8_t*, const uint8_t* data, \
      size_t data_len) { \
    return decoding_type(data, data_len); \
  } \
};

#define MESSAGE_ATTRIBUTE_UINT8_PAD(d, a) \
template<> \
struct traits<attribute::type::d> { \
  typedef uint8_pad::decoder decoding_type; \
  decoding_type decode(const uint8_t*, const uint8_t* data, \
      size_t data_len) { \
    return decoding_type(data, data_len); \
  } \
};

#define MESSAGE_ATTRIBUTE_UINT16(d, a) \
template<> \
struct traits<attribute::type::d> { \
  typedef uint16::decoder decoding_type; \
  decoding_type decode(const uint8_t*, const uint8_t* data, \
      size_t data_len) { \
    return decoding_type(data, data_len); \
  } \
};

#define MESSAGE_ATTRIBUTE_UINT16_PAD(d, a) \
template<> \
struct traits<attribute::type::d> { \
  typedef uint16_pad::decoder decoding_type; \
  decoding_type decode(const uint8_t*, const uint8_t* data, \
      size_t data_len) { \
    return decoding_type(data, data_len); \
  } \
};

#define MESSAGE_ATTRIBUTE_UINT32(d, a) \
template<> \
struct traits<attribute::type::d> { \
  typedef uint32::decoder decoding_type; \
  decoding_type decode(const uint8_t*, const uint8_t* data, \
      size_t data_len) { \
    return decoding_type(data, data_len); \
  } \
};

#define MESSAGE_ATTRIBUTE_UINT64(d, a) \
template<> \
struct traits<attribute::type::d> { \
  typedef uint64::decoder decoding_type; \
  decoding_type decode(const uint8_t*, const uint8_t* data, \
      size_t data_len) { \
    return decoding_type(data, data_len); \
  } \
};

#include <message/attribute/attributes_template.hpp>

#undef MESSAGE_ATTRIBUTE_SPECIAL
#undef MESSAGE_ATTRIBUTE_EMPTY
#undef MESSAGE_ATTRIBUTE_DATA
#undef MESSAGE_ATTRIBUTE_STRING
#undef MESSAGE_ATTRIBUTE_SOCKADDR
#undef MESSAGE_ATTRIBUTE_XOR_SOCKADDR
#undef MESSAGE_ATTRIBUTE_UINT8
#undef MESSAGE_ATTRIBUTE_UINT8_PAD
#undef MESSAGE_ATTRIBUTE_UINT16
#undef MESSAGE_ATTRIBUTE_UINT16_PAD
#undef MESSAGE_ATTRIBUTE_UINT32
#undef MESSAGE_ATTRIBUTE_UINT64

template<>
struct traits<attribute::type::unknown_attributes> {
  typedef unknown_attributes::decoder decoding_type;
  decoding_type decode(const uint8_t*, const uint8_t* data, size_t data_len) {
    return decoding_type(data, data_len);
  }
};

template<>
struct traits<attribute::type::fingerprint> {
  typedef fingerprint::decoder decoding_type;
  decoding_type decode(const uint8_t* message_header,
      const uint8_t* data, size_t data_len) {
    return decoding_type(message_header, data, data_len);
  }
};

template<>
struct traits<attribute::type::message_integrity> {
  typedef message_integrity::decoder decoding_type;
  decoding_type decode(const uint8_t* message_header,
      const uint8_t* data, size_t data_len) {
    return decoding_type(message_header, data, data_len);
  }
};

template<>
struct traits<attribute::type::error_code> {
  typedef error_code::decoder decoding_type;
  decoding_type decode(const uint8_t*, const uint8_t* data, size_t data_len) {
    return decoding_type(data, data_len);
  }
};

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_DETAIL_TRAITS_HPP

