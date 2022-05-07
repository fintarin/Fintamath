#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Cot.hpp"

#include "fintamath/literals/Constant.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

TEST(CotTests, toStringTest) {
  EXPECT_EQ(Cot().toString(), "cot");
}

TEST(CotTests, callTest) {
  EXPECT_EQ(Cot()(Constant("pi").toRational(10) / 2)->toString(), "-0");
  EXPECT_EQ(Cot()(Integer(10))->toString(), "1.542351045356920048277469355682429311");
  EXPECT_EQ(Cot()(Integer(-10))->toString(), "-1.542351045356920048277469355682429311");
  EXPECT_EQ(Cot()(Integer(5))->toString(), "-0.295812915532745540427767168082485286");
  EXPECT_EQ(Cot()(Rational(1, 10))->toString(), "9.966644423259237859794112689270593908");
  EXPECT_EQ(Cot()(Constant("pi").toRational(10) / 4)->toString(), "1");

  EXPECT_ANY_THROW(Cot()(Variable("a")));
  EXPECT_ANY_THROW(Cot()(Integer(0)));

  std::unique_ptr<Function> f = std::make_unique<Cot>();
  EXPECT_EQ((*f)(Integer(10))->toString(), "1.542351045356920048277469355682429311");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}