#include <gtest/gtest.h>

#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/exceptions/UndefinedUnaryOpearatorException.hpp"
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
  EXPECT_EQ(pow(Integer(5), 2), 25);
  EXPECT_EQ(pow(Integer(-5), 5), -3125);
  EXPECT_EQ(pow(Integer("6789"), 4), 2124336126051441);

  EXPECT_THROW(pow(Integer(0), 0), UndefinedBinaryOpearatorException);
}

TEST(IntegerFunctionsTests, factorialTest) {
  EXPECT_EQ(factorial(Integer(0)), 1);
  EXPECT_EQ(factorial(Integer(5)), 120);
  EXPECT_EQ(factorial(Integer("25")).toString(), "15511210043330985984000000");

  EXPECT_THROW(factorial(Integer(-1)), UndefinedUnaryOpearatorException);
}
