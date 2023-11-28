#pragma once

#include "fintamath/expressions/Expression.hpp"

namespace fintamath {

struct ComparatorOptions {
  bool termsOrderInversed = false;
  bool comparableOrderInversed = false;
};

std::strong_ordering comparator(const ArgumentPtr &lhs, const ArgumentPtr &rhs, ComparatorOptions options = {});

}
