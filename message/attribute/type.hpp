// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_ATTRIBUTE_TYPE_HPP
#define MESSAGE_ATTRIBUTE_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <cstdint>

namespace stun {
namespace attribute {

struct type {
#define MESSAGE_ATTRIBUTE_DEF(d, a) static const uint16_t d = a;
#include "message/attribute/attributes_template.hpp"
#undef MESSAGE_ATTRIBUTE_DEF
};

} // namespace attribute
} // namespace stun

#endif // MESSAGE_ATTRIBUTE_TYPE_HPP

