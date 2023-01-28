#include <gtest/gtest.h>

#include "fintamath/core/CoreUtils.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

// TODO: implement tests

TEST(CoreUtilsTests, castUniquePtrTest) {
  EXPECT_NO_THROW(ArithmeticPtr a = cast<IArithmetic>(ONE.clone()));
  EXPECT_FALSE(is<Rational>(ONE.clone()));
}
