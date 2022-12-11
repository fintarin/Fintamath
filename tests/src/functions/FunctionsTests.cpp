#include <gtest/gtest.h>

#include "fintamath/functions/Functions.hpp"

#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

// TODO add all functions from fintamath/functions/Functions.hpp

TEST(FunctionsTests, addTest) {
  EXPECT_EQ(add(Variable("a"), -1, Expression("b^2")).toString(), "b^2+a-1");
}
