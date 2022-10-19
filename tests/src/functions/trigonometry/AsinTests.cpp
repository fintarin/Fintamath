#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Asin.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(AsinTests, toStringTest) {
  EXPECT_EQ(Asin().toString(), "asin");
}

TEST(AsinTests, getFunctionTypeTest) {
  EXPECT_EQ(Asin().getFunctionType(), Function::Type::Unary);
}

TEST(AsinTests, callTest) {
  EXPECT_EQ(Asin()(Integer(0))->toString(), "0");
  EXPECT_EQ(Asin()(Integer(1))->toString(), "1.570796326794896619231321691639751442");
  EXPECT_EQ(Asin()(Rational(1, 10))->toString(), "0.100167421161559796345523179452693319");
  EXPECT_EQ(Asin()(Rational(-1, 5))->toString(), "-0.20135792079033079145512555221762341");

  EXPECT_ANY_THROW(Asin()(Variable("a")));
  EXPECT_ANY_THROW(Asin()(Integer(10)));

  std::unique_ptr<Function> f = std::make_unique<Asin>();
  EXPECT_EQ((*f)(Rational(1, 10))->toString(), "0.100167421161559796345523179452693319");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}
