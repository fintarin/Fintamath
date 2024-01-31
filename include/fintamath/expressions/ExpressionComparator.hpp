#pragma once

#include "fintamath/functions/FunctionArguments.hpp"

namespace fintamath {

struct ComparatorOptions final {
  bool constantGreaterThanVariable = false;
  bool comparableOrderInversed = false;
};

std::strong_ordering compare(ArgumentPtr lhs, ArgumentPtr rhs, ComparatorOptions options = {});

}
