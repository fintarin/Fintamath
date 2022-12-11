#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Atan.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(AtanTests, toStringTest) {
  EXPECT_EQ(Atan().toString(), "atan");
}

TEST(AtanTests, getFunctionTypeTest) {
  EXPECT_EQ(Atan().getFunctionType(), IFunction::Type::Unary);
}

TEST(AtanTests, callTest) {
  EXPECT_EQ(Atan()(Integer(0)).toString(), "0");
  EXPECT_EQ(Atan()(Integer(1)).toString(),
            "0.78539816339744830961566084581987572104929234984377645524373614807695410157155225");
  EXPECT_EQ(Atan()(Integer(10)).toString(),
            "1.4711276743037345918528755717617308518553063771832382624719635193438804556955538");
  EXPECT_EQ(Atan()(Integer(-10)).toString(),
            "-1.4711276743037345918528755717617308518553063771832382624719635193438804556955538");
  EXPECT_EQ(Atan()(Rational(1, 10)).toString(),
            "0.099668652491162027378446119878020590243278322504314648015508776810027747447550654");

  EXPECT_EQ(Atan()(Variable("a")).toString(), "atan(a)");

  std::unique_ptr<IFunction> f = std::make_unique<Atan>();
  EXPECT_EQ((*f)(Integer(10)).toString(),
            "1.4711276743037345918528755717617308518553063771832382624719635193438804556955538");
  EXPECT_THROW((*f)(), FunctionCallException);
  EXPECT_THROW((*f)(Integer(1), Integer(1), Integer(1)), FunctionCallException);
}
