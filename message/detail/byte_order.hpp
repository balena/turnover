// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_BYTE_ORDER_HPP
#define MESSAGE_DETAIL_BYTE_ORDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <cstdint>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

MESSAGE_DECL uint32_t network_to_host_long(uint32_t value);

MESSAGE_DECL uint32_t host_to_network_long(uint32_t value);

MESSAGE_DECL uint16_t network_to_host_short(uint16_t value);

MESSAGE_DECL uint16_t host_to_network_short(uint16_t value);

MESSAGE_DECL uint64_t network_to_host_long_long(uint64_t value);

MESSAGE_DECL uint64_t host_to_network_long_long(uint64_t value);

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#if defined(MESSAGE_HEADER_ONLY)
#include <message/detail/impl/byte_order.ipp>
#endif // defined(MESSAGE_HEADER_ONLY)

#endif // MESSAGE_DETAIL_BYTE_ORDER_HPP
