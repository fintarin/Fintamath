#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/powers/Sqrt.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Sqrt f;

TEST(SqrtTests, toStringTest) {
  EXPECT_EQ(f.toString(), "sqrt");
}

TEST(SqrtTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(SqrtTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(SqrtTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(SqrtTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(SqrtTests, callTest) {
  EXPECT_EQ(f(Integer(100))->toString(), "10");
  EXPECT_EQ(f(Integer(25))->toString(), "5");
  EXPECT_EQ(f(Integer(144))->toString(), "12");
  EXPECT_EQ(f(Integer("10000000000000000000000000000000000000000000000000000"))->toString(), "100000000000000000000000000");
  EXPECT_EQ(f(Integer(10))->toString(), "sqrt(10)");
  EXPECT_EQ(f(Integer(35))->toString(), "sqrt(35)");
  EXPECT_EQ(f(Integer(4212))->toString(), "18 sqrt(13)");
  EXPECT_EQ(f(Integer("992188888888"))->toString(), "2 sqrt(248047222222)");
  EXPECT_EQ(f(Integer("68732648273642987365932706179432649827364"))->toString(), "2 sqrt(17183162068410746841483176544858162456841)");

  EXPECT_EQ(f(Rational(25))->toString(), "5");
  EXPECT_EQ(f(Rational(25, 169))->toString(), "5/13");
  EXPECT_EQ(f(Rational(144, 49))->toString(), "12/7");
  EXPECT_EQ(f(Rational("1.44"))->toString(), "6/5");
  EXPECT_EQ(f(Rational(1, 10))->toString(), "1/sqrt(10)");
  EXPECT_EQ(f(Rational(25, 48))->toString(), "5/(4 sqrt(3))");
  EXPECT_EQ(f(Rational(26, 49))->toString(), "sqrt(26)/7");
  EXPECT_EQ(f(Rational(45, 67))->toString(), "(3 sqrt(335))/67");
  EXPECT_EQ(f(Rational("68732648273642987365932706179432649827364.144"))->toString(), "sqrt(42957905171026867103707941362145406142102590)/25");

  EXPECT_EQ(f(Real(144))->toString(), "12.0");
  EXPECT_EQ(f(Real(2))->toString(), "1.4142135623730950488");

  EXPECT_EQ(f(Integer(-10))->toString(), "I sqrt(10)");
  EXPECT_EQ(f(Rational(-9289, 10))->toString(), "(I sqrt(92890))/10");
  EXPECT_EQ(f(Real(-9289))->toString(), "96.379458392335863966 I");

  EXPECT_EQ(f(Variable("a"))->toString(), "sqrt(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(SqrtTests, exprTest) {
  EXPECT_EQ(sqrtExpr(Integer(10))->toString(), "sqrt(10)");
}

TEST(SqrtTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Sqrt");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
