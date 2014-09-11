// Copyright (c) 2014, Guilherme Balena Versiani <guibv@yahoo.com>
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MESSAGE_DETAIL_CONFIG_HPP
#define MESSAGE_DETAIL_CONFIG_HPP

#include <boost/asio/detail/config.hpp>

// Forward definitions to BOOST_ASIO
#define MESSAGE_DECL BOOST_ASIO_DECL
#if defined(BOOST_ASIO_HEADER_ONLY)
# define MESSAGE_HEADER_ONLY 1
#endif

#endif // MESSAGE_DETAIL_CONFIG_HPP
