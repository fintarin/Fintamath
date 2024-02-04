#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Acot.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Acot f;

TEST(AcotTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acot");
}

TEST(AcotTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AcotTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "-Pi/4");
  EXPECT_EQ(f(Integer(0))->toString(), "Pi/2");
  EXPECT_EQ(f(Integer(1))->toString(), "Pi/4");
  EXPECT_EQ(f(Integer(-2))->toString(),
            "-0.46364760900080611621425623146121440202853705428612026381093308872019786416574171");
  EXPECT_EQ(f(Integer(2))->toString(),
            "0.46364760900080611621425623146121440202853705428612026381093308872019786416574171");

  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "1.4711276743037345918528755717617308518553063771832382624719635193438804556955538");
  EXPECT_EQ(f(Rational(-1, 5))->toString(),
            "-1.3734007669450158608612719264449611486509995958997008089697833559128742331648607");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "1.1071487177940905030170654601785370400700476454014326466765392074337103389773628");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "acot(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "acot(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AcotTests, exprTest) {
  EXPECT_EQ(acotExpr(Integer(10))->toString(), "acot(10)");
}

TEST(AcotTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(AcotTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Acot());
  EXPECT_EQ(Acot(), f);
  EXPECT_EQ(f, cast<IMathObject>(Acot()));
  EXPECT_EQ(cast<IMathObject>(Acot()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(AcotTests, getTypeTest) {
  EXPECT_EQ(Acot::getTypeStatic(), MathObjectType::Acot);
  EXPECT_EQ(Acot().getType(), MathObjectType::Acot);
}
