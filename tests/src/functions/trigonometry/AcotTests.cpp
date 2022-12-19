#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Acot.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(AcotTests, toStringTest) {
  EXPECT_EQ(Acot().toString(), "acot");
}

TEST(AcotTests, getFunctionTypeTest) {
  EXPECT_EQ(Acot().getFunctionType(), IFunction::Type::Unary);
}

TEST(AcotTests, callTest) {
  EXPECT_EQ(Acot()(Integer(0)).toString(),
            "1.5707963267948966192313216916397514420985846996875529104874722961539082031431045");
  EXPECT_EQ(Acot()(Integer(1)).toString(),
            "0.78539816339744830961566084581987572104929234984377645524373614807695410157155225");
  EXPECT_EQ(Acot()(Integer(10)).toString(),
            "0.099668652491162027378446119878020590243278322504314648015508776810027747447550654");
  EXPECT_EQ(Acot()(Integer(-10)).toString(),
            "-0.099668652491162027378446119878020590243278322504314648015508776810027747447550654");
  EXPECT_EQ(Acot()(Rational(1, 10)).toString(),
            "1.4711276743037345918528755717617308518553063771832382624719635193438804556955538");

  EXPECT_EQ(Acot()(Variable("a")).toString(), "acot(a)");

  std::unique_ptr<IFunction> f = std::make_unique<Acot>();
  EXPECT_EQ((*f)(Integer(10)).toString(),
            "0.099668652491162027378446119878020590243278322504314648015508776810027747447550654");
  EXPECT_THROW((*f)(), FunctionCallException);
  EXPECT_THROW((*f)(Integer(1), Integer(1), Integer(1)), FunctionCallException);
}

TEST(AcotTests, getClassNameTest) {
  EXPECT_EQ(Acot().getClassName(), "Acot");
}
