#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Tanh.hpp"

#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/literals/Variable.hpp"
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

  EXPECT_EQ(f(Variable("a"))->toString(), "tanh(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
