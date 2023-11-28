#pragma once

#include "fintamath/expressions/Expression.hpp"

namespace fintamath {

struct ComparatorOptions {
  bool constantOrderInversed = false;
  bool comparableOrderInversed = false;
};

std::strong_ordering compare(const ArgumentPtr &lhs, const ArgumentPtr &rhs, ComparatorOptions options = {});

}
