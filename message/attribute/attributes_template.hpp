// Copyright (c) 2014 Guilherme Balena Versiani.
//
// I dedicate any and all copyright interest in this software to the
// public domain. I make this dedication for the benefit of the public at
// large and to the detriment of my heirs and successors. I intend this
// dedication to be an overt act of relinquishment in perpetuity of all
// present and future rights to this software under copyright law.

// Note: this header is a header template and must NOT have multiple-inclusion
// protection.

// STUN attributes are all of the following types:
//
// - MESSAGE_ATTRIBUTE_DATA(d, a)
// - MESSAGE_ATTRIBUTE_EMPTY(d, a)
// - MESSAGE_ATTRIBUTE_SOCKADDR(d, a)
// - MESSAGE_ATTRIBUTE_XOR_SOCKADDR(d, a)
// - MESSAGE_ATTRIBUTE_SPECIAL(d, a)
// - MESSAGE_ATTRIBUTE_STRING(d, a)
// - MESSAGE_ATTRIBUTE_UINT8(d, a)
// - MESSAGE_ATTRIBUTE_UINT8_PAD(d, a)
// - MESSAGE_ATTRIBUTE_UINT16(d, a)
// - MESSAGE_ATTRIBUTE_UINT16_PAD(d, a)
// - MESSAGE_ATTRIBUTE_UINT32(d, a)
// - MESSAGE_ATTRIBUTE_UINT64(d, a)

// The following macro is handy when defining generic statements
#ifdef MESSAGE_ATTRIBUTE_DEF
#define MESSAGE_ATTRIBUTE_EMPTY(d, a) MESSAGE_ATTRIBUTE_DEF(d, a)
#define MESSAGE_ATTRIBUTE_DATA(d, a) MESSAGE_ATTRIBUTE_DEF(d, a)
#define MESSAGE_ATTRIBUTE_SOCKADDR(d, a) MESSAGE_ATTRIBUTE_DEF(d, a)
#define MESSAGE_ATTRIBUTE_XOR_SOCKADDR(d, a) MESSAGE_ATTRIBUTE_DEF(d, a)
#define MESSAGE_ATTRIBUTE_SPECIAL(d, a) MESSAGE_ATTRIBUTE_DEF(d, a)
#define MESSAGE_ATTRIBUTE_STRING(d, a) MESSAGE_ATTRIBUTE_DEF(d, a)
#define MESSAGE_ATTRIBUTE_UINT8(d, a) MESSAGE_ATTRIBUTE_DEF(d, a)
#define MESSAGE_ATTRIBUTE_UINT8_PAD(d, a) MESSAGE_ATTRIBUTE_DEF(d, a)
#define MESSAGE_ATTRIBUTE_UINT16(d, a) MESSAGE_ATTRIBUTE_DEF(d, a)
#define MESSAGE_ATTRIBUTE_UINT16_PAD(d, a) MESSAGE_ATTRIBUTE_DEF(d, a)
#define MESSAGE_ATTRIBUTE_UINT32(d, a) MESSAGE_ATTRIBUTE_DEF(d, a)
#define MESSAGE_ATTRIBUTE_UINT64(d, a) MESSAGE_ATTRIBUTE_DEF(d, a)
#endif

// Define the several STUN attributes below:
MESSAGE_ATTRIBUTE_SOCKADDR(mapped_address, 0x0001)
MESSAGE_ATTRIBUTE_SOCKADDR(response_address, 0x0002)
MESSAGE_ATTRIBUTE_UINT32(change_request, 0x0003)
MESSAGE_ATTRIBUTE_SOCKADDR(source_address, 0x0004)
MESSAGE_ATTRIBUTE_SOCKADDR(changed_address, 0x0005)
MESSAGE_ATTRIBUTE_STRING(username, 0x0006)
MESSAGE_ATTRIBUTE_STRING(password, 0x0007)
MESSAGE_ATTRIBUTE_SPECIAL(message_integrity, 0x0008)
MESSAGE_ATTRIBUTE_SPECIAL(error_code, 0x0009)
MESSAGE_ATTRIBUTE_SPECIAL(unknown_attributes, 0x000A)
MESSAGE_ATTRIBUTE_SOCKADDR(reflected_from, 0x000B)
MESSAGE_ATTRIBUTE_UINT32(channel_number, 0x000C)
MESSAGE_ATTRIBUTE_UINT32(lifetime, 0x000D)
MESSAGE_ATTRIBUTE_UINT32(bandwidth, 0x0010)
MESSAGE_ATTRIBUTE_XOR_SOCKADDR(xor_peer_address, 0x0012)
MESSAGE_ATTRIBUTE_DATA(data, 0x0013)
MESSAGE_ATTRIBUTE_STRING(realm, 0x0014)
MESSAGE_ATTRIBUTE_STRING(nonce, 0x0015)
MESSAGE_ATTRIBUTE_XOR_SOCKADDR(xor_relayed_address, 0x0016)
MESSAGE_ATTRIBUTE_UINT8(req_address_family, 0x0017)
MESSAGE_ATTRIBUTE_UINT8_PAD(even_port, 0x0018)
MESSAGE_ATTRIBUTE_UINT32(requested_transport, 0x0019)
MESSAGE_ATTRIBUTE_EMPTY(dont_fragment, 0x001A)
MESSAGE_ATTRIBUTE_XOR_SOCKADDR(xor_mapped_address, 0x0020)
MESSAGE_ATTRIBUTE_UINT32(timer_val, 0x0021)
MESSAGE_ATTRIBUTE_UINT64(reservation_token, 0x0022)
MESSAGE_ATTRIBUTE_UINT32(priority, 0x0024)
MESSAGE_ATTRIBUTE_EMPTY(use_candidate, 0x0025)
MESSAGE_ATTRIBUTE_DATA(padding, 0x0026)
MESSAGE_ATTRIBUTE_UINT16_PAD(response_port, 0x0027)
MESSAGE_ATTRIBUTE_UINT32(connection_id, 0x002A)
MESSAGE_ATTRIBUTE_STRING(software, 0x8022)
MESSAGE_ATTRIBUTE_SOCKADDR(alternate_server, 0x8023)
MESSAGE_ATTRIBUTE_SPECIAL(fingerprint, 0x8028)
MESSAGE_ATTRIBUTE_UINT64(ice_controlled, 0x8029)
MESSAGE_ATTRIBUTE_UINT64(ice_controlling, 0x802A)
MESSAGE_ATTRIBUTE_SOCKADDR(response_origin, 0x802B)
MESSAGE_ATTRIBUTE_SOCKADDR(other_address, 0x802C)

#ifdef MESSAGE_ATTRIBUTE_DEF
#undef MESSAGE_ATTRIBUTE_EMPTY
#undef MESSAGE_ATTRIBUTE_DATA
#undef MESSAGE_ATTRIBUTE_SOCKADDR
#undef MESSAGE_ATTRIBUTE_XOR_SOCKADDR
#undef MESSAGE_ATTRIBUTE_SPECIAL
#undef MESSAGE_ATTRIBUTE_STRING
#undef MESSAGE_ATTRIBUTE_UINT8
#undef MESSAGE_ATTRIBUTE_UINT8_PAD
#undef MESSAGE_ATTRIBUTE_UINT16
#undef MESSAGE_ATTRIBUTE_UINT16_PAD
#undef MESSAGE_ATTRIBUTE_UINT32
#undef MESSAGE_ATTRIBUTE_UINT64
#endif

