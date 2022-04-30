#include <gtest/gtest.h>

#include "fintamath/meta/Converter.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;
using namespace fintamath::meta;

TEST(ConverterTests, convertTest) {
  EXPECT_TRUE(convertRhsToLhsType(Rational(), Integer())->is<Rational>());

  EXPECT_FALSE(convertRhsToLhsType(Integer(), Rational()));
}
