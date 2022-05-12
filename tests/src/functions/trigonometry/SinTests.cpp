#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Sin.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(SinTests, toStringTest) {
  EXPECT_EQ(Sin().toString(), "sin");
}

TEST(SinTests, callTest) {
  EXPECT_EQ(Sin()(Integer(0))->toString(), "0");
  EXPECT_EQ(Sin()(Integer(10))->toString(), "-0.544021110889369813404747661851377282");
  EXPECT_EQ(Sin()(Integer(5))->toString(), "-0.958924274663138468893154406155993973");
  EXPECT_EQ(Sin()(Rational(1, 10))->toString(), "0.099833416646828152306814198410622027");
  EXPECT_EQ(Sin()(Pi().getValue(10) / 2)->toString(), "1");

  EXPECT_ANY_THROW(Sin()(Variable("a")));

  std::unique_ptr<Function> f = std::make_unique<Sin>();
  EXPECT_EQ((*f)(Integer(10))->toString(), "-0.544021110889369813404747661851377282");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}
