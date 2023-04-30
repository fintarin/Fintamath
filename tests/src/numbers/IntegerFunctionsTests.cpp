#include <gtest/gtest.h>

#include "fintamath/numbers/IntegerFunctions.hpp"

#include "fintamath/exceptions/UndefinedBinaryOperatorException.hpp"
#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/exceptions/UndefinedUnaryOperatorException.hpp"

using namespace fintamath;

TEST(IntegerFunctionsTests, intSqrtTest) {
  EXPECT_EQ(intSqrt(Integer(25)), 5);
  EXPECT_EQ(intSqrt(Integer(100)), 10);
  EXPECT_EQ(intSqrt(Integer(144)), 12);
  EXPECT_EQ(intSqrt(Integer("10000000000000000000000000000000000000000000000000000")),
            Integer("100000000000000000000000000"));

  EXPECT_EQ(intSqrt(Integer(35)), 5);
  EXPECT_EQ(intSqrt(Integer(4212)), Integer(64));
  EXPECT_EQ(intSqrt(Integer("992188888888")), Integer(996086));
  EXPECT_EQ(intSqrt(Integer("68732648273642987365932706179432649827364")), Integer("262169121510606178721"));

  EXPECT_THROW(intSqrt(Integer(-9289)), UndefinedFunctionException);
}

TEST(IntegerFunctionsTests, sqrtWithRemainderTest) {
  Integer remainder;

  EXPECT_EQ(intSqrt(Integer(25), remainder), 5);
  EXPECT_EQ(remainder.toString(), "0");

  EXPECT_EQ(intSqrt(Integer(100), remainder), 10);
  EXPECT_EQ(remainder.toString(), "0");

  EXPECT_EQ(intSqrt(Integer(144), remainder), 12);
  EXPECT_EQ(remainder.toString(), "0");

  EXPECT_EQ(intSqrt(Integer("10000000000000000000000000000000000000000000000000000"), remainder),
            Integer("100000000000000000000000000"));
  EXPECT_EQ(remainder.toString(), "0");

  EXPECT_EQ(intSqrt(Integer(35), remainder), 5);
  EXPECT_EQ(remainder.toString(), "10");

  EXPECT_EQ(intSqrt(Integer(4212), remainder), Integer(64));
  EXPECT_EQ(remainder.toString(), "116");

  EXPECT_EQ(intSqrt(Integer("992188888888"), remainder), Integer(996086));
  EXPECT_EQ(remainder.toString(), "1569492");

  EXPECT_EQ(intSqrt(Integer("68732648273642987365932706179432649827364"), remainder), Integer("262169121510606178721"));
  EXPECT_EQ(remainder.toString(), "307087949370856631523");

  EXPECT_THROW(intSqrt(Integer(-9289), remainder), UndefinedFunctionException);
}

TEST(IntegerFunctionsTests, powTest) {
  EXPECT_EQ(pow(Integer(5), 2), 25);
  EXPECT_EQ(pow(Integer(-5), 5), -3125);
  EXPECT_EQ(pow(Integer("6789"), 4), 2124336126051441);

  EXPECT_THROW(pow(Integer(0), 0), UndefinedBinaryOperatorException);
}

TEST(IntegerFunctionsTests, factorialTest) {
  EXPECT_EQ(factorial(Integer(0)), 1);
  EXPECT_EQ(factorial(Integer(5)), 120);
  EXPECT_EQ(factorial(Integer("25")).toString(), "15511210043330985984000000");

  EXPECT_THROW(factorial(Integer(-1)), UndefinedUnaryOperatorException);
}

TEST(IntegerFunctionsTests, combinationsTest) {
  EXPECT_EQ(combinations(Integer(6), Integer(2)), 15);
  EXPECT_EQ(combinations(Integer(10), Integer(7)), 120);
  EXPECT_EQ(combinations(Integer(15), Integer(2)), 105);

  EXPECT_THROW(combinations(Integer(20), Integer(40)), UndefinedFunctionException);
  EXPECT_THROW(combinations(Integer(-3), Integer(-8)), UndefinedUnaryOperatorException);
  EXPECT_THROW(combinations(Integer(5), Integer(-3)), UndefinedUnaryOperatorException);
}

TEST(IntegerFunctionsTests, multinomialCoefficientTest) {
  EXPECT_EQ(multinomialCoefficient(Integer(6), {Integer(2), Integer(3), Integer(1)}), 60);
  EXPECT_EQ(multinomialCoefficient(Integer(8), {Integer(8)}), 1);
  EXPECT_EQ(multinomialCoefficient(Integer(5), {Integer(3), Integer(2)}), 10);
  EXPECT_EQ(multinomialCoefficient(Integer(12), {Integer(3), Integer(9), Integer(0)}), 220);

  EXPECT_THROW(multinomialCoefficient(Integer(12), {Integer(3)}), UndefinedFunctionException);
  EXPECT_THROW(multinomialCoefficient(Integer(12), {Integer(3), Integer(19), Integer(0)}), UndefinedFunctionException);
  EXPECT_THROW(multinomialCoefficient(Integer(12), {Integer(0)}), UndefinedFunctionException);
  EXPECT_THROW(multinomialCoefficient(Integer(-12), {Integer(3), Integer(9), Integer(0)}), UndefinedFunctionException);
  EXPECT_THROW(multinomialCoefficient(Integer(12), {Integer(-3), Integer(9), Integer(0)}), UndefinedFunctionException);
}
