#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Sec.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Sec f;

TEST(SecTests, toStringTest) {
  EXPECT_EQ(f.toString(), "sec");
}

TEST(SecTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(SecTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "1");
  EXPECT_EQ(f(Integer(10))->toString(),
            "-1.1917935066878958108796938984273465902047299220035186727706136445417481901426913");
  EXPECT_EQ(f(Integer(5))->toString(),
            "3.5253200858160884067018010599632442585428194001762460017361484962258391406750578");

  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "1.0050209184004554284651141013116358193966528970926934395762732116936548070911247");

  EXPECT_EQ(f(Real("1.123"))->toString(),
            "2.3095744949058823397033462863395854122293002544300187921553680386593297257080509");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "sec(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "sec(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(SecTests, exprTest) {
  EXPECT_EQ(secExpr(Integer(10))->toString(), "sec(10)");
}

TEST(SecTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(SecTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Sec());
  EXPECT_EQ(Sec(), f);
  EXPECT_EQ(f, cast<IMathObject>(Sec()));
  EXPECT_EQ(cast<IMathObject>(Sec()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(SecTests, getTypeTest) {
  EXPECT_EQ(Sec::getTypeStatic(), MathObjectType::Sec);
  EXPECT_EQ(Sec().getType(), MathObjectType::Sec);
}
