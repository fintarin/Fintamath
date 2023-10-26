#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Asinh.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Asinh f;

TEST(AsinhTests, toStringTest) {
  EXPECT_EQ(f.toString(), "asinh");
}

TEST(AsinhTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AsinhTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(1))->toString(),
            "0.88137358701954302523260932497979230902816032826163541075329560865337718422202609");

  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "0.099834078899207563327303124704769443267712911708825010742382695651591768393613465");
  EXPECT_EQ(f(Rational(-1, 5))->toString(),
            "-0.19869011034924140647463691595020696822130879422445377302126322228548564789597237");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "0.48121182505960344749775891342436842313518433438566051966101816884016386760822177");
  EXPECT_EQ(f(pow(Real(11), -100))->toString(),
            "7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(f(-pow(Real(11), -100))->toString(),
            "-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(f(pow(Real(11), 100))->toString(),
            "240.48267446039699971561158991797110655024618552810197277597745092255075601329337");
  EXPECT_EQ(f(-pow(Real(11), 100))->toString(),
            "-240.48267446039699971561158991797110655024618552810197277597745092255075601329337");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "asinh(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "asinh(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AsinhTests, exprTest) {
  EXPECT_EQ(asinhExpr(Integer(10))->toString(), "asinh(10)");
}

TEST(AsinhTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(AsinhTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Asinh());
  EXPECT_EQ(Asinh(), f);
  EXPECT_EQ(f, cast<IMathObject>(Asinh()));
  EXPECT_EQ(cast<IMathObject>(Asinh()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(AsinhTests, getTypeTest) {
  EXPECT_EQ(Asinh::getTypeStatic(), MathObjectType::Asinh);
  EXPECT_EQ(Asinh().getType(), MathObjectType::Asinh);
}
