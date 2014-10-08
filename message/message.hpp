// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <vector>
#include <message/attribute/encoding.hpp>
#include <message/attribute/decoding.hpp>
#include <message/attribute/decoded.hpp>
#include <message/detail/crypto/md5.hpp>
#include <message/detail/uint96_t.hpp>
#include <message/detail/byte_order.hpp>

#include <message/detail/push_options.hpp>

namespace stun {

template<class Allocator>
class basic_message {
 public:
  class iterator {
   public:
    typedef iterator self_type;
    typedef size_t difference_type;
    typedef size_t size_type;
    typedef attribute::decoded value_type;
    typedef attribute::decoded* pointer;
    typedef attribute::decoded& reference;
    typedef std::forward_iterator_tag iterator_category;

    iterator(const uint8_t *msg_hdr, const uint8_t *ptr)
        : attr_(msg_hdr, ptr) {}

    self_type operator++() {
      attr_ = attr_.next();
      return *this;
    }

    self_type operator++(int) {
      self_type it = *this;
      attr_ = attr_.next();
      return it;
    }

    const reference operator*() {
      return attr_;
    }
    const pointer operator->() {
      return &attr_;
    }

    bool operator==(const self_type& rhs) {
      return attr_ == rhs.attr_;
    }
    bool operator!=(const self_type& rhs) {
      return attr_ != rhs.attr_;
    }

   private:
    attribute::decoded attr_;
  };

  enum type {
    binding_request                   = 0x0001, // RFC 5389
    binding_response                  = 0x0101, // RFC 5389
    binding_error_response            = 0x0111, // RFC 5389
    binding_indication                = 0x0011, // RFC 5389
    shared_secret_request             = 0x0002, // RFC 5389
    shared_secret_response            = 0x0102, // RFC 5389
    shared_secret_error_response      = 0x0112, // RFC 5389
    allocate_request                  = 0x0003, // RFC 5766
    allocate_response                 = 0x0103, // RFC 5766
    allocate_error_response           = 0x0113, // RFC 5766
    refresh_request                   = 0x0004, // RFC 5766
    refresh_response                  = 0x0104, // RFC 5766
    refresh_error_response            = 0x0114, // RFC 5766
    send_indication                   = 0x0016, // RFC 5766
    data_indication                   = 0x0017, // RFC 5766
    create_perm_request               = 0x0008, // RFC 5766
    create_perm_response              = 0x0108, // RFC 5766
    create_perm_error_response        = 0x0118, // RFC 5766
    channel_bind_request              = 0x0009, // RFC 5766
    channel_bind_response             = 0x0109, // RFC 5766
    channel_bind_error_response       = 0x0119, // RFC 5766
    connect_request                   = 0x000A, // RFC 6062
    connect_response                  = 0x010A, // RFC 6062
    connect_error_response            = 0x011A, // RFC 6062
    connection_bind_request           = 0x000B, // RFC 6062
    connection_bind_response          = 0x010B, // RFC 6062
    connection_bind_error_response    = 0x011B, // RFC 6062
    connection_attempt_request        = 0x000C, // RFC 6062
    connection_attempt_response       = 0x010C, // RFC 6062
    connection_attempt_error_response = 0x011C, // RFC 6062
  };

  static const size_t header_size = detail::message_header::size;
  static const size_t attribute_header_size = detail::attribute_header::size;
  static const uint32_t magic_value = 0x2112A442ul;

  typedef detail::uint96_t transaction_type;

  basic_message()
      : buffer_(header_size, 0) {}

  basic_message(size_t n)
      : buffer_(n < header_size ? header_size : n, 0) {}

  basic_message(const basic_message& msg)
      : buffer_(msg.buffer_) {}

  basic_message(const uint8_t *buf, size_t buf_len)
      : buffer_(buf, buf_len) {}

  template<class InputIterator>
  basic_message(InputIterator first, InputIterator last)
      : buffer_(first, last) {}

  basic_message(uint16_t type, const transaction_type& tsx_id)
      : buffer_(header_size, 0) {
    using detail::message_header;
    message_header::encoder henc(buffer_.data());
    henc.set_type(type);
    henc.set_magic(magic_value);
    
    message_header::tsx_id_type p;
    p.u96.high = detail::host_to_network_long(tsx_id.high());
    p.u96.low = detail::host_to_network_long_long(tsx_id.low());
    henc.set_tsx_id(p);
  }

  ~basic_message() {}

  void resize(size_t size) { buffer_.resize(size, 0); }
  size_t capacity() const { return buffer_.size(); }

  uint8_t *data() { return buffer_.data(); }
  const uint8_t *data() const { return buffer_.data(); }

  size_t size() const {
    using detail::message_header;
    message_header::decoder hdec(buffer_.data());
    return message_header::size + hdec.length();
  }

  bool verify() const {
    // TODO
    return false;
    //return stun_msg_verify(hdr(), capacity()) == 0 ? false : true;
  }

  uint16_t type() const {
    using detail::message_header;
    message_header::decoder hdec(buffer_.data());
    return hdec.type();
  }

