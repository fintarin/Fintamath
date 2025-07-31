#pragma once

#include <concepts>
#include <functional>
#include <utility>

namespace fintamath::detail {

template <typename From, typename To>
concept ConvertibleToAndNotSameAs = std::convertible_to<From, To> && !std::same_as<From, To>;

template <typename T>
concept TupleLike = requires {
  std::tuple_size<T>::value;
};

template <typename T>
concept Hashable = requires(T v) {
  std::hash<T>{}(v);
};

}
