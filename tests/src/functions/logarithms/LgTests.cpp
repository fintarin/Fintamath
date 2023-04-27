#include "gtest/gtest.h"

#include "fintamath/functions/logarithms/Lg.hpp"

#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Lg f;

TEST(LgTests, toStringTest) {
  EXPECT_EQ(f.toString(), "lg");
}

TEST(LgTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(LgTests, callTest) {
  EXPECT_EQ(f(Integer(10))->toString(), "1");
  EXPECT_EQ(f(Integer(20))->toString(),
            "1.3010299956639811952137388947244930267681898814621085413104274611271081892744245");
  EXPECT_EQ(f(Integer(2))->toString(),
            "0.30102999566398119521373889472449302676818988146210854131042746112710818927442451");
  EXPECT_EQ(f(Rational(1, 10))->toString(), "-1");

  EXPECT_EQ(f(Variable("a"))->toString(), "ln(a)/ln(10)");

  EXPECT_THROW(f(Integer(-10)), UndefinedFunctionException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(10), Integer(10), Integer(10)), InvalidInputFunctionException);
}
