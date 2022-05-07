#include <gtest/gtest.h>

#include "fintamath/functions/Operator.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"

using namespace fintamath;

TEST(OperatorTests, getPriorityTests) {
  OperatorPtr o1 = std::make_unique<Add>();
  EXPECT_EQ(o1->getPriority(), 1);

  OperatorPtr o2 = std::make_unique<Mul>();
  EXPECT_EQ(o2->getPriority(), 2);
}
