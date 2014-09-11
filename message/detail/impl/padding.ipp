// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_IMPL_PADDING_IPP
#define MESSAGE_DETAIL_IMPL_PADDING_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

void append_padding(uint8_t *p, size_t n, uint8_t pad) {
  using namespace std; // For memset.
  if ((n & 0x03) > 0) {
    memset(p, pad, 4 - (n & 0x03));
  }
}

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_DETAIL_IMPL_PADDING_HPP

