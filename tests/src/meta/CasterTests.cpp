#include <gtest/gtest.h>

#include "fintamath/helpers/Caster.hpp"

#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;
using namespace fintamath::help;

TEST(CasterTests, castPtrTest) {
  MathObjectPtr obj = std::make_unique<Integer>(1);
  EXPECT_NO_THROW(ArithmeticPtr a = castPtr<IArithmetic>(obj));

  EXPECT_FALSE(castPtr<Rational>(obj));
}
