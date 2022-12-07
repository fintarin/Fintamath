#include <gtest/gtest.h>

#include "fintamath/helpers/Converter.hpp"

#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;
using namespace fintamath::helpers;

TEST(ConverterTests, convertTest) {
  EXPECT_TRUE(Converter::convert(Integer(), Integer())->is<Integer>());

  EXPECT_TRUE(Converter::convert(Rational(), Rational())->is<Rational>());
  EXPECT_TRUE(Converter::convert(Integer(), Rational())->is<Rational>());
  EXPECT_FALSE(Converter::convert(Rational(), Integer()));

  EXPECT_TRUE(Converter::convert(Real(), Real())->is<Real>());
  EXPECT_TRUE(Converter::convert(Integer(), Real())->is<Real>());
  EXPECT_FALSE(Converter::convert(Real(), Integer()));
  EXPECT_TRUE(Converter::convert(Rational(), Real())->is<Real>());
  EXPECT_FALSE(Converter::convert(Real(), Rational()));
}
