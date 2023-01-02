#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Tan.hpp"

#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/numbers/RealFunctions.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

TEST(TanTests, toStringTest) {
  EXPECT_EQ(Tan().toString(), "tan");
}

TEST(TanTests, getFunctionTypeTest) {
  EXPECT_EQ(Tan().getFunctionType(), IFunction::Type::Unary);
}

TEST(TanTests, callTest) {
  EXPECT_EQ(Tan()(Integer(0))->toString(), "0");
  EXPECT_EQ(Tan()(Integer(10))->toString(),
            "0.6483608274590866712591249330098086768168743429837249756336279673958556003746239");
  EXPECT_EQ(Tan()(Integer(-10))->toString(),
            "-0.6483608274590866712591249330098086768168743429837249756336279673958556003746239");
  EXPECT_EQ(Tan()(Integer(5))->toString(),
            "-3.3805150062465856369827058794473439087095692082854598771768209809183460102012061");
  EXPECT_EQ(Tan()(Rational(1, 10))->toString(),
            "0.10033467208545054505808004578111153681900480457644204002220806579803211288567387");
  EXPECT_EQ(Tan()(PI_NUM / 4)->toString(), "1");

  EXPECT_EQ(Tan()(Variable("a"))->toString(), "tan(a)");

  EXPECT_THROW(Tan()(PI_NUM / 2), UndefinedFunctionException);

  std::unique_ptr<IFunction> f = std::make_unique<Tan>();
  EXPECT_EQ((*f)(Integer(10))->toString(),
            "0.6483608274590866712591249330098086768168743429837249756336279673958556003746239");
  EXPECT_THROW((*f)(), InvalidInputFunctionException);
  EXPECT_THROW((*f)(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
