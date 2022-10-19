#include "gtest/gtest.h"

#include "fintamath/functions/powers/Sqrt.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(SqrtTests, toStringTest) {
  EXPECT_EQ(Sqrt().toString(), "sqrt");
}

TEST(SqrtTests, getFunctionTypeTest) {
  EXPECT_EQ(Sqrt().getFunctionType(), Function::Type::Unary);
}

TEST(SqrtTests, callTest) {
  EXPECT_EQ(Sqrt()(Integer(100))->toString(), "10");
  EXPECT_EQ(Sqrt()(Integer(10))->toString(), "3.162277660168379331998893544432718534");
  EXPECT_EQ(Sqrt()(Integer(10))->toString(), "3.162277660168379331998893544432718534");
  EXPECT_EQ(Sqrt()(Rational(1, 10))->toString(), "0.316227766016837933199889354443271853");

  EXPECT_ANY_THROW(Sqrt()(Variable("a")));
  EXPECT_ANY_THROW(Sqrt()(Integer(-10)));

  std::unique_ptr<Function> f = std::make_unique<Sqrt>();
  EXPECT_EQ((*f)(Integer(10))->toString(), "3.162277660168379331998893544432718534");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}
