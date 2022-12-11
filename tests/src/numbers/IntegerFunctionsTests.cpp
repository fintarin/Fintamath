#include <gtest/gtest.h>

#include "fintamath/numbers/IntegerFunctions.hpp"

#include "fintamath/exceptions/UndefinedFunctionException.hpp"

using namespace fintamath;

TEST(IntegerFunctionsTests, sqrtTest) {
  EXPECT_EQ(sqrt(Integer(35)), 5);
  EXPECT_EQ(sqrt(Integer(100)), 10);
  EXPECT_EQ(sqrt(Integer(4212)), Integer(64));

  EXPECT_EQ(sqrt(Integer("992188888888")), Integer(996086));
  EXPECT_EQ(sqrt(Integer("10000000000000000000000000000000000000000000000000000")),
            Integer("100000000000000000000000000"));
  EXPECT_EQ(sqrt(Integer("68732648273642987365932706179432649827364")), Integer("262169121510606178721"));

  EXPECT_THROW(sqrt(Integer(-9289)), UndefinedFunctionException);
}

TEST(IntegerFunctionsTests, powTest) {
  // TODO
}

TEST(IntegerFunctionsTests, factorialTest) {
  // TODO
}

TEST(IntegerFunctionsTests, doubleFactorialTest) {
  // TODO
}
