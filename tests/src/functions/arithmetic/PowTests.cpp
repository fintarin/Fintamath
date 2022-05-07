#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/Pow.hpp"

#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(PowTests, toStringTest) {
  EXPECT_EQ(Pow().toString(), "^");
}

TEST(PowTests, getPriorityTest) {
  EXPECT_EQ(Pow().getPriority(), 3);
}

TEST(PowTests, callTest) {
  EXPECT_EQ(Pow()(Integer(3), Integer(2))->toString(), "9");
  EXPECT_EQ(Pow()(Integer(-3), Integer(2))->toString(), "9");
  EXPECT_EQ(Pow()(Rational(5, 2), Integer(2))->toString(), "25/4");
  EXPECT_EQ(Pow()(Integer(4), Rational(1, 2))->toString(), "2");

  EXPECT_EQ(Pow()(Integer(4), Rational(1, 2))->toString(), "2");
  EXPECT_EQ(Pow()(Integer(4), Rational(1, 3))->toString(),
            "79370052598409973737585281963615413/50000000000000000000000000000000000");
  EXPECT_EQ(Pow()(Integer(4), Rational(1, 4))->toString(),
            "1414213562373095048801688724209698079/1000000000000000000000000000000000000");
  EXPECT_EQ(Pow()(Integer(8), Rational(1, 3))->toString(), "2");
  EXPECT_EQ(Pow()(Integer(16), Rational(1, 4))->toString(), "2");
  EXPECT_EQ(Pow()(Integer(7), Rational(1, 1000))->toString(),
            "250486951165215008125889157059945617/250000000000000000000000000000000000");
  EXPECT_EQ(Pow()(*Pow()(Integer(10), Integer(100)), Rational(1, 100))->toString(), "10");
  EXPECT_EQ(Pow()(Integer(4), Rational(5, 2))->toString(), "32");
  EXPECT_EQ(Pow()(Integer(4), Rational(5, 3))->toString(),
            "2015873679831797063627536971645165361/200000000000000000000000000000000000");
  EXPECT_EQ(Pow()(Integer(4), Rational(5, 4))->toString(),
            "2828427124746190097603377448419396157/500000000000000000000000000000000000");
  EXPECT_EQ(Pow()(Integer(8), Rational(5, 3))->toString(), "32");
  EXPECT_EQ(Pow()(Integer(16), Rational(5, 4))->toString(), "32");
  EXPECT_EQ(Pow()(Integer(7), Rational(3, 1000))->toString(),
            "1005854803201430554046280293844745209/1000000000000000000000000000000000000");
  EXPECT_EQ(Pow()(*Pow()(Integer(10), Integer(300)), Rational(1, 100))->toString(),
            "499999999999999999999999999999999999999/500000000000000000000000000000000000");
  EXPECT_EQ(Pow()(Integer(1), Rational(1, 1234))->toString(), "1");
  EXPECT_EQ(Pow()(Integer(10000000000), Rational(1, 100))->toString(),
            "629462705897083605211977053197900303/500000000000000000000000000000000000");

  EXPECT_ANY_THROW(Pow()(Integer(3), Variable("a")));

  std::unique_ptr<Operator> o = std::make_unique<Pow>();
  EXPECT_ANY_THROW((*o)(Integer(1)));
  EXPECT_ANY_THROW((*o)(Rational(2, 3)));
  EXPECT_ANY_THROW((*o)());
  EXPECT_ANY_THROW((*o)(Integer(1), Integer(1), Integer(1)));
}

TEST(PowTests, equalsTest) {
  EXPECT_TRUE(Pow() == Pow());
  EXPECT_FALSE(Pow() == Neg());
}
