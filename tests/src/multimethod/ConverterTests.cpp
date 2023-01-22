#include <gtest/gtest.h>

#include "fintamath/multimethod/Converter.hpp"

#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

TEST(ConverterTests, convertTest) {
  EXPECT_TRUE(Converter::convert(Integer(), Integer())->instanceof<Integer>());

  EXPECT_TRUE(Converter::convert(Rational(), Rational())->instanceof<Rational>());
  EXPECT_TRUE(Converter::convert(Integer(), Rational())->instanceof<Rational>());
  EXPECT_FALSE(Converter::convert(Rational(), Integer()));

  EXPECT_TRUE(Converter::convert(Real(), Real())->instanceof<Real>());
  EXPECT_TRUE(Converter::convert(Integer(), Real())->instanceof<Real>());
  EXPECT_FALSE(Converter::convert(Real(), Integer()));
  EXPECT_TRUE(Converter::convert(Rational(), Real())->instanceof<Real>());
  EXPECT_FALSE(Converter::convert(Real(), Rational()));
}
