#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Tan.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(TanTests, toStringTest) {
  EXPECT_EQ(Tan().toString(), "tan");
}

TEST(TanTests, getFunctionTypeTest) {
  EXPECT_EQ(Tan().getFunctionType(), IFunction::Type::Unary);
}

TEST(TanTests, callTest) {
  EXPECT_EQ(Tan()(Integer(0))->toString(), "0");
  EXPECT_EQ(Tan()(Integer(10))->toString(), "0.648360827459086671259124933009808677");
  EXPECT_EQ(Tan()(Integer(-10))->toString(), "-0.648360827459086671259124933009808677");
  EXPECT_EQ(Tan()(Integer(5))->toString(), "-3.380515006246585636982705879447343909");
  EXPECT_EQ(Tan()(Rational(1, 10))->toString(), "0.100334672085450545058080045781111537");
  EXPECT_EQ(Tan()(Pi().getValue(10) / 4)->toString(), "1");

  EXPECT_ANY_THROW(Tan()(Variable("a")));
  EXPECT_ANY_THROW(Tan()(Pi().getValue(10) / 2));

  std::unique_ptr<IFunction> f = std::make_unique<Tan>();
  EXPECT_EQ((*f)(Integer(10))->toString(), "0.648360827459086671259124933009808677");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}
