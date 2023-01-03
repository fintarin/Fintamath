#include <gtest/gtest.h>

#include "fintamath/core/CoreUtils.hpp"

#include "fintamath/multimethod/Converter.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(CoreUtilsTests, castPtrTest) {
  MathObjectPtr obj = std::make_unique<Integer>(1);
  EXPECT_NO_THROW(ArithmeticPtr a = castPtr<IArithmetic>(obj));
  EXPECT_FALSE(castPtr<Rational>(obj));
}
