#include "gtest/gtest.h"

#include "fintamath/functions/other/Percent.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(PercentTests, toStringTest) {
  EXPECT_EQ(Percent().toString(), "%");
}

TEST(PercentTests, callTest) {
  EXPECT_EQ(Percent()(Integer(1))->toString(), "1/100");
  EXPECT_EQ(Percent()(Integer(1000))->toString(), "10");
  EXPECT_EQ(Percent()(Integer(-10))->toString(), "-1/10");
  EXPECT_EQ(Percent()(Rational(1, 10))->toString(), "1/1000");

  EXPECT_ANY_THROW(Percent()(Variable("a")));

  std::unique_ptr<Function> f = std::make_unique<Percent>();
  EXPECT_EQ((*f)(Integer(10))->toString(), "1/10");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}