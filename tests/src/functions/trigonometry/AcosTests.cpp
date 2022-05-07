#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Acos.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

TEST(AcosTests, toStringTest) {
  EXPECT_EQ(Acos().toString(), "acos");
}

TEST(AcosTests, callTest) {
  EXPECT_EQ(Acos()(Integer(1))->to<Rational>().toString(5), "0");
  EXPECT_EQ(Acos()(Integer(0))->to<Rational>().toString(36), "1.570796326794896619231321691639751442");
  EXPECT_EQ(Acos()(Rational(1, 10))->to<Rational>().toString(10), "1.4706289056");
  EXPECT_EQ(Acos()(Rational(-1, 5))->to<Rational>().toString(10), "1.7721542476");

  EXPECT_ANY_THROW(Acos()(Variable("a")));
  EXPECT_ANY_THROW(Acos()(Integer(10)));

  std::unique_ptr<Function> f = std::make_unique<Acos>();
  EXPECT_EQ((*f)(Rational(1, 10))->to<Rational>().toString(10), "1.4706289056");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}

TEST(AcosTests, equalsTest) {
  EXPECT_TRUE(Acos() == Acos());
  EXPECT_FALSE(Acos() == Add());
}
