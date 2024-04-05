#pragma once

#include <concepts>
#include <functional>

namespace fintamath {

template <typename From, typename To>
concept ConvertibleToAndNotSameAs = std::convertible_to<From, To> && !std::same_as<From, To>;

template <typename T>
concept TupleLike = requires {
  std::tuple_size<T>::value;
};

template <typename T>
concept Hashable = requires(const T &v) {
  std::hash<T>{}(v);
};

template <typename Number, typename Function>
void repeat(const Number &num, Function &&func) {
  for (Number i = 0; i < num; ++i) {
    func();
  }
}

}
