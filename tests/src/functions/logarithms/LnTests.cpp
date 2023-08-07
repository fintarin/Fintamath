#include "gtest/gtest.h"

#include "fintamath/functions/logarithms/Ln.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Ln f;

TEST(LnTests, toStringTest) {
  EXPECT_EQ(f.toString(), "ln");
}

TEST(LnTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(LnTests, callTest) {
  EXPECT_EQ(f(Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(10))->toString(),
            "2.3025850929940456840179914546843642076011014886287729760333279009675726096773525");
  EXPECT_EQ(f(Integer(5))->toString(),
            "1.6094379124341003746007593332261876395256013542685177219126478914741789877076578");
  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "-2.3025850929940456840179914546843642076011014886287729760333279009675726096773525");
  EXPECT_EQ(f(getE())->toString(), "1.0");

  EXPECT_EQ(f(Variable("a"))->toString(), "ln(a)");

  EXPECT_THROW(f(Integer(-10)), UndefinedFunctionException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(LnTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(LnTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Ln());
  EXPECT_EQ(Ln(), f);
  EXPECT_EQ(f, cast<IMathObject>(Ln()));
  EXPECT_EQ(cast<IMathObject>(Ln()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(LnTests, getTypeIdTest) {
  EXPECT_EQ(Ln::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Ln));
  EXPECT_EQ(Ln().getTypeId(), MathObjectTypeId(MathObjectType::Ln));
}
