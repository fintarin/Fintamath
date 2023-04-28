#include "gtest/gtest.h"

#include "fintamath/functions/other/Rad.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Rad f;

TEST(RadTests, toStringTest) {
  EXPECT_EQ(f.toString(), "rad");
}

TEST(RadTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(RadTests, callTest) {
  EXPECT_EQ(f(Integer(10))->toString(),
            "0.17453292519943295769236907684886127134428718885417254560971914401710091146034494");
  EXPECT_EQ(f(Integer(-10))->toString(),
            "-0.17453292519943295769236907684886127134428718885417254560971914401710091146034494");
  EXPECT_EQ(f(Rational(-5, 2))->toString(),
            "-0.043633231299858239423092269212215317836071797213543136402429786004275227865086236");

  EXPECT_EQ(f(Variable("a"))->toString(), "1/180 Pi a");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
