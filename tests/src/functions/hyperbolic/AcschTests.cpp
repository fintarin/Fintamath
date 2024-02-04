#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Acsch.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Acsch f;

TEST(AcschTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acsch");
}

TEST(AcschTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AcschTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(),
            "-0.88137358701954302523260932497979230902816032826163541075329560865337718422202609");
  EXPECT_EQ(f(Integer(0))->toString(),
            "ComplexInf");
  EXPECT_EQ(f(Integer(1))->toString(),
            "0.88137358701954302523260932497979230902816032826163541075329560865337718422202609");
  EXPECT_EQ(f(Integer(2))->toString(),
            "0.48121182505960344749775891342436842313518433438566051966101816884016386760822177");

  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "2.9982229502979697388465955375964534766070580548773036557344592627530896573521661");
  EXPECT_EQ(f(Rational(-1, 5))->toString(),
            "-2.3124383412727526202535623413644143836582450726465592371672289900991325548382389");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "1.4436354751788103424932767402731052694055530031569815589830545065204916028246653");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "acsch(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "acsch(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AcschTests, exprTest) {
  EXPECT_EQ(acschExpr(Integer(10))->toString(), "acsch(10)");
}

TEST(AcschTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(AcschTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Acsch());
  EXPECT_EQ(Acsch(), f);
  EXPECT_EQ(f, cast<IMathObject>(Acsch()));
  EXPECT_EQ(cast<IMathObject>(Acsch()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(AcschTests, getTypeTest) {
  EXPECT_EQ(Acsch::getTypeStatic(), MathObjectType::Acsch);
  EXPECT_EQ(Acsch().getType(), MathObjectType::Acsch);
}
