#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Sin.hpp"

#include "fintamath/functions/Functions.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

TEST(SinTests, toStringTest) {
  EXPECT_EQ(Sin().toString(), "sin");
}

TEST(SinTests, getFunctionTypeTest) {
  EXPECT_EQ(Sin().getFunctionType(), IFunction::Type::Unary);
}

TEST(SinTests, callTest) {
  EXPECT_EQ(Sin()(Integer(0)).toString(), "0");
  EXPECT_EQ(Sin()(Integer(10)).toString(),
            "-0.54402111088936981340474766185137728168364301291622389157418401261675720964049343");
  EXPECT_EQ(Sin()(Integer(5)).toString(),
            "-0.9589242746631384688931544061559939733524615439646017781316724542351025580865596");
  EXPECT_EQ(Sin()(Rational(1, 10)).toString(),
            "0.099833416646828152306814198410622026989915388017982259992766861561651744283292428");
  EXPECT_EQ(Sin()(pi() / 2).toString(), "1");

  EXPECT_EQ(Sin()(Variable("a")).toString(), "sin(a)");

  std::unique_ptr<IFunction> f = std::make_unique<Sin>();
  EXPECT_EQ((*f)(Integer(10)).toString(),
            "-0.54402111088936981340474766185137728168364301291622389157418401261675720964049343");
  EXPECT_THROW((*f)(), FunctionCallException);
  EXPECT_THROW((*f)(Integer(1), Integer(1), Integer(1)), FunctionCallException);
}
