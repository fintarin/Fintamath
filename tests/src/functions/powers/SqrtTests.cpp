#include "gtest/gtest.h"

#include "fintamath/functions/powers/Sqrt.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

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
  EXPECT_EQ(f(Integer(25))->toString(), "5");
  EXPECT_EQ(f(Integer(144))->toString(), "12");
  EXPECT_EQ(f(Integer("10000000000000000000000000000000000000000000000000000"))->toString(),
            "100000000000000000000000000");
  EXPECT_EQ(f(Integer(10))->toString(), "sqrt(10)");
  EXPECT_EQ(f(Integer(35))->toString(), "sqrt(35)");
  EXPECT_EQ(f(Integer(4212))->toString(), "18 sqrt(13)");
  EXPECT_EQ(f(Integer("992188888888"))->toString(), "2 sqrt(248047222222)");
  EXPECT_EQ(f(Integer("68732648273642987365932706179432649827364"))->toString(),
            "2 sqrt(17183162068410746841483176544858162456841)");

  EXPECT_EQ(f(Rational(25))->toString(), "5");
  EXPECT_EQ(f(Rational(25, 169))->toString(), "5/13");
  EXPECT_EQ(f(Rational(144, 49))->toString(), "12/7");
  EXPECT_EQ(f(Rational("1.44"))->toString(), "6/5");
  EXPECT_EQ(f(Rational(1, 10))->toString(), "1/sqrt(10)");
  EXPECT_EQ(f(Rational(25, 48))->toString(), "5/(4 sqrt(3))");
  EXPECT_EQ(f(Rational(26, 49))->toString(), "sqrt(26)/7");
  EXPECT_EQ(f(Rational(45, 67))->toString(), "(3 sqrt(335))/67");
  EXPECT_EQ(f(Rational("68732648273642987365932706179432649827364.144"))->toString(),
            "sqrt(42957905171026867103707941362145406142102590)/25");

  EXPECT_EQ(f(Real(144))->toString(), "12.0");
  EXPECT_EQ(f(Real(2))->toString(), "1.414213562373095048801688724209698078569671875376948073176679737990732478462107");

  EXPECT_EQ(f(Integer(-10))->toString(), "I sqrt(10)");
  EXPECT_EQ(f(Rational(-9289, 10))->toString(), "1/10 I sqrt(92890)");
  EXPECT_EQ(f(Real(-9289))->toString(), "96.379458392335863966326568498632217265291077134379132716928952438952915972901934 I");

  EXPECT_EQ(f(Variable("a"))->toString(), "sqrt(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(SqrtTests, exprTest) {
  EXPECT_EQ(sqrtExpr(Integer(10))->toString(), "sqrt(10)");
}

TEST(SqrtTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(SqrtTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Sqrt());
  EXPECT_EQ(Sqrt(), f);
  EXPECT_EQ(f, cast<IMathObject>(Sqrt()));
  EXPECT_EQ(cast<IMathObject>(Sqrt()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(SqrtTests, getTypeTest) {
  EXPECT_EQ(Sqrt::getTypeStatic(), MathObjectType::Sqrt);
  EXPECT_EQ(Sqrt().getType(), MathObjectType::Sqrt);
}
