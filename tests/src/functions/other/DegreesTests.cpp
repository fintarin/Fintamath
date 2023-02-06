#include "gtest/gtest.h"

#include "fintamath/functions/other/Degrees.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Degrees f;

TEST(DegreesTests, toStringTest) {
  EXPECT_EQ(f.toString(), "degrees");
}

TEST(DegreesTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(DegreesTests, callTest) {
  EXPECT_EQ(f(Integer(10))->toString(),
            "572.95779513082320876798154814105170332405472466564321549160243861202847148321553");
  EXPECT_EQ(f(Integer(-10))->toString(),
            "-572.95779513082320876798154814105170332405472466564321549160243861202847148321553");
  EXPECT_EQ(f(Rational(-5, 2))->toString(),
            "-143.23944878270580219199538703526292583101368116641080387290060965300711787080388");

  EXPECT_EQ(f(Variable("a"))->toString(), "degrees(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
