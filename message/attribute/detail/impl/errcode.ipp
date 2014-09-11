// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_ATTRIBUTE_DETAIL_IMPL_ERRCODE_HPP
#define MESSAGE_ATTRIBUTE_DETAIL_IMPL_ERRCODE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/attribute/detail/padding.hpp>
#include <cstring>

#include <message/detail/push_options.hpp>

namespace stun {
namespace attribute {
namespace detail {

errcode::decoder::decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr)
  : p_((impl_type*)attr_hdr),
    attribute_base::decoder(msg_hdr, attr_hdr) {
}

bool errcode::decoder::valid() const {
  return length() >= sizeof(p_->unused) + sizeof(p_->err_class) +
      sizeof(p_->err_code);
}

int errcode::decoder::error_class() const {
  return p_->err_class;
}

int errcode::decoder::error_code() const {
  return p_->err_code;
}

std::string errcode::decoder::reason_phrase() const {
  std::string result;
  size_t n = length() - attribute_base::size + sizeof(p_->unused) +
      sizeof(p_->err_class) + sizeof(p_->err_code);
  if (n > 0)
    result.assign(p_->err_reason, n);
  return result;
}

errcode::encoder::encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr)
  : p_((impl_type*)attr_hdr),
    attribute_base::encoder(msg_hdr, attr_hdr) {
  p_->unused = 0;
}

void errcode::encoder::set_status_code(int status) {
  p_->err_class = status / 100;
  p_->err_code = status % 100;
}

void errcode::encoder::set_reason_phrase(const char* reason_phrase,
    size_t len, uint8_t pad) {
  using namespace std;
  if (len > 0)
    memcpy(p_->err_reason, reason_phrase, len);
  append_padding((uint8_t*)p_->err_reason + len, len, pad);
  set_length(sizeof(p_->unused) + sizeof(p_->err_class) +
      sizeof(p_->err_code) + len);
}

} // namespace detail
} // namespace attribute
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_ATTRIBUTE_DETAIL_IMPL_ERRCODE_HPP

