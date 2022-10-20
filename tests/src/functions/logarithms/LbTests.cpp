#include "gtest/gtest.h"

#include "fintamath/functions/logarithms/Lb.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(LbTests, toStringTest) {
  EXPECT_EQ(Lb().toString(), "lb");
}

TEST(LbTests, getFunctionTypeTest) {
  EXPECT_EQ(Lb().getFunctionType(), IFunction::Type::Unary);
}

TEST(LbTests, callTest) {
  EXPECT_EQ(Lb()(Integer(2))->toString(), "1");
  EXPECT_EQ(Lb()(Integer(10))->toString(), "3.321928094887362347870319429489390176");
  EXPECT_EQ(Lb()(Integer(3))->toString(), "1.584962500721156181453738943947816509");
  EXPECT_EQ(Lb()(Rational(1, 16))->toString(), "-4");

  EXPECT_ANY_THROW(Lb()(Variable("a")));
  EXPECT_ANY_THROW(Lb()(Integer(-10)));

  std::unique_ptr<IFunction> f = std::make_unique<Lb>();
  EXPECT_EQ((*f)(Integer(10))->toString(), "3.321928094887362347870319429489390176");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(10), Integer(10), Integer(10)));
}
