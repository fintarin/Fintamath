#include "gtest/gtest.h"

#include "fintamath/functions/logarithms/Lg.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(LgTests, toStringTest) {
  EXPECT_EQ(Lg().toString(), "lg");
}

TEST(LgTests, getFunctionTypeTest) {
  EXPECT_EQ(Lg().getFunctionType(), IFunction::Type::Unary);
}

TEST(LgTests, callTest) {
  EXPECT_EQ(Lg()(Integer(10))->toString(), "1");
  EXPECT_EQ(Lg()(Integer(20))->toString(), "1.301029995663981195213738894724493027");
  EXPECT_EQ(Lg()(Integer(2))->toString(), "0.301029995663981195213738894724493027");
  EXPECT_EQ(Lg()(Rational(1, 10))->toString(), "-1");

  EXPECT_EQ(Lg()(Variable("a"))->toString(), "lg(a)");

  EXPECT_ANY_THROW(Lg()(Integer(-10)));

  std::unique_ptr<IFunction> f = std::make_unique<Lg>();
  EXPECT_EQ((*f)(Integer(20))->toString(), "1.301029995663981195213738894724493027");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(10), Integer(10), Integer(10)));
}
