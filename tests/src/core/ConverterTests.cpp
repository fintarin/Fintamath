#include <gtest/gtest.h>

#include "fintamath/core/Converter.hpp"

#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

TEST(ConverterTests, convertTest) {
  EXPECT_TRUE(is<Integer>(Converter::convert(Integer(), Integer())));

  EXPECT_TRUE(is<Rational>(Converter::convert(Rational(), Rational())));
  EXPECT_TRUE(is<Rational>(Converter::convert(Rational(), Integer())));
  EXPECT_FALSE(Converter::convert(Integer(), Rational()));

  EXPECT_TRUE(is<Real>(Converter::convert(Real(), Real())));
  EXPECT_TRUE(is<Real>(Converter::convert(Real(), Integer())));
  EXPECT_FALSE(Converter::convert(Integer(), Real()));
  EXPECT_TRUE(is<Real>(Converter::convert(Real(), Rational())));
  EXPECT_FALSE(Converter::convert(Rational(), Real()));
}
