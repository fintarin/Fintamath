#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Cos.hpp"

#include "fintamath/functions/Functions.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

TEST(CosTests, toStringTest) {
  EXPECT_EQ(Cos().toString(), "cos");
}

TEST(CosTests, getFunctionTypeTest) {
  EXPECT_EQ(Cos().getFunctionType(), IFunction::Type::Unary);
}

TEST(CosTests, callTest) {
  EXPECT_EQ(Cos()(Integer(0)).toString(), "1");
  EXPECT_EQ(Cos()(Integer(10)).toString(),
            "-0.83907152907645245225886394782406483451993016513316854683595373104879258686627077");
  EXPECT_EQ(Cos()(Integer(5)).toString(),
            "0.2836621854632262644666391715135573083344225922522159449303590665861514567673827");
  EXPECT_EQ(Cos()(Rational(1, 10)).toString(),
            "0.99500416527802576609556198780387029483857622541508403595935274468526591021824047");
  EXPECT_EQ(Cos()(PI_NUM / 2).toString(), "0");
  EXPECT_EQ(Cos()(PI_NUM).toString(), "-1");

  EXPECT_EQ(Cos()(Variable("a")).toString(), "cos(a)");

  std::unique_ptr<IFunction> f = std::make_unique<Cos>();
  EXPECT_EQ((*f)(Integer(10)).toString(),
            "-0.83907152907645245225886394782406483451993016513316854683595373104879258686627077");
  EXPECT_THROW((*f)(), FunctionCallException);
  EXPECT_THROW((*f)(Integer(1), Integer(1), Integer(1)), FunctionCallException);
}

TEST(CosTests, getClassNameTest) {
  EXPECT_EQ(Cos().getClassName(), "Cos");
}
