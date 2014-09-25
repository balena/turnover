// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_ATTRIBUTE_ENCODING_HPP
#define MESSAGE_ATTRIBUTE_ENCODING_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <cstring>

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
namespace attribute {

namespace bits {

struct empty {
  empty(uint16_t type)
      : type_(type) {}
  uint16_t type() const { return type_; }
  size_t size() const { return 0; }
  void append(const uint8_t*, uint8_t*) const {}
  uint16_t type_;
};

template<typename Impl>
struct basic_endpoint {
  typedef typename Impl::address_type address_type;
  basic_endpoint(uint16_t type, const address_type &address, uint16_t port)
      : type_(type), address_(address), port_(port) {}
  uint16_t type() const { return type_; }
  size_t size() const { return Impl::size_of(address_); }
  void append(const uint8_t* msg_hdr, uint8_t* data) const {
    typename Impl::encoder encoder(msg_hdr, data);
    encoder.set_address(address_);
    encoder.set_port(port_);
  }
  uint16_t type_;
  address_type address_;
  uint16_t port_;
};

typedef basic_endpoint<detail::endpoint> endpoint;
typedef basic_endpoint<detail::xor_endpoint> xor_endpoint;

template<typename char_type>
struct varsize {
  varsize(uint16_t type, const char_type *s, size_t len, uint8_t pad)
      : type_(type), s_(s), len_(len), pad_(pad) {}
  uint16_t type() const { return type_; }
  size_t size() const { return len_; }
  void append(const uint8_t*, uint8_t* data) const {
    detail::varsize::encoder encoder(data);
    encoder.assign(reinterpret_cast<const uint8_t*>(s_), len_, pad_);
  }
  uint16_t type_;
  const char_type *s_;
  size_t len_;
  uint8_t pad_;
};

template<typename Impl>
struct basic_uint {
  basic_uint(uint16_t type, typename Impl::value_type value)
      : type_(type), value_(value) {}
  uint16_t type() const { return type_; }
  size_t size() const { return Impl::size; }
  void append(const uint8_t*, uint8_t* data) const {
    typename Impl::encoder encoder(data);
    encoder.set_value(value_);
  }
  uint16_t type_;
  typename Impl::value_type value_;
};

typedef basic_uint<detail::uint8> uint8;
typedef basic_uint<detail::uint16> uint16;
typedef basic_uint<detail::uint32> uint32;
typedef basic_uint<detail::uint64> uint64;

template<typename Impl>
struct basic_uint_pad {
  basic_uint_pad(uint16_t type, typename Impl::value_type value, uint8_t pad)
      : type_(type), value_(value), pad_(pad) {}
  uint16_t type() const { return type_; }
  size_t size() const { return Impl::size; }
  void append(const uint8_t*, uint8_t* data) const {
    typename Impl::encoder encoder(data, pad_);
    encoder.set_value(value_);
  }
  uint16_t type_;
  typename Impl::value_type value_;
  uint8_t pad_;
};

typedef basic_uint_pad<detail::uint8_pad> uint8_pad;
typedef basic_uint_pad<detail::uint16_pad> uint16_pad;

struct error_code {
  error_code(int status_code, const char *reason, uint8_t pad)
      : status_code_(status_code), reason_(reason), pad_(pad) {
    using namespace std;
    reason_len_ = strlen(reason);
  }
  uint16_t type() const { return type::error_code; }
  size_t size() const { return detail::error_code::size_of(reason_len_); }
  void append(const uint8_t*, uint8_t* data) const {
    detail::error_code::encoder encoder(data);
    encoder.set_status_code(status_code_);
    encoder.set_reason_phrase(reason_, reason_len_, pad_);
  }
  int status_code_;
  const char *reason_;
  size_t reason_len_;
  uint8_t pad_;
};

struct unknown_attributes {
  unknown_attributes(const uint16_t *codes, size_t count, uint8_t pad)
      : codes_(codes), count_(count), pad_(pad) {}
  uint16_t type() const { return type::unknown_attributes; }
  size_t size() const { return detail::unknown_attributes::size_of(count_); }
  void append(const uint8_t*, uint8_t* data) const {
    detail::unknown_attributes::encoder encoder(data);
    encoder.assign(codes_, count_);
  }
  const uint16_t *codes_;
  size_t count_;
  uint8_t pad_;
};

struct message_integrity {
  message_integrity(const uint8_t *key, size_t key_len)
      : key_(key), key_len_(key_len) {}
  uint16_t type() const { return type::message_integrity; }
  size_t size() const { return detail::message_integrity::size; }
  void append(const uint8_t* message_header, uint8_t *data) const {
    detail::message_integrity::encoder encoder(message_header, data);
    encoder.sign(key_, key_len_);
  }
  const uint8_t *key_;
  size_t key_len_;
};

struct fingerprint {
  fingerprint() {}
  uint16_t type() const { return type::fingerprint; }
  size_t size() const { return detail::fingerprint::size; }
  void append(const uint8_t* message_header, uint8_t* data) const {
    detail::fingerprint::encoder encoder(message_header, data);
    encoder.sign();
  }
};

} // namespace bits

#define MESSAGE_ATTRIBUTE_SPECIAL(name, x) // defined below

#define MESSAGE_ATTRIBUTE_STRING(name, x) \
bits::varsize<char> name(const char *data, uint8_t pad = 0) { \
  return bits::varsize<char>(type::name, data, strlen(data), pad); \
} \
bits::varsize<char> name(const std::string &s, uint8_t pad = 0) { \
  return bits::varsize<char>(type::name, s.data(), s.size(), pad); \
} \
bits::varsize<char> name(const char *begin, const char *end, \
    uint8_t pad = 0) { \
  return bits::varsize<char>(type::name, begin, end - begin, pad); \
}

#define MESSAGE_ATTRIBUTE_DATA(name, x) \
bits::varsize<uint8_t> name(const uint8_t *data, size_t data_len, \
    uint8_t pad = 0) { \
  return bits::varsize<uint8_t>(type::name, data, data_len, pad); \
} \
bits::varsize<uint8_t> name(const uint8_t *begin, const uint8_t *end, \
    uint8_t pad = 0) { \
  return bits::varsize<uint8_t>(type::name, begin, end - begin, pad); \
}

#define MESSAGE_ATTRIBUTE_SOCKADDR(name, x) \
bits::endpoint name(const boost::asio::ip::address &address, \
    uint16_t port) { \
  return bits::endpoint(type::name, address, port); \
}

#define MESSAGE_ATTRIBUTE_XOR_SOCKADDR(name, x) \
bits::xor_endpoint name(const boost::asio::ip::address &address, \
    uint16_t port) { \
  return bits::xor_endpoint(type::name, address, port); \
}

#define MESSAGE_ATTRIBUTE_EMPTY(name, x) \
bits::empty name() { \
  return bits::empty(type::name); \
}

#define MESSAGE_ATTRIBUTE_UINT8(name, x) \
bits::uint8 name(uint8_t value) { \
  return bits::uint8(type::name, value); \
}

#define MESSAGE_ATTRIBUTE_UINT8_PAD(name, x) \
bits::uint8_pad name(uint8_t value, uint8_t pad = 0) { \
  return bits::uint8_pad(type::name, value, pad); \
}

#define MESSAGE_ATTRIBUTE_UINT16(name, x) \
bits::uint16 name(uint16_t value) { \
  return bits::uint16(type::name, value); \
}

#define MESSAGE_ATTRIBUTE_UINT16_PAD(name, x) \
bits::uint16_pad name(uint16_t value, uint8_t pad = 0) { \
  return bits::uint16_pad(type::name, value, pad); \
}

#define MESSAGE_ATTRIBUTE_UINT32(name, x) \
bits::uint32 name(uint32_t value) { \
  return bits::uint32(type::name, value); \
}

#define MESSAGE_ATTRIBUTE_UINT64(name, x) \
bits::uint64 name(uint64_t value) { \
  return bits::uint64(type::name, value); \
}

#include <message/attribute/attributes_template.hpp>

#undef MESSAGE_ATTRIBUTE_SPECIAL
#undef MESSAGE_ATTRIBUTE_STRING
#undef MESSAGE_ATTRIBUTE_DATA
#undef MESSAGE_ATTRIBUTE_SOCKADDR
#undef MESSAGE_ATTRIBUTE_XOR_SOCKADDR
#undef MESSAGE_ATTRIBUTE_EMPTY
#undef MESSAGE_ATTRIBUTE_UINT8
#undef MESSAGE_ATTRIBUTE_UINT8_PAD
#undef MESSAGE_ATTRIBUTE_UINT16
#undef MESSAGE_ATTRIBUTE_UINT16_PAD
#undef MESSAGE_ATTRIBUTE_UINT32
#undef MESSAGE_ATTRIBUTE_UINT64

// Special attributes define below:

bits::error_code error_code(int status_code, const char *reason,
    uint8_t pad = 0) {
  return bits::error_code(status_code, reason, pad);
}

bits::unknown_attributes unknown_attributes(const uint16_t *data, size_t count,
    uint8_t pad = 0) {
  return bits::unknown_attributes(data, count, pad);
}

bits::unknown_attributes unknown_attributes(const uint16_t *begin,
    const uint16_t *end, uint8_t pad = 0) {
  return bits::unknown_attributes(begin, end - begin, pad);
}

bits::message_integrity message_integrity(const char *key) {
  return bits::message_integrity(reinterpret_cast<const uint8_t*>(key),
      strlen(key));
}

bits::message_integrity message_integrity(const std::string &key) {
  return bits::message_integrity(reinterpret_cast<const uint8_t*>(key.c_str()),
      key.size());
}

bits::message_integrity message_integrity(const uint8_t *key, size_t key_len) {
  return bits::message_integrity(key, key_len);
}

bits::fingerprint fingerprint() {
  return bits::fingerprint();
}

} // namespace attribute
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_ATTRIBUTE_ENCODING_HPP