  template<typename AttributeType>
  void push_back(const AttributeType &attr) {
    using detail::message_header;
    using detail::attribute_header;
    size_t attribute_size = (attr.size()+3) & (~3);
    buffer_.resize(size() + attribute_header_size + attribute_size);
    message_header::encoder henc(buffer_.data());
    message_header::decoder hdec(buffer_.data());
    uint8_t *end = buffer_.data() + header_size + hdec.length();
    henc.set_length(hdec.length() + attribute_header::size + attribute_size);
    attribute_header::encoder aenc(end);
    aenc.set_length(attr.size());
    aenc.set_type(attr.type());
    attr.append(buffer_.data(), end + attribute_header_size);
  }

  iterator begin() const {
    return iterator(buffer_.data(),
        buffer_.data() + detail::message_header::size);
  }

  iterator end() const {
    return iterator(buffer_.data(),
        buffer_.data() + detail::message_header::size
        + detail::message_header::decoder(buffer_.data()).length());
  }

  static std::string hash_key(const std::string& username,
                              const std::string& realm,
                              const std::string& password) {
    using stun::detail::crypto::md5;
    md5 ctx;
    ctx.update(username.data(), username.size());
    ctx.update(":", 1);
    ctx.update(realm.data(), realm.size());
    ctx.update(":", 1);
    ctx.update(password.data(), password.size());

    std::string result;
    md5::bytes_type digest(ctx.to_bytes());
    result.resize(digest.size());
    std::copy(digest.begin(), digest.end(), result.begin());
    return result;
  }

 private:
  std::vector<uint8_t, Allocator> buffer_;
};

template<class Allocator>
inline basic_message<Allocator> &operator << (basic_message<Allocator> &msg,
    const attribute::bits::empty &attr) {
  msg.push_back(attr);
  return msg;
}

template<class Allocator, class AddressType>
inline basic_message<Allocator> &operator << (basic_message<Allocator> &msg,
    const attribute::bits::basic_endpoint<AddressType> &attr) {
  msg.push_back(attr);
  return msg;
}

template<class Allocator, typename char_type>
inline basic_message<Allocator> &operator << (basic_message<Allocator> &msg,
    const attribute::bits::varsize<char_type> &attr) {
  msg.push_back(attr);
  return msg;
}

template<class Allocator, typename ValueType>
inline basic_message<Allocator> &operator << (basic_message<Allocator> &msg,
    const attribute::bits::basic_uint<ValueType> &attr) {
  msg.push_back(attr);
  return msg;
}

template<class Allocator, typename ValueType>
inline basic_message<Allocator> &operator << (basic_message<Allocator> &msg,
    const attribute::bits::basic_uint_pad<ValueType> &attr) {
  msg.push_back(attr);
  return msg;
}

template<class Allocator>
inline basic_message<Allocator> &operator << (basic_message<Allocator> &msg,
    const attribute::bits::error_code &attr) {
  msg.push_back(attr);
  return msg;
}

template<class Allocator>
inline basic_message<Allocator> &operator << (basic_message<Allocator> &msg,
    const attribute::bits::unknown_attributes &attr) {
  msg.push_back(attr);
  return msg;
}

template<class Allocator>
inline basic_message<Allocator> &operator << (basic_message<Allocator> &msg,
    const attribute::bits::message_integrity &attr) {
  msg.push_back(attr);
  return msg;
}

template<class Allocator>
inline basic_message<Allocator> &operator << (basic_message<Allocator> &msg,
    const attribute::bits::fingerprint &attr) {
  msg.push_back(attr);
  return msg;
}

typedef basic_message<std::allocator<uint8_t> > message;

#if 0
class message_piece {
 public:
  typedef message::iterator iterator;

  message_piece()
      : ptr_(NULL), length_(0) {}

  message_piece(const message& msg)
      : ptr_(msg.data()), length_(msg.size()) {}

  message_piece(const uint8_t *buf, size_t buf_len)
      : ptr_(buf), length_(buf_len) {}

  template<class InputIterator>
  message_piece(InputIterator first, InputIterator last)
      : ptr_((last > first) ? &(*first) : NULL),
        length_((last > first) ? (size_t)(last - first) : 0) {}

  ~message_piece() {}

  const uint8_t *data() const { return ptr_; }
  size_t size() const { return length_; }

  bool verify() const {
    return stun_msg_verify(hdr(), length_) == 0 ? false : true;
  }

  uint16_t type() const {
    return stun_msg_type(hdr());
  }

  iterator begin() const {
    return iterator(hdr(),
      reinterpret_cast<const uint8_t*>(stun_msg_next_attr(hdr(), NULL)));
  }

  iterator end() const {
    return iterator(hdr(), NULL);
  }

 private:
  const uint8_t *ptr_;
  size_t length_;

  const stun_msg_hdr *hdr() const {
    return reinterpret_cast<const stun_msg_hdr*>(ptr_);
  }
};
#endif

} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_HPP

