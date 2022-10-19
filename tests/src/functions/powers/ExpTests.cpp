#include "gtest/gtest.h"

#include "fintamath/functions/powers/Exp.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(ExpTests, toStringTest) {
  EXPECT_EQ(Exp().toString(), "exp");
}

TEST(ExpTests, getFunctionTypeTest) {
  EXPECT_EQ(Exp().getFunctionType(), Function::Type::Unary);
}

TEST(ExpTests, callTest) {
  EXPECT_EQ(Exp()(Integer(3))->toString(), "20.085536923187667740928529654581717897");
  EXPECT_EQ(Exp()(Integer(3))->toString(), "20.085536923187667740928529654581717897");
  EXPECT_EQ(Exp()(Integer(-3))->toString(), "0.049787068367863942979342415650061777");
  EXPECT_EQ(Exp()(Rational(1, 3))->toString(), "1.395612425086089528628125319602586838");

  EXPECT_ANY_THROW(Exp()(Variable("a")));

  std::unique_ptr<Function> f = std::make_unique<Exp>();
  EXPECT_EQ((*f)(Integer(3))->toString(), "20.085536923187667740928529654581717897");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1)));
}
