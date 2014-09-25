/* Copyright (c) 2014 Guilherme Balena Versiani.
 *
 * I dedicate any and all copyright interest in this software to the
 * public domain. I make this dedication for the benefit of the public at
 * large and to the detriment of my heirs and successors. I intend this
 * dedication to be an overt act of relinquishment in perpetuity of all
 * present and future rights to this software under copyright law.
 */

#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <message/detail/crypto/md5.hpp>
#include <gtest/gtest.h>

using namespace stun::detail::crypto;

namespace {

std::string digest_to_hex(const md5::bytes_type& bytes) {
  std::ostringstream out;
  for (size_t i = 0; i < bytes.size(); i++) {
    out << std::setfill('0')
        << std::setw(2)
        << std::hex
        << (int)bytes[i];
  }
  return out.str();
}

::testing::AssertionResult IsEqual(const char *test_data,
                                   const md5::bytes_type& bytes,
                                   const char *test_result) {
  std::string output = digest_to_hex(bytes);
  if (output == test_result) {
    return ::testing::AssertionSuccess();
  } else {
    return ::testing::AssertionFailure()
        << "hash of \"" << test_data << "\" incorrect:\n"
        << "\t" << output << " returned\n"
        << "\t" << test_result << " is correct\n";
  }
}

} // empty namespace

TEST(Md5Hash, TestVectors) {
  struct {
    const char *input;
    const char *digest;
  } test[] = {
    { "",
      "d41d8cd98f00b204e9800998ecf8427e" },
    { "a",
      "0cc175b9c0f1b6a831c399e269772661" },
    { "abc",
      "900150983cd24fb0d6963f7d28e17f72" },
    { "message digest",
      "f96b697d7cb7938d525a2f31aaf161d0" },
    { "abcdefghijklmnopqrstuvwxyz",
      "c3fcd3d76192e4007dfb496cca67e13b" },
  };
  for (int k = 0; k < sizeof(test)/sizeof(test[0]); k++){
    md5 ctx;
    ctx.update(test[k].input, strlen(test[k].input));
    EXPECT_TRUE(IsEqual(test[k].input, ctx.to_bytes(), test[k].digest));
  }
}
