#pragma once

#include <concepts>
#include <functional>

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

template <typename... Args>
struct Overload : Args... {
  using Args::operator()...;
};

template <typename T>
using RemoveQualifiers = std::remove_cvref_t<std::remove_pointer_t<T>>;

template <typename From, typename To>
struct CopyQualifiersFromTo {
  using Type = RemoveQualifiers<To>;
};

template <typename From, typename To>
struct CopyQualifiersFromTo<const From, To> {
  using Type = const RemoveQualifiers<To>;
};

template <typename From, typename To>
struct CopyQualifiersFromTo<From &, To> {
  using Type = RemoveQualifiers<To> &;
};

template <typename From, typename To>
struct CopyQualifiersFromTo<From &&, To> {
  using Type = RemoveQualifiers<To> &&;
};

template <typename From, typename To>
struct CopyQualifiersFromTo<const From &, To> {
  using Type = const RemoveQualifiers<To> &;
};

template <typename From, typename To>
struct CopyQualifiersFromTo<const From &&, To> {
  using Type = const RemoveQualifiers<To> &&;
};

template <typename From, typename To>
struct CopyQualifiersFromTo<From *, To> {
  using Type = RemoveQualifiers<To> *;
};

template <typename From, typename To>
struct CopyQualifiersFromTo<const From *, To> {
  using Type = const RemoveQualifiers<To> *;
};

template <typename From, typename To>
using CopyQualifiersFromToType = CopyQualifiersFromTo<From, To>::Type;

template <typename Number, typename Function>
void repeat(const Number &num, Function &&func) {
  for (Number i = 0; i < num; ++i) {
    std::forward<Function>(func)();
  }
}

}
