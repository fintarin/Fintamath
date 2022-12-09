#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Cot.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(CotTests, toStringTest) {
  EXPECT_EQ(Cot().toString(), "cot");
}

TEST(CotTests, getFunctionTypeTest) {
  EXPECT_EQ(Cot().getFunctionType(), IFunction::Type::Unary);
}

TEST(CotTests, callTest) {
  EXPECT_EQ(Cot()(Pi().getValue(10) / 2)->toString(), "0");
  EXPECT_EQ(Cot()(Integer(10))->toString(), "1.542351045356920048277469355682429311");
  EXPECT_EQ(Cot()(Integer(-10))->toString(), "-1.542351045356920048277469355682429311");
  EXPECT_EQ(Cot()(Integer(5))->toString(), "-0.295812915532745540427767168082485286");
  EXPECT_EQ(Cot()(Rational(1, 10))->toString(), "9.966644423259237859794112689270593908");
  EXPECT_EQ(Cot()(Pi().getValue(10) / 4)->toString(), "1");

  EXPECT_EQ(Cot()(Variable("a"))->toString(), "cot(a)");

  EXPECT_ANY_THROW(Cot()(Integer(0)));

  std::unique_ptr<IFunction> f = std::make_unique<Cot>();
  EXPECT_EQ((*f)(Integer(10))->toString(), "1.542351045356920048277469355682429311");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}