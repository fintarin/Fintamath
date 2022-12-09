#include "gtest/gtest.h"

#include "fintamath/functions/logarithms/Ln.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/E.hpp"

using namespace fintamath;

TEST(LnTests, toStringTest) {
  EXPECT_EQ(Ln().toString(), "ln");
}

TEST(LnTests, getFunctionTypeTest) {
  EXPECT_EQ(Ln().getFunctionType(), IFunction::Type::Unary);
}

TEST(LnTests, callTest) {
  EXPECT_EQ(Ln()(Integer(1))->toString(), "0");
  EXPECT_EQ(Ln()(Integer(10))->toString(), "2.302585092994045684017991454684364208");
  EXPECT_EQ(Ln()(Integer(5))->toString(), "1.60943791243410037460075933322618764");
  EXPECT_EQ(Ln()(Rational(1, 10))->toString(), "-2.302585092994045684017991454684364208");
  EXPECT_EQ(Ln()(E().getValue(10))->toString(), "1");

  EXPECT_EQ(Ln()(Variable("a"))->toString(), "ln(a)");

  EXPECT_ANY_THROW(Ln()(Integer(-10)));

  std::unique_ptr<IFunction> f = std::make_unique<Ln>();
  EXPECT_EQ((*f)(Integer(10))->toString(), "2.302585092994045684017991454684364208");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}
