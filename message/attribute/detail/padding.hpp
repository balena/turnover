// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_ATTRIBUTE_DETAIL_PADDING_HPP
#define MESSAGE_ATTRIBUTE_DETAIL_PADDING_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <cstring> // for size_t
#include <cstdint>

#include <message/detail/push_options.hpp>

namespace stun {
namespace attribute {
namespace detail {

MESSAGE_DECL void append_padding(uint8_t *p, size_t n, uint8_t pad);

} // namespace detail
} // namespace attribute
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/attribute/detail/impl/padding.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_ATTRIBUTE_DETAIL_PADDING_HPP

