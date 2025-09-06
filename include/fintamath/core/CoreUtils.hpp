#pragma once

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

template <typename T>
concept IsSmartPointer = requires(T v) {
  v.operator->();
  *v;
  v.get();
};

template <typename T>
using EqualTo = std::equal_to<T>;

template <typename Res, typename T>
struct AddTo {
  constexpr Res operator()(const T &lhs, const T &rhs) const { return lhs + rhs; }
};

template <typename Number, typename Callback>
constexpr void repeat(const Number &num, Callback &&callback) {
  for (Number i = 0; i < num; ++i) {
    std::forward<Callback>(callback)();
  }
}

template <typename Container, typename Comparator = std::equal_to<typename Container::value_type>>
constexpr bool areContainersEqual(const Container &lhs, const Container &rhs, const Comparator &comp = {}) noexcept {
  if (lhs.size() != rhs.size()) {
    return false;
  }

  auto lhsIter = lhs.begin();
  auto rhsIter = rhs.begin();

  for (; lhsIter != lhs.end(); ++lhsIter, ++rhsIter) {
    if (!comp(*lhsIter, *rhsIter)) {
      return false;
    }
  }

  return true;
}

}
