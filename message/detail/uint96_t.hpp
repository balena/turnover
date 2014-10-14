// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_UINT96_T_HPP
#define MESSAGE_DETAIL_UINT96_T_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <message/detail/config.hpp>

#include <cstdint>
#include <string>
#include <iostream>

#include <message/detail/push_options.hpp>

namespace stun {
namespace detail {

class uint96_t {
 public:
  uint96_t() : high_(0), low_(0) {}

  template<typename T>
  uint96_t(const T& rhs) : high_(0), low_((uint64_t)rhs) {}

  template<typename T, typename V>
  uint96_t(const T& high, const V& low)
    : high_((uint32_t)high), low_((uint64_t)low) {}

  template<typename T>
  uint96_t operator=(const T& rhs) {
    high_ = 0;
    low_ = (uint64_t)rhs;
    return *this;
  }

  uint96_t operator&(const uint96_t& rhs) const {
    return uint96_t(high_ & rhs.high_, low_ & rhs.low_);
  }
  uint96_t operator|(const uint96_t& rhs) const {
    return uint96_t(high_ | rhs.high_, low_ | rhs.low_);
  }
  uint96_t operator^(const uint96_t & rhs) const {
    return uint96_t(high_ ^ rhs.high_, low_ ^ rhs.low_);
  }
  uint96_t operator&=(const uint96_t & rhs) {
    high_ &= rhs.high_;
    low_ &= rhs.low_;
    return *this;
  }
  uint96_t operator|=(const uint96_t & rhs)  {
    high_ |= rhs.high_;
    low_ |= rhs.low_;
    return *this;
  }
  uint96_t operator^=(const uint96_t & rhs) {
    high_ ^= rhs.high_;
    low_ ^= rhs.low_;
    return *this;
  }
  uint96_t operator~() const {
    return uint96_t(~high_, ~low_);
  }

  uint96_t operator<<(unsigned int rhs) const {
    return uint96_t((high_ << rhs) + (low_ >> (64 - rhs)), low_ << rhs);
  }
  uint96_t operator>>(unsigned int rhs) const {
    return uint96_t(high_ >> rhs, (high_ << (64 - rhs)) + (low_ >> rhs));
  }

  uint96_t operator<<=(unsigned int rhs) {
    *this = *this << rhs;
    return *this;
  }
  uint96_t operator>>=(unsigned int rhs) {
    *this = *this >> rhs;
    return *this;
  }

  bool operator==(const uint96_t& rhs) const {
    return high_ == rhs.high_ && low_ == rhs.low_;
  }
  bool operator!=(const uint96_t& rhs) const {
    return high_ != rhs.high_ || low_ != rhs.low_;
  }

  bool operator<(const uint96_t& rhs) const {
    return (high_ == rhs.high_ && low_ < rhs.low_) || (high_ < rhs.high_);
  }
  bool operator>(const uint96_t& rhs) const {
    return (high_ == rhs.high_ && low_ > rhs.low_) || (high_ > rhs.high_);
  }

  bool operator<=(const uint96_t& rhs) const {
    return *this == rhs || *this < rhs;
  }
  bool operator>=(const uint96_t& rhs) const {
    return *this == rhs || *this > rhs;
  }

  uint96_t operator+=(const uint96_t& rhs) {
    high_ += rhs.high_;
    low_ += rhs.low_;
    if (low_ < rhs.low_) // overflow
      high_ += 1;
    return *this;
  }
  uint96_t operator+(const uint96_t& rhs) const {
    uint96_t result(*this);
    return result += rhs;
  }

  uint96_t operator-=(const uint96_t& rhs) {
    high_ -= rhs.high_;
    low_ -= rhs.low_;
    if (low_ > rhs.low_) // overflow
      high_ -= 1;
    return *this;
  }
  uint96_t operator-(const uint96_t& rhs) const {
    uint96_t result(*this);
    return result -= rhs;
  }

  uint96_t operator++() {
    *this += uint96_t(1);
    return *this;
  }
  uint96_t operator++(int) {
    uint96_t temp(*this);
    ++*this;
    return temp;
  }

  uint96_t operator--() {
    *this -= uint96_t(1);
    return *this;
  }
  uint96_t operator--(int) {
    uint96_t temp(*this);
    --*this;
    return temp;
  }

  uint96_t operator*(const uint96_t & rhs) const{
    // split values into 3 32-bit parts
    uint64_t top[3] = {high_, low_ >> 32, low_ & 0xffffffff};
    uint64_t bottom[3] = {rhs.high_, rhs.low_ >> 32, rhs.low_ & 0xffffffff};
    uint64_t products[3][3];

    for (int y = 2; y >= 0; --y) {
      for(int x = 2; x >= 0; --x) {
        products[2 - x][y] = top[x] * bottom[y];
      }
    }

    // initial row
    uint64_t third32 = (products[0][2] & 0xffffffff);
    uint64_t second32 = (products[0][1] & 0xffffffff) + (products[0][2] >> 32);
    uint64_t first32 = (products[0][0] & 0xffffffff) + (products[0][1] >> 32);

    // second row
    second32 += (products[1][2] & 0xffffffff);
    first32 += (products[1][1] & 0xffffffff) + (products[1][2] >> 32);

    // third row
    first32 += (products[2][2] & 0xffffffff);

    // combines the values, taking care of carry over
    return uint96_t(first32, 0)
           + uint96_t(second32 >> 32, second32 << 32)
           + uint96_t(third32);
  }
  uint96_t operator*=(const uint96_t & rhs){
    *this = *this * rhs;
    return *this;
  }

  uint32_t high() const { return high_; }
  uint64_t low() const { return low_; }

  /*
  std::string str(int base = 10, const unsigned int &len = 0) const {
    if ((base < 2) || (base > 16))
      throw std::invalid_argument("base must be in th range 2-16");
    std::string out = "";
    if (!(*this))
      out = "0";
    else {
      std::pair<uint96_t, uint96_t> qr(*this, 0);
      do {
        qr = divmod(qr.first, base);
        out = "0123456789abcdef"[(uint8_t)qr.second] + out;
      } while (qr.first);
    }
    if (out.size() < len)
      out = std::string(len - out.size(), '0') + out;
    return out;
  }*/

 private:
  uint32_t high_;
  uint64_t low_;
};
/*
inline std::ostream & operator<<(std::ostream& os, const uint96_t & rhs) {
  if (os.flags() & os.oct)
    os << rhs.str(8);
  else if (os.flags() & os.dec)
    os << rhs.str(10);
  else if (os.flags() & os.hex)
    os << rhs.str(16);
  return os;
}*/

} // namespace detail
} // namespace stun

#include <message/detail/pop_options.hpp>

#endif // MESSAGE_DETAIL_UINT96_T_HPP

