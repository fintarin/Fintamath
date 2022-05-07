#include "gtest/gtest.h"

#include "fintamath/functions/logarithms/Ln.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/literals/Constant.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

TEST(LnTests, toStringTest) {
  EXPECT_EQ(Ln().toString(), "ln");
}

TEST(LnTests, callTest) {
  EXPECT_EQ(Ln()(Integer(1))->to<Rational>().toString(5), "0");
  EXPECT_EQ(Ln()(Integer(10))->to<Rational>().toString(10), "2.302585093");
  EXPECT_EQ(Ln()(Integer(5))->to<Rational>().toString(36), "1.609437912434100374600759333226187489");
  EXPECT_EQ(Ln()(Rational(1, 10))->to<Rational>().toString(10), "-2.302585093");
  EXPECT_EQ(Ln()(Constant("e").toRational(10))->to<Rational>().toString(5), "1");

  EXPECT_ANY_THROW(Ln()(Variable("a")));
  EXPECT_ANY_THROW(Ln()(Integer(-10)));

  std::unique_ptr<Function> f = std::make_unique<Ln>();
  EXPECT_EQ((*f)(Integer(10))->to<Rational>().toString(10), "2.302585093");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}

TEST(LnTests, equalsTest) {
  EXPECT_TRUE(Ln() == Ln());
  EXPECT_FALSE(Ln() == Add());
}
