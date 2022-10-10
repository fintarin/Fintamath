#include <gtest/gtest.h>

#include "fintamath/meta/Converter.hpp"

#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;
using namespace fintamath::meta;

TEST(ConverterTests, convertTest) {
  EXPECT_TRUE(convertMathObject(Integer(), Rational())->is<Rational>());

  EXPECT_FALSE(convertMathObject(Rational(), Integer()));
}
