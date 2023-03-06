#pragma once

#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

Integer abs(const Integer &rhs);

Integer sqrt(const Integer &rhs);

Integer pow(const Integer &lhs, uint64_t rhs);

Integer factorial(const Integer &rhs);

Integer factorial(const Integer &rhs, int64_t order);

Integer combinations(const Integer &n, const Integer &k);

Integer split(const Integer &n, const std::vector<Integer> &k_values);

}
