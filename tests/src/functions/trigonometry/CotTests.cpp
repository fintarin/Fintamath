#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Cot.hpp"

#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Cot f;

TEST(CotTests, toStringTest) {
  EXPECT_EQ(f.toString(), "cot");
}

TEST(CotTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(CotTests, callTest) {
  EXPECT_EQ(f(Integer(10))->toString(),
            "1.5423510453569200482774693556824293113206672064019624909194716061981945043136768");
  EXPECT_EQ(f(Integer(-10))->toString(),
            "-1.5423510453569200482774693556824293113206672064019624909194716061981945043136768");
  EXPECT_EQ(f(Integer(5))->toString(),
            "-0.29581291553274554042776716808248528606823479548153489533787776852195700157385241");
  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "9.9666444232592378597941126892705939076302483291514474270066809743652342102525365");
  EXPECT_EQ(f(PI_NUM / 2)->toString(), "0");
  EXPECT_EQ(f(PI_NUM / 4)->toString(), "1");

  EXPECT_EQ(f(Variable("a"))->toString(), "1/tan(a)");

  EXPECT_THROW(f(Integer(0)), UndefinedFunctionException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
