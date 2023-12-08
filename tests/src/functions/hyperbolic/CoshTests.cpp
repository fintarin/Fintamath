#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Cosh.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Cosh f;

TEST(CoshTests, toStringTest) {
  EXPECT_EQ(f.toString(), "cosh");
}

TEST(CoshTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(CoshTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "1");
  EXPECT_EQ(f(Integer(5))->toString(),
            "74.20994852478784444410610804448771402386825858945317206609157532124237417173709");
  EXPECT_EQ(f(Integer(-5))->toString(),
            "74.20994852478784444410610804448771402386825858945317206609157532124237417173709");

  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "1.0050041680558035989879784429683416447096262778589598354245603032483739660459513");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "1.127625965206380785226225161402672012547847118098667483628985735187858770303982");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "cosh(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "cosh(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(CoshTests, exprTest) {
  EXPECT_EQ(coshExpr(Integer(10))->toString(), "cosh(10)");
}

TEST(CoshTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(CoshTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Cosh());
  EXPECT_EQ(Cosh(), f);
  EXPECT_EQ(f, cast<IMathObject>(Cosh()));
  EXPECT_EQ(cast<IMathObject>(Cosh()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(CoshTests, getTypeTest) {
  EXPECT_EQ(Cosh::getTypeStatic(), MathObjectType::Cosh);
  EXPECT_EQ(Cosh().getType(), MathObjectType::Cosh);
}
