#include <gtest/gtest.h>

#include "fintamath/math_objects/relations/operators/arithmetic_operators/unary_arithmetic_operators/UnaryPlus.hpp"

using namespace fintamath;

const auto oper = std::make_unique<UnaryPlus>();

TEST(UnaryMinusTests, getPriorityTest) {
  EXPECT_EQ(oper->getPriority(), 0);
}
