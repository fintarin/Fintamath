#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Acoth.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Acoth f;

TEST(AcothTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acoth");
}

TEST(AcothTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AcothTests, callTest) {
  EXPECT_EQ(f(Integer(2))->toString(),
            "0.54930614433405484569762261846126285232374527891137472586734716681874714660930448");
  EXPECT_EQ(f(Integer(-2))->toString(),
            "-0.54930614433405484569762261846126285232374527891137472586734716681874714660930448");
  EXPECT_EQ(f(Rational(27, 10))->toString(),
            "0.38885228429400418205928052657916031415593728729094568817383747165534858559471489");
  EXPECT_EQ(f(Rational(23, 13))->toString(),
            "0.64046692273103215880348163103852016892243994786861821783871039264710161034962744");

  EXPECT_EQ(f(Variable("a"))->toString(), "acoth(a)");

  EXPECT_THROW(f(Integer(0)), UndefinedFunctionException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
