#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Tanh.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Tanh f;

TEST(TanhTests, toStringTest) {
  EXPECT_EQ(f.toString(), "tanh");
}

TEST(TanhTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(TanhTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(5))->toString(),
            "0.99990920426259513121099044753447302108981261599054786273642887226256101633392102");
  EXPECT_EQ(f(Integer(-5))->toString(),
            "-0.99990920426259513121099044753447302108981261599054786273642887226256101633392102");

  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "0.099667994624955817118305083678352183538962095776734436930476438543991782735048838");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "0.46211715726000975850231848364367254873028928033011303855273181583808090614040928");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "tanh(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "tanh(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(TanhTests, exprTest) {
  EXPECT_EQ(tanhExpr(Integer(10))->toString(), "tanh(10)");
}

TEST(TanhTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(TanhTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Tanh());
  EXPECT_EQ(Tanh(), f);
  EXPECT_EQ(f, cast<IMathObject>(Tanh()));
  EXPECT_EQ(cast<IMathObject>(Tanh()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(TanhTests, getTypeIdTest) {
  EXPECT_EQ(Tanh::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Tanh));
  EXPECT_EQ(Tanh().getTypeId(), MathObjectTypeId(MathObjectType::Tanh));
}
