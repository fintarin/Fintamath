#pragma once

#include <type_traits>

#define FINTAMATH_CONVERTIBLE()                                                                                        \
public:                                                                                                                \
  inline static const bool IS_CONVERTIBLE = true;                                                                      \
                                                                                                                       \
private:

#define FINTAMATH_FUNCTION_TYPE_ANY()                                                                                  \
public:                                                                                                                \
  inline static const bool IS_FUNCTION_TYPE_ANY = true;                                                                \
                                                                                                                       \
private:

namespace fintamath {

template <typename T, typename U = bool>
struct IsConvertible : std::false_type {};

template <typename T>
struct IsConvertible<T, decltype((void)T::IS_CONVERTIBLE, true)> : std::true_type {};

template <typename T, typename U = bool>
struct IsFunctionTypeAny : std::false_type {};

template <typename T>
struct IsFunctionTypeAny<T, decltype((void)T::IS_FUNCTION_TYPE_ANY, true)> : std::true_type {};

}
