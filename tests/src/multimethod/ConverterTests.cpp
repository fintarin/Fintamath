#include <gtest/gtest.h>

#include "fintamath/multimethod/Converter.hpp"

#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

TEST(ConverterTests, convertTest) {
  EXPECT_TRUE(Converter::convert(Integer(), Integer())->instanceOf<Integer>());

  EXPECT_TRUE(Converter::convert(Rational(), Rational())->instanceOf<Rational>());
  EXPECT_TRUE(Converter::convert(Integer(), Rational())->instanceOf<Rational>());
  EXPECT_FALSE(Converter::convert(Rational(), Integer()));

  EXPECT_TRUE(Converter::convert(Real(), Real())->instanceOf<Real>());
  EXPECT_TRUE(Converter::convert(Integer(), Real())->instanceOf<Real>());
  EXPECT_FALSE(Converter::convert(Real(), Integer()));
  EXPECT_TRUE(Converter::convert(Rational(), Real())->instanceOf<Real>());
  EXPECT_FALSE(Converter::convert(Real(), Rational()));
}
