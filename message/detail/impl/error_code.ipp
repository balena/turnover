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

error_code::decoder::decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr)
  : p_((impl_type*)attr_hdr),
    basic_attribute::decoder(msg_hdr, attr_hdr) {
}

bool error_code::decoder::valid() const {
  return length() >= sizeof(p_->unused) + sizeof(p_->err_class) +
      sizeof(p_->err_code);
}

int error_code::decoder::error_class() const {
  return p_->err_class;
}

int error_code::decoder::error_code() const {
  return p_->err_code;
}

std::string error_code::decoder::reason_phrase() const {
  std::string result;
  size_t n = length() - basic_attribute::size + sizeof(p_->unused) +
      sizeof(p_->err_class) + sizeof(p_->err_code);
  if (n > 0)
    result.assign(p_->err_reason, n);
  return result;
}

error_code::encoder::encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr)
  : p_((impl_type*)attr_hdr),
    basic_attribute::encoder(msg_hdr, attr_hdr) {
  p_->unused = 0;
}

void error_code::encoder::set_status_code(int status) {
  p_->err_class = status / 100;
  p_->err_code = status % 100;
}

void error_code::encoder::set_reason_phrase(const char* reason_phrase,
    size_t len, uint8_t pad) {
  using namespace std;
  if (len > 0)
    memcpy(p_->err_reason, reason_phrase, len);
  append_padding((uint8_t*)p_->err_reason + len, len, pad);
  set_length(sizeof(p_->unused) + sizeof(p_->err_class) +
      sizeof(p_->err_code) + len);
}

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_DETAIL_IMPL_ERROR_CODE_HPP

