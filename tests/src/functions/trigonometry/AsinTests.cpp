#include "gtest/gtest.h"

#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(AsinTests, toStringTest) {
  EXPECT_EQ(Asin().toString(), "asin");
}

TEST(AsinTests, getFunctionTypeTest) {
  EXPECT_EQ(Asin().getFunctionType(), IFunction::Type::Unary);
}

TEST(AsinTests, callTest) {
  EXPECT_EQ(Asin()(Integer(0)).toString(), "0");
  EXPECT_EQ(Asin()(Integer(1)).toString(),
            "1.5707963267948966192313216916397514420985846996875529104874722961539082031431045");
  EXPECT_EQ(Asin()(Rational(1, 10)).toString(),
            "0.10016742116155979634552317945269331856867597222962954139102385503640267365086255");
  EXPECT_EQ(Asin()(Rational(-1, 5)).toString(),
            "-0.20135792079033079145512555221762341024003808140222838625725124345560937462885185");

  EXPECT_EQ(Asin()(Variable("a")).toString(), "asin(a)");

  EXPECT_THROW(Asin()(Integer(10)), UndefinedFunctionException);

  std::unique_ptr<IFunction> f = std::make_unique<Asin>();
  EXPECT_EQ((*f)(Rational(1, 10)).toString(),
            "0.10016742116155979634552317945269331856867597222962954139102385503640267365086255");
  EXPECT_THROW((*f)(), FunctionCallException);
  EXPECT_THROW((*f)(Integer(1), Integer(1), Integer(1)), FunctionCallException);
}

TEST(AsinTests, getClassNameTest) {
  EXPECT_EQ(Asin().getClassName(), "Asin");
}
