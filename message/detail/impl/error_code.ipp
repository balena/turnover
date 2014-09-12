// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_IMPL_ERROR_CODE_HPP
#define MESSAGE_DETAIL_IMPL_ERROR_CODE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/padding.hpp>
#include <cstring>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

error_code::decoder::decoder(const uint8_t* data, size_t data_len)
  : data_(reinterpret_cast<const impl_type*>(data)),
    data_len_(data_len) {
}

bool error_code::decoder::valid() const {
  return data_len_ >= size_of(0);
}

int error_code::decoder::status_code() const {
  return data_->err_class * 100 + data_->err_code;
}

std::string error_code::decoder::reason_phrase() const {
  std::string result;
  size_t n = data_len_ - (sizeof(data_->unused) + sizeof(data_->err_class)
      + sizeof(data_->err_code));
  if (n > 0)
    result.assign(data_->err_reason, n);
  return result;
}

error_code::encoder::encoder(uint8_t* data)
  : data_(reinterpret_cast<impl_type*>(data)) {
  data_->unused = 0;
}

void error_code::encoder::set_status_code(int status) {
  data_->err_class = status / 100;
  data_->err_code = status % 100;
}

void error_code::encoder::set_reason_phrase(const char* reason_phrase,
    size_t len, uint8_t pad) {
  using namespace std;
  if (len > 0)
    memcpy(data_->err_reason, reason_phrase, len);
  append_padding((uint8_t*)data_->err_reason + len, len, pad);
}

size_t error_code::size_of(size_t reason_len) {
  return sizeof(impl_type) - 1 + reason_len;
}

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_DETAIL_IMPL_ERROR_CODE_HPP

