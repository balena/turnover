// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_IMPL_INT_TYPES_HPP
#define MESSAGE_DETAIL_IMPL_INT_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/byte_order.hpp>
#include <cstring>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

uint8::decoder::decoder(const uint8_t* data, size_t data_len)
  : data_(reinterpret_cast<const impl_type*>(data)),
    data_len_(data_len) {
}

bool uint8::decoder::valid() const {
  return data_len_ == sizeof(impl_type);
}

uint8_t uint8::decoder::value() const {
  return data_->value;
}

uint8::encoder::encoder(uint8_t* data)
  : data_(reinterpret_cast<impl_type*>(data)) {
  using namespace std; // For memset.
  memset(&data_->unused, 0, sizeof(data_->unused));
}

void uint8::encoder::set_value(uint8_t value) {
  data_->value = value;
}


uint8_pad::decoder::decoder(const uint8_t* data, size_t data_len)
  : data_(reinterpret_cast<const impl_type*>(data)),
    data_len_(data_len) {
}

bool uint8_pad::decoder::valid() const {
  return data_len_ == sizeof(data_->value);
}

uint8_t uint8_pad::decoder::value() const {
  return data_->value;
}

uint8_pad::encoder::encoder(uint8_t* data, uint8_t pad)
  : data_(reinterpret_cast<impl_type*>(data)) {
  using namespace std; // For memset.
  memset(&data_->unused, pad, sizeof(data_->unused));
}

void uint8_pad::encoder::set_value(uint8_t value) {
  data_->value = value;
}


uint16::decoder::decoder(const uint8_t* data, size_t data_len)
  : data_(reinterpret_cast<const impl_type*>(data)),
    data_len_(data_len) {
}

bool uint16::decoder::valid() const {
  return data_len_ == sizeof(impl_type);
}

uint16_t uint16::decoder::value() const {
  return network_to_host_short(data_->value);
}

uint16::encoder::encoder(uint8_t* data)
  : data_(reinterpret_cast<impl_type*>(data)) {
  using namespace std; // For memset.
  memset(&data_->unused, 0, sizeof(data_->unused));
}

void uint16::encoder::set_value(uint16_t value) {
  data_->value = host_to_network_short(value);
}


uint16_pad::decoder::decoder(const uint8_t* data, size_t data_len)
  : data_(reinterpret_cast<const impl_type*>(data)),
    data_len_(data_len) {
}

bool uint16_pad::decoder::valid() const {
  return data_len_ == sizeof(data_->value);
}

uint16_t uint16_pad::decoder::value() const {
  return network_to_host_short(data_->value);
}

uint16_pad::encoder::encoder(uint8_t* data, uint8_t pad)
  : data_(reinterpret_cast<impl_type*>(data)) {
  using namespace std; // For memset.
  memset(&data_->unused, pad, sizeof(data_->unused));
}

void uint16_pad::encoder::set_value(uint16_t value) {
  data_->value = host_to_network_short(value);
}


uint32::decoder::decoder(const uint8_t* data, size_t data_len)
  : data_(reinterpret_cast<const impl_type*>(data)),
    data_len_(data_len) {
}

bool uint32::decoder::valid() const {
  return data_len_ == sizeof(impl_type);
}

uint32_t uint32::decoder::value() const {
  return network_to_host_long(data_->value);
}

uint32::encoder::encoder(uint8_t* data)
  : data_(reinterpret_cast<impl_type*>(data)) {
}

void uint32::encoder::set_value(uint32_t value) {
  data_->value = host_to_network_long(value);
}


uint64::decoder::decoder(const uint8_t* data, size_t data_len)
  : data_(reinterpret_cast<const impl_type*>(data)),
    data_len_(data_len) {
}

bool uint64::decoder::valid() const {
  return data_len_ == sizeof(impl_type);
}

uint64_t uint64::decoder::value() const {
  return network_to_host_long_long(data_->value);
}

uint64::encoder::encoder(uint8_t* data)
  : data_(reinterpret_cast<impl_type*>(data)) {
}

void uint64::encoder::set_value(uint64_t value) {
  data_->value = host_to_network_long_long(value);
}

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_DETAIL_IMPL_INT_TYPES_HPP

