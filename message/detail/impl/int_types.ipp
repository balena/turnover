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

#include "message/detail/byte_order.hpp"
#include <cstring>

namespace stun {
namespace detail {

uint8::decoder::decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr)
  : attribute_base::decoder(msg_hdr, attr_hdr),
    p_((const impl_type*)attr_hdr) {
}

bool uint8::decoder::valid() const {
  return length() == sizeof(impl_type) - sizeof(attribute_base::impl_type);
}

uint8_t uint8::decoder::value() const {
  return p_->value;
}

uint8::encoder::encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr)
  : attribute_base::encoder(msg_hdr, attr_hdr),
    p_((impl_type*)attr_hdr) {
  using namespace std;
  set_length(sizeof(impl_type) - sizeof(attribute_base::impl_type));
  memset(&p_->unused, 0, sizeof(p_->unused));
}

void uint8::encoder::set_value(uint8_t value) {
  p_->value = value;
}


uint8_pad::decoder::decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr)
  : attribute_base::decoder(msg_hdr, attr_hdr),
    p_((const impl_type*)attr_hdr) {
}

bool uint8_pad::decoder::valid() const {
  return length() == sizeof(p_->value);
}

uint8_t uint8_pad::decoder::value() const {
  return p_->value;
}

uint8_pad::encoder::encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr,
    uint8_t pad)
  : attribute_base::encoder(msg_hdr, attr_hdr),
    p_((impl_type*)attr_hdr) {
  using namespace std;
  set_length(sizeof(p_->value));
  memset(&p_->unused, pad, sizeof(p_->unused));
}

void uint8_pad::encoder::set_value(uint8_t value) {
  p_->value = value;
}


uint16::decoder::decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr)
  : attribute_base::decoder(msg_hdr, attr_hdr),
    p_((const impl_type*)attr_hdr) {
}

bool uint16::decoder::valid() const {
  return length() == sizeof(impl_type) - sizeof(attribute_base::impl_type);
}

uint16_t uint16::decoder::value() const {
  return network_to_host_short(p_->value);
}

uint16::encoder::encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr)
  : attribute_base::encoder(msg_hdr, attr_hdr),
    p_((impl_type*)attr_hdr) {
  using namespace std;
  set_length(sizeof(impl_type) - sizeof(attribute_base::impl_type));
  memset(&p_->unused, 0, sizeof(p_->unused));
}

void uint16::encoder::set_value(uint16_t value) {
  p_->value = host_to_network_short(value);
}


uint16_pad::decoder::decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr)
  : attribute_base::decoder(msg_hdr, attr_hdr),
    p_((const impl_type*)attr_hdr) {
}

bool uint16_pad::decoder::valid() const {
  return length() == sizeof(p_->value);
}

uint16_t uint16_pad::decoder::value() const {
  return network_to_host_short(p_->value);
}

uint16_pad::encoder::encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr,
    uint8_t pad)
  : attribute_base::encoder(msg_hdr, attr_hdr),
    p_((impl_type*)attr_hdr) {
  using namespace std;
  set_length(sizeof(p_->value));
  memset(&p_->unused, pad, sizeof(p_->unused));
}

void uint16_pad::encoder::set_value(uint16_t value) {
  p_->value = host_to_network_short(value);
}


uint32::decoder::decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr)
  : attribute_base::decoder(msg_hdr, attr_hdr),
    p_((const impl_type*)attr_hdr) {
}

bool uint32::decoder::valid() const {
  return length() == sizeof(impl_type) - sizeof(attribute_base::impl_type);
}

uint32_t uint32::decoder::value() const {
  return network_to_host_long(p_->value);
}

uint32::encoder::encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr)
  : attribute_base::encoder(msg_hdr, attr_hdr),
    p_((impl_type*)attr_hdr) {
  using namespace std;
  set_length(sizeof(impl_type) - sizeof(attribute_base::impl_type));
}

void uint32::encoder::set_value(uint32_t value) {
  p_->value = host_to_network_long(value);
}


uint64::decoder::decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr)
  : attribute_base::decoder(msg_hdr, attr_hdr),
    p_((const impl_type*)attr_hdr) {
}

bool uint64::decoder::valid() const {
  return length() == sizeof(impl_type) - sizeof(attribute_base::impl_type);
}

uint64_t uint64::decoder::value() const {
  return network_to_host_long_long(p_->value);
}

uint64::encoder::encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr)
  : attribute_base::encoder(msg_hdr, attr_hdr),
    p_((impl_type*)attr_hdr) {
  using namespace std;
  set_length(sizeof(impl_type) - sizeof(attribute_base::impl_type));
}

void uint64::encoder::set_value(uint64_t value) {
  p_->value = host_to_network_long_long(value);
}

} // namespace detail
} // namespace stun

#endif // MESSAGE_DETAIL_IMPL_INT_TYPES_HPP

