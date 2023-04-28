#pragma once

#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

Integer abs(const Integer &rhs);

Integer sqrt(const Integer &rhs);

Integer pow(const Integer &lhs, uint64_t rhs);

Integer factorial(const Integer &rhs);

Integer factorial(const Integer &rhs, size_t order);

Integer combinations(const Integer &totalNumber, const Integer &choosedNumber);

Integer multinomialCoefficient(const Integer &totalNumber, const vector<Integer> &groupNumbers);

}
