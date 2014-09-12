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

#include <message/detail/config.hpp>

#include <message/detail/padding.hpp>
#include <cstring>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

varsize::decoder::decoder(const uint8_t* data, size_t data_len)
  : data_(reinterpret_cast<const impl_type*>(data)),
    data_len_(data_len) {
}

const uint8_t *varsize::decoder::data() const {
  return data_->value;
}

size_t varsize::decoder::size() const {
  return data_len_;
}

std::string varsize::decoder::to_string() const {
  return std::string((const char*)data_->value, data_len_);
}

varsize::encoder::encoder(uint8_t* data)
  : data_(reinterpret_cast<impl_type*>(data)) {
}

void varsize::encoder::assign(const uint8_t *data, size_t data_len,
    uint8_t pad) {
  using namespace std; // For memcpy.
  memcpy(data_->value, data, data_len);
  append_padding(data_->value + data_len, data_len, pad);
}

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_DETAIL_IMPL_VARSIZE_HPP

