#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Acos.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Acos f;

TEST(AcosTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acos");
}

TEST(AcosTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AcosTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "Pi");
  EXPECT_EQ(f(Integer(0))->toString(), "Pi/2");
  EXPECT_EQ(f(Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(-2))->toString(), "acos(-2)");
  EXPECT_EQ(f(Integer(2))->toString(), "acos(2)");

  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "1.4706289056333368228857985121870581235299087274579233690964484411175055294922419");
  EXPECT_EQ(f(Rational(-1, 5))->toString(),
            "1.7721542475852274106864472438573748523386227810897812967447235396095175777719563");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "1.0471975511965977461542144610931676280657231331250352736583148641026054687620697");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "acos(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "acos(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AcosTests, exprTest) {
  EXPECT_EQ(acosExpr(Integer(10))->toString(), "acos(10)");
}

TEST(AcosTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(AcosTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Acos());
  EXPECT_EQ(Acos(), f);
  EXPECT_EQ(f, cast<IMathObject>(Acos()));
  EXPECT_EQ(cast<IMathObject>(Acos()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(AcosTests, getTypeTest) {
  EXPECT_EQ(Acos::getTypeStatic(), MathObjectType::Acos);
  EXPECT_EQ(Acos().getType(), MathObjectType::Acos);
}
