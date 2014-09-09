// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_IMPL_VARSIZE_HPP
#define MESSAGE_DETAIL_IMPL_VARSIZE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <algorithm>

namespace stun {
namespace detail {

string::decoder::decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr)
  : attribute_base::decoder(msg_hdr, attr_hdr),
    p_((const impl_type*)attr_hdr) {
}

std::string string::decoder::to_string() const {
  return std::string((const char*)p_->value, length());
}

string::encoder::encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr)
  : attribute_base::encoder(msg_hdr, attr_hdr),
    p_((impl_type*)attr_hdr) {
}

template<typename Iter>
void string::encoder::set_value(Iter first, Iter last) {
  std::copy(first, last, &p_->value[0]);
}

void string::encoder::set_value(const std::string& value) {
  const uint8_t* begin = (const uint8_t*)value.data();
  const uint8_t* end = begin + value.length();
  set_value(begin, end);
}


data::decoder::decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr)
  : attribute_base::decoder(msg_hdr, attr_hdr),
    p_((const impl_type*)attr_hdr) {
}

const uint8_t *data::decoder::data() const {
  return p_->value;
}

size_t data::decoder::size() const {
  return length();
}

data::encoder::encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr)
  : attribute_base::encoder(msg_hdr, attr_hdr),
    p_((impl_type*)attr_hdr) {
}

template<typename Iter>
void data::encoder::set_value(Iter first, Iter last) {
  std::copy(first, last, &p_->value[0]);  
}

void data::encoder::set_value(const uint8_t* data, size_t data_len) {
  set_value(data, data + data_len);
}

} // namespace detail
} // namespace stun

#endif // MESSAGE_DETAIL_IMPL_VARSIZE_HPP

