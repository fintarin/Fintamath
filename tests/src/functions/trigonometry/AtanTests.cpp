#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Atan.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Atan f;

TEST(AtanTests, toStringTest) {
  EXPECT_EQ(f.toString(), "atan");
}

TEST(AtanTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AtanTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(1))->toString(),
            "0.78539816339744830961566084581987572104929234984377645524373614807695410157155225");
  EXPECT_EQ(f(Integer(10))->toString(),
            "1.4711276743037345918528755717617308518553063771832382624719635193438804556955538");
  EXPECT_EQ(f(Integer(-10))->toString(),
            "-1.4711276743037345918528755717617308518553063771832382624719635193438804556955538");
  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "0.099668652491162027378446119878020590243278322504314648015508776810027747447550654");

  EXPECT_EQ(f(Variable("a"))->toString(), "atan(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
