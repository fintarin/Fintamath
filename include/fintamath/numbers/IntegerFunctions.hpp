#pragma once

#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

Integer abs(const Integer &rhs);

Integer sqrt(const Integer &rhs);

Integer pow(const Integer &lhs, uint64_t rhs);

Integer factorial(const Integer &rhs);

Integer factorial(const Integer &rhs, int64_t order);

}
