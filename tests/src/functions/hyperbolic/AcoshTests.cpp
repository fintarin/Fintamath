#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Acosh.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Acosh f;

TEST(AcoshTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acosh");
}

TEST(AcoshTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AcoshTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "I Pi");
  EXPECT_EQ(f(Integer(0))->toString(), "(I Pi)/2");
  EXPECT_EQ(f(Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(2))->toString(),
            "1.316957896924816708625046347307968444026981971467516479768472256920460185416444");

  EXPECT_EQ(f(Rational(11, 10))->toString(),
            "0.44356825438511518913291106635249808664900116609997546389342095580766881611303472");
  EXPECT_EQ(f(Rational(23, 13))->toString(),
            "1.1720930632462197632831227513306924192738346732428024686924646851189700836483782");

  EXPECT_EQ(f(Real("1.5"))->toString(),
            "0.96242365011920689499551782684873684627036866877132103932203633768032773521644355");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "acosh(1 + I)");

  EXPECT_EQ(f(Integer(-2))->toString(), "acosh(-2)");

  EXPECT_EQ(f(Variable("a"))->toString(), "acosh(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AcoshTests, exprTest) {
  EXPECT_EQ(acoshExpr(Integer(10))->toString(), "acosh(10)");
}

TEST(AcoshTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(AcoshTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Acosh());
  EXPECT_EQ(Acosh(), f);
  EXPECT_EQ(f, cast<IMathObject>(Acosh()));
  EXPECT_EQ(cast<IMathObject>(Acosh()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(AcoshTests, getTypeIdTest) {
  EXPECT_EQ(Acosh::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Acosh));
  EXPECT_EQ(Acosh().getTypeId(), MathObjectTypeId(MathObjectType::Acosh));
}
