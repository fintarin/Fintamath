#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Cot.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
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
  EXPECT_EQ(f(getPi() / 2)->toString(), "0");
  EXPECT_EQ(f(getPi() / 4)->toString(), "1");

  EXPECT_EQ(f(Variable("a"))->toString(), "cot(a)");

  EXPECT_THROW(f(Integer(0)), UndefinedFunctionException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(CotTests, doArgsMatchTest) {
  EXPECT_FALSE(f.doArgsMatch({}));
}

TEST(CotTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Cot());
  EXPECT_EQ(Cot(), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}