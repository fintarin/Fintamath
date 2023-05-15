#pragma once

#include <algorithm>

#define FINTAMATH_FUNCTION_TYPE_ANY()                                                                                  \
public:                                                                                                                \
  inline static const bool IS_FUNCTION_TYPE_ANY = true;                                                                \
                                                                                                                       \
private:

namespace fintamath {

template <typename T, typename U = bool>
struct IsFunctionTypeAny : std::false_type {};

template <typename T>
struct IsFunctionTypeAny<T, decltype((void)T::IS_FUNCTION_TYPE_ANY, true)> : std::true_type {};

}
