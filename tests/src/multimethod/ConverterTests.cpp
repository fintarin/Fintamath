#include <gtest/gtest.h>

#include "fintamath/multimethod/Converter.hpp"

#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

TEST(ConverterTests, convertTest) {
  EXPECT_TRUE(cast<Integer>(Converter::convert(Integer(), Integer())));

  EXPECT_TRUE(cast<Rational>(Converter::convert(Rational(), Rational())));
  EXPECT_TRUE(cast<Rational>(Converter::convert(Integer(), Rational())));
  EXPECT_FALSE(Converter::convert(Rational(), Integer()));

  EXPECT_TRUE(cast<Real>(Converter::convert(Real(), Real())));
  EXPECT_TRUE(cast<Real>(Converter::convert(Integer(), Real())));
  EXPECT_FALSE(Converter::convert(Real(), Integer()));
  EXPECT_TRUE(cast<Real>(Converter::convert(Rational(), Real())));
  EXPECT_FALSE(Converter::convert(Real(), Rational()));
}
