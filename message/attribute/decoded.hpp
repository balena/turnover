// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_ATTRIBUTE_DECODED_HPP
#define MESSAGE_ATTRIBUTE_DECODED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <cstdint>
#include <message/detail/attribute_header.hpp>
#include <message/detail/traits.hpp>

#include <message/detail/push_options.hpp>

namespace stun {
namespace attribute {

class decoded {
  typedef detail::attribute_header attribute_header;
 public:
  decoded(const uint8_t* message_header, const uint8_t* attribute_start)
    : message_header_(message_header), attribute_start_(attribute_start) {}

  uint16_t type() const {
    return attribute_header::decoder(attribute_start_).type();
  }

  decoded next() const {
    return decoded(message_header_, attribute_start_ + attribute_header::size +
        + attribute_header::decoder(attribute_start_).length());
  }

/*
  template<uint16_t T>
  typename detail::traits<T>::decoding_type to() {
    return detail::traits<T>::decode(message_header_, attribute_start_,
        attribute_header::decoder(attribute_start_).length());
  }
*/

  bool operator==(const decoded &rhs) const {
    return attribute_start_ == rhs.attribute_start_;
  }

  bool operator!=(const decoded &rhs) const {
    return attribute_start_ != rhs.attribute_start_;
  }

 private:
  const uint8_t* message_header_;
  const uint8_t* attribute_start_;
};

} // namespace attribute
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_ATTRIBUTE_DECODED_HPP

