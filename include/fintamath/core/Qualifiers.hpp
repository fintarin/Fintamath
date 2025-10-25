#pragma once

#include <type_traits>

namespace fintamath::detail {

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

}
