// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_ATTRIBUTE_DETAIL_IMPL_VARSIZE_HPP
#define MESSAGE_ATTRIBUTE_DETAIL_IMPL_VARSIZE_HPP

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

varsize::decoder::decoder(const uint8_t* msg_hdr, const uint8_t* attr_hdr)
  : attribute_base::decoder(msg_hdr, attr_hdr),
    p_((const impl_type*)attr_hdr) {
}

const uint8_t *varsize::decoder::data() const {
  return p_->value;
}

size_t varsize::decoder::size() const {
  return length();
}

std::string varsize::decoder::to_string() const {
  return std::string((const char*)p_->value, length());
}

varsize::encoder::encoder(const uint8_t* msg_hdr, uint8_t* attr_hdr)
  : attribute_base::encoder(msg_hdr, attr_hdr),
    p_((impl_type*)attr_hdr) {
}

void varsize::encoder::assign(const uint8_t *data, size_t data_len,
    uint8_t pad) {
  using namespace std; // For memcpy and memset.
  memcpy(p_->value, data, data_len);
  append_padding(p_->value + data_len, data_len, pad);
  set_length(data_len);
}

} // namespace detail
} // namespace attribute
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_ATTRIBUTE_DETAIL_IMPL_VARSIZE_HPP

