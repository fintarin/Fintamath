#include "gtest/gtest.h"
#include <fintamath/operators/Add.hpp>
#include <fintamath/literals/Variable.hpp>
#include <fintamath/literals/Constant.hpp>

#include <fintamath/functions/trigonometry/Acot.hpp>

using namespace fintamath;

TEST(AcotTests, toStringTest) {
  EXPECT_EQ(Acot().toString(), "acot");
}

TEST(AcotTests, callTest){
  EXPECT_EQ(Acot()(Integer(0))->to<Rational>().toString(10), "1.5707963268");
  EXPECT_EQ(Acot()(Integer(1))->to<Rational>().toString(36), "0.785398163397448309615660845819875726");
  EXPECT_EQ(Acot()(Integer(10))->to<Rational>().toString(10), "0.0996686525");
  EXPECT_EQ(Acot()(Integer(-10))->to<Rational>().toString(10), "-0.0996686525");
  EXPECT_EQ(Acot()(Rational(1, 10))->to<Rational>().toString(10), "1.4711276743");

  EXPECT_ANY_THROW(Acot()(Variable("a")));

  std::unique_ptr<Function> f = std::make_unique<Acot>();
  EXPECT_EQ((*f)(Integer(10))->to<Rational>().toString(10), "0.0996686525");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}

TEST(AcotTests, equalsTest) {
  EXPECT_TRUE(Acot() == Acot());
  EXPECT_FALSE(Acot() == Add());
}
