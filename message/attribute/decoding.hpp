// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_ATTRIBUTE_DECODING_HPP
#define MESSAGE_ATTRIBUTE_DECODING_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/traits.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace attribute {
namespace decoding {

#define MESSAGE_ATTRIBUTE_DEF(d, a) \
typedef detail::traits<attribute::type::d>::decoding_type d;
#include <message/attribute/attributes_template.hpp>
#undef MESSAGE_ATTRIBUTE_DEF

} // namespace decoding
} // namespace attribute
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_ATTRIBUTE_DECODING_HPP

