#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Acoth.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Acoth f;

TEST(AcothTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acoth");
}

TEST(AcothTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AcothTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "-Inf");
  EXPECT_EQ(f(Integer(0))->toString(), "acoth(0)");
  EXPECT_EQ(f(Integer(1))->toString(), "Inf");
  EXPECT_EQ(f(Integer(2))->toString(),
            "0.54930614433405484569762261846126285232374527891137472586734716681874714660930448");

  EXPECT_EQ(f(Rational(27, 10))->toString(),
            "0.38885228429400418205928052657916031415593728729094568817383747165534858559471489");
  EXPECT_EQ(f(Rational(23, 13))->toString(),
            "0.64046692273103215880348163103852016892243994786861821783871039264710161034962744");

  EXPECT_EQ(f(Real("1.5"))->toString(),
            "0.80471895621705018730037966661309381976280067713425886095632394573708949385382888");

  EXPECT_EQ(f(Variable("a"))->toString(), "acoth(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AcothTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(AcothTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Acoth());
  EXPECT_EQ(Acoth(), f);
  EXPECT_EQ(f, cast<IMathObject>(Acoth()));
  EXPECT_EQ(cast<IMathObject>(Acoth()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(AcothTests, getTypeIdTest) {
  EXPECT_EQ(Acoth::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Acoth));
  EXPECT_EQ(Acoth().getTypeId(), MathObjectTypeId(MathObjectType::Acoth));
}
