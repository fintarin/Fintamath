#include "gtest/gtest.h"

#include "fintamath/functions/comparison/Neqv.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(NeqvTests, toStringTest) {
  EXPECT_EQ(Neqv().toString(), "!=");
}

TEST(NeqvTests, getFunctionTypeTest) {
  EXPECT_EQ(Neqv().getFunctionType(), IFunction::Type::Binary);
}

TEST(NeqvTests, getOperatorPriorityTest) {
  EXPECT_EQ(Neqv().getOperatorPriority(), IOperator::Priority::Comparison);
}

TEST(NeqvTests, callTest) {
  EXPECT_EQ(Neqv()(Integer(5), Integer(3))->toString(), "true");
  EXPECT_EQ(Neqv()(Integer(3), Integer(5))->toString(), "true");
  EXPECT_EQ(Neqv()(Integer(3), Integer(3))->toString(), "false");
  EXPECT_EQ(Neqv()(Integer(3), Rational(3, 1))->toString(), "false");
  EXPECT_EQ(Neqv()(Rational(5, 2), Integer(2))->toString(), "true");

  EXPECT_EQ(Neqv()(Integer(3), Variable("a"))->toString(), "-a+3!=0");
  EXPECT_EQ(Neqv()(Variable("a"), Variable("a"))->toString(), "false");

  std::unique_ptr<IOperator> o = std::make_unique<Neqv>();
  EXPECT_THROW((*o)(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW((*o)(Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW((*o)(), InvalidInputFunctionException);
  EXPECT_THROW((*o)(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
