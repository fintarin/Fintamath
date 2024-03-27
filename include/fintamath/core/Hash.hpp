#pragma once

#include <functional>
#include <tuple>

#include "fintamath/core/CoreUtils.hpp"

namespace fintamath::detail {

template <class T>
struct Hash;

template <class T>
void hashCombine(size_t &seed, const T &v) noexcept {
  Hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <Hashable T>
struct Hash<T> {
  size_t operator()(const T &v) const noexcept {
    return std::hash<T>{}(v);
  }
};

template <TupleLike T>
struct Hash<T> {
  size_t operator()(const T &v) const noexcept {
    std::size_t seed = 0;
    hashCombineTuple<0>(seed, v);
    return seed;
  }

private:
  template <std::size_t i>
  static void hashCombineTuple(std::size_t &seed, const T &v) noexcept {
    if constexpr (i < std::tuple_size_v<T>) {
      Hash<std::tuple_element_t<i, T>> hasher;
      hashCombine(seed, hasher(std::get<i>(v)));
      hashCombineTuple<i + 1>(seed, v);
    }
  }
};

}
