#include <gtest/gtest.h>

#include "fintamath/meta/Converter.hpp"

#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

TEST(ConverterTests, convertTest) {
  EXPECT_TRUE(is<Integer>(Converter::convert(Integer(), Integer())));

  EXPECT_TRUE(is<Rational>(Converter::convert(Rational(), Rational())));
  EXPECT_TRUE(is<Rational>(Converter::convert(Integer(), Rational())));
  EXPECT_FALSE(Converter::convert(Rational(), Integer()));

  EXPECT_TRUE(is<Real>(Converter::convert(Real(), Real())));
  EXPECT_TRUE(is<Real>(Converter::convert(Integer(), Real())));
  EXPECT_FALSE(Converter::convert(Real(), Integer()));
  EXPECT_TRUE(is<Real>(Converter::convert(Rational(), Real())));
  EXPECT_FALSE(Converter::convert(Real(), Rational()));
}
