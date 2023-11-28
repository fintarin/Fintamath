#pragma once

#include "fintamath/expressions/Expression.hpp"

namespace fintamath {

struct ComparatorOptions {
  bool termsOrderInversed = false;
  bool comparableOrderInversed = false;
};

int comparator(const ArgumentPtr &lhs, const ArgumentPtr &rhs, ComparatorOptions options = {});

}
