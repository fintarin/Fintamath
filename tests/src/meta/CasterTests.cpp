#include <gtest/gtest.h>

#include "fintamath/meta/Caster.hpp"

#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;
using namespace fintamath::meta;

TEST(CasterTests, castPtrTest) {
  MathObjectPtr obj = std::make_unique<Integer>(1);
  EXPECT_NO_THROW(ArithmeticPtr a = castPtr<Arithmetic>(obj));
  
  EXPECT_FALSE(castPtr<Rational>(obj));
}
