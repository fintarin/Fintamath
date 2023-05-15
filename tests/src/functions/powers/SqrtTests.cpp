#include "gtest/gtest.h"

#include "fintamath/functions/powers/Sqrt.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Sqrt f;

TEST(SqrtTests, toStringTest) {
  EXPECT_EQ(f.toString(), "sqrt");
}

TEST(SqrtTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(SqrtTests, callTest) {
  EXPECT_EQ(f(Integer(100))->toString(), "10");
  EXPECT_EQ(f(Integer(10))->toString(),
            "3.1622776601683793319988935444327185337195551393252168268575048527925944386392382");
  EXPECT_EQ(f(Integer(10))->toString(),
            "3.1622776601683793319988935444327185337195551393252168268575048527925944386392382");
  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "0.31622776601683793319988935444327185337195551393252168268575048527925944386392382");

  EXPECT_EQ(f(Variable("a"))->toString(), "sqrt(a)");

  EXPECT_THROW(f(Integer(-10)), UndefinedFunctionException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
