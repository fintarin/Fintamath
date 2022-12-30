#include "gtest/gtest.h"

#include "fintamath/functions/other/Abs.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(AbsTests, toStringTest) {
  EXPECT_EQ(Abs().toString(), "abs");
}

TEST(AbsTests, getFunctionTypeTest) {
  EXPECT_EQ(Abs().getFunctionType(), IFunction::Type::Unary);
}

TEST(AbsTests, callTest) {
  EXPECT_EQ(Abs()(Integer(10)).toString(), "10");
  EXPECT_EQ(Abs()(Integer(-10)).toString(), "10");
  EXPECT_EQ(Abs()(Rational(-5, 2)).toString(), "5/2");

  EXPECT_EQ(Abs()(Variable("a")).toString(), "abs(a)");

  std::unique_ptr<IFunction> f = std::make_unique<Abs>();
  EXPECT_EQ((*f)(Integer(10)).toString(), "10");
  EXPECT_THROW((*f)(), InvalidInputFunctionException);
  EXPECT_THROW((*f)(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
