#include "gtest/gtest.h"

#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/arithmetic/Inv.hpp"

#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Inv f;

TEST(InvTests, toStringTest) {
	EXPECT_EQ(f.toString(), "inv");
}

TEST(InvTests, getFunctionTypeTest) {
	EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
} 

TEST(InvTests, callTest) {
  EXPECT_EQ(f(Integer(10))->toString(), "1/10");
  EXPECT_EQ(f(Integer(20))->toString(),
            "1/20");
  EXPECT_EQ(f(Integer(2))->toString(),
            "1/2");
  EXPECT_EQ(f(Rational(1, 10))->toString(), "10");

  EXPECT_EQ(f(Variable("a"))->toString(), "1/a");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(10), Integer(10), Integer(10)), InvalidInputFunctionException);
	EXPECT_THROW(f(Integer(0)), UndefinedBinaryOpearatorException);
}