#pragma once

#include <concepts>
#include <functional>
#include <ranges>

namespace fintamath {

namespace stdr = std::ranges;
namespace stdv = std::views;

template <typename From, typename To>
concept ConvertibleToAndNotSameAs = std::convertible_to<From, To> && !std::same_as<From, To>;

template <class T>
concept TupleLike = requires {
  std::tuple_size<T>::value;
};

template <class T>
concept Hashable = requires(const T &v) {
  std::hash<T>{}(v);
};

}
