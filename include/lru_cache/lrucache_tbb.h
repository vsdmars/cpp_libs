/**
 * AtsPluginUtils is used inside Linkedin, retain here for compatible usage.
 *
 */

#pragma once

#include <ats_type.h>

// intel TBB header
#include <tbb/concurrent_hash_map.h>
// Boost lib header
#include <boost/functional/hash.hpp>

namespace tbb {
using IpAddress = AtsPluginUtils::IpAddress;

//  twang_mix64
//
//  Thomas Wang 64 bit mix hash function.
//  https://github.com/facebook/folly/blob/99fbca1df19fdd21f1b831cad6f50ece94573675/folly/hash/Hash.h#L87
constexpr uint64_t twang_mix64(uint64_t key) noexcept {
  key = (~key) + (key << 21);  // key *= (1 << 21) - 1; key -= 1;
  key = key ^ (key >> 24);
  key = key + (key << 3) + (key << 8);  // key *= 1 + (1 << 3) + (1 << 8)
  key = key ^ (key >> 14);
  key = key + (key << 2) + (key << 4);  // key *= 1 + (1 << 2) + (1 << 4)
  key = key ^ (key >> 28);
  key = key + (key << 31);  // key *= 1 + (1 << 31)
  return key;
}

/**
 * tbb_hash_compare<IpAddress> is a fully specialized type with AtsPluginUtils::IpAddress
 * for tbb::tbb_hash_compare used as hash function object type used by tbb::concurrent_hash_map
 * to support AtsPluginUtils::IpAddress as key.
 *
 * Official document:
 * https://spec.oneapi.com/versions/latest/elements/oneTBB/source/named_requirements/containers/hash_compare.html
 *
 */
template <>
struct tbb_hash_compare<IpAddress> {
  static std::size_t hash(const IpAddress& k) {
    size_t seed = twang_mix64(k.base.sa_family);

    switch (k.base.sa_family) {
      case AF_INET:
        boost::hash_combine(seed, twang_mix64(k.v4.sin_addr.s_addr));
        break;
      case AF_INET6: {
        // The IPv6 address is 16 bytes long.
        // Combine it in blocks of sizeof(size_t) bytes each.
        static_assert(sizeof(struct in6_addr) % sizeof(size_t) == 0);

        const size_t* p = reinterpret_cast<const size_t*>(k.v6.sin6_addr.s6_addr);
        constexpr auto in6_addr_size = sizeof(struct in6_addr);

        for (auto amtHashed = 0UL; amtHashed < in6_addr_size; amtHashed += sizeof(*p), ++p) {
          boost::hash_combine(seed, twang_mix64(*p));
        }
      }
    }

    return seed;
  }

  static bool equal(const IpAddress& k1, const IpAddress& k2) { return k1 == k2; }
};

}  // namespace tbb
