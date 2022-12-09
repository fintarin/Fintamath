#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Cos.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

TEST(CosTests, toStringTest) {
  EXPECT_EQ(Cos().toString(), "cos");
}

TEST(CosTests, getFunctionTypeTest) {
  EXPECT_EQ(Cos().getFunctionType(), IFunction::Type::Unary);
}

TEST(CosTests, callTest) {
  EXPECT_EQ(Cos()(Integer(0))->toString(), "1");
  EXPECT_EQ(Cos()(Integer(10))->toString(), "-0.839071529076452452258863947824064835");
  EXPECT_EQ(Cos()(Integer(5))->toString(), "0.283662185463226264466639171513557308");
  EXPECT_EQ(Cos()(Rational(1, 10))->toString(), "0.995004165278025766095561987803870295");
  EXPECT_EQ(Cos()(Pi().getValue(10) / 2)->toString(), "0");

  EXPECT_EQ(Cos()(Variable("a"))->toString(), "cos(a)");

  std::unique_ptr<IFunction> f = std::make_unique<Cos>();
  EXPECT_EQ((*f)(Integer(10))->toString(), "-0.839071529076452452258863947824064835");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}
