// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_ATTRIBUTE_DETAIL_EMPTY_HPP
#define MESSAGE_ATTRIBUTE_DETAIL_EMPTY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

struct empty {
  class decoder {
   public:
    decoder(size_t data_len) : data_len_(data_len) {}
    bool valid() const { return data_len_ == 0; }
   private:
    size_t data_len_;
  };
};

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_ATTRIBUTE_DETAIL_EMPTY_HPP

