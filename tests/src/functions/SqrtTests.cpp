#include "gtest/gtest.h"
#include <fintamath/operators/Add.hpp>
#include <fintamath/variables/Variable.hpp>

#include <fintamath/functions/Sqrt.hpp>

using namespace fintamath;

TEST(SqrtTests, toStringTest) {
  EXPECT_EQ(Sqrt().toString(), "sqrt");
}

TEST(SqrtTests, callTest){
  EXPECT_EQ(Sqrt()(Integer(100))->to<Rational>().toString(10), "10");
  EXPECT_EQ(Sqrt()(Integer(10))->to<Rational>().toString(10), "3.1622776602");
  EXPECT_EQ(Sqrt()(Integer(10))->to<Rational>().toString(36), "3.162277660168379331998893544432718533");
  EXPECT_EQ(Sqrt()(Rational(1, 10))->to<Rational>().toString(10), "0.316227766");

  EXPECT_ANY_THROW(Sqrt()(Variable("a")));
  EXPECT_ANY_THROW(Sqrt()(Integer(-10)));

  std::unique_ptr<Function> f = std::make_unique<Sqrt>();
  EXPECT_EQ((*f)(Integer(10))->to<Rational>().toString(10), "3.1622776602");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}

TEST(SqrtTests, equalsTest) {
  EXPECT_TRUE(Sqrt() == Sqrt());
  EXPECT_FALSE(Sqrt() == Add());
}