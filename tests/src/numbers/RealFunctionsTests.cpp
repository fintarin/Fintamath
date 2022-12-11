#include <gtest/gtest.h>

#include "fintamath/numbers/RealFunctions.hpp"

#include "fintamath/exceptions/UndefinedFunctionException.hpp"

using namespace fintamath;

// TODO add all functions from fintamath/numbers/RealFunctions.hpp

TEST(RealFunctionsTests, sqrtTest) {
  EXPECT_EQ(sqrt(Real(4)).toString(), "2");
}
