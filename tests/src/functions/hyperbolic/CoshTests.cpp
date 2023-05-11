#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Cosh.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Cosh f;

TEST(CoshTests, toStringTest) {
  EXPECT_EQ(f.toString(), "cosh");
}

TEST(CoshTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(CoshTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "1");
  EXPECT_EQ(f(Integer(5))->toString(),
            "74.20994852478784444410610804448771402386825858945317206609157532124237417173709");
  EXPECT_EQ(f(Integer(-5))->toString(),
            "74.20994852478784444410610804448771402386825858945317206609157532124237417173709");
  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "1.0050041680558035989879784429683416447096262778589598354245603032483739660459513");

  EXPECT_EQ(f(Variable("a"))->toString(), "cosh(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
