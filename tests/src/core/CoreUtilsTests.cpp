#include <gtest/gtest.h>

#include "fintamath/core/CoreUtils.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(CoreUtilsTests, castTest) {
  EXPECT_NO_THROW(unique_ptr<IArithmetic> a = cast<IArithmetic>(ONE.clone()));
  EXPECT_FALSE(is<Rational>(ONE.clone()));
}

TEST(CoreUtilsTests, convertTest) {
  EXPECT_TRUE(is<Rational>(convert(Rational(), Integer())));
  EXPECT_FALSE(convert(Integer(), Rational()));

  EXPECT_TRUE(is<Rational>(convert<Rational>(Integer())));
  EXPECT_THROW(convert<Integer>(Rational()), std::bad_cast);
}
