#include "gtest/gtest.h"

#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/functions/trigonometry/Cot.hpp"

#include "fintamath/functions/Functions.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

TEST(CotTests, toStringTest) {
  EXPECT_EQ(Cot().toString(), "cot");
}

TEST(CotTests, getFunctionTypeTest) {
  EXPECT_EQ(Cot().getFunctionType(), IFunction::Type::Unary);
}

TEST(CotTests, callTest) {
  EXPECT_EQ(Cot()(Integer(10)).toString(),
            "1.5423510453569200482774693556824293113206672064019624909194716061981945043136768");
  EXPECT_EQ(Cot()(Integer(-10)).toString(),
            "-1.5423510453569200482774693556824293113206672064019624909194716061981945043136768");
  EXPECT_EQ(Cot()(Integer(5)).toString(),
            "-0.29581291553274554042776716808248528606823479548153489533787776852195700157385241");
  EXPECT_EQ(Cot()(Rational(1, 10)).toString(),
            "9.9666444232592378597941126892705939076302483291514474270066809743652342102525365");
  EXPECT_EQ(Cot()(pi() / 2).toString(), "0");
  EXPECT_EQ(Cot()(pi() / 4).toString(), "1");

  EXPECT_EQ(Cot()(Variable("a")).toString(), "cot(a)");

  EXPECT_THROW(Cot()(Integer(0)), UndefinedFunctionException);

  std::unique_ptr<IFunction> f = std::make_unique<Cot>();
  EXPECT_EQ((*f)(Integer(10)).toString(),
            "1.5423510453569200482774693556824293113206672064019624909194716061981945043136768");
  EXPECT_THROW((*f)(), FunctionCallException);
  EXPECT_THROW((*f)(Integer(1), Integer(1), Integer(1)), FunctionCallException);
}