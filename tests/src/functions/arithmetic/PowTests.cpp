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
  EXPECT_EQ(Pow()(Integer(4), Rational(1, 3))->toString(), "1.58740105196819947475170563927230826");
  EXPECT_EQ(Pow()(Integer(4), Rational(1, 4))->toString(), "1.414213562373095048801688724209698079");
  EXPECT_EQ(Pow()(Integer(8), Rational(1, 3))->toString(), "2");
  EXPECT_EQ(Pow()(Integer(16), Rational(1, 4))->toString(), "2");
  EXPECT_EQ(Pow()(Integer(7), Rational(1, 1000))->toString(), "1.001947804660860032503556628239782468");
  EXPECT_EQ(Pow()(*Pow()(Integer(10), Integer(100)), Rational(1, 100))->toString(), "10");
  EXPECT_EQ(Pow()(Integer(4), Rational(5, 2))->toString(), "32");
  EXPECT_EQ(Pow()(Integer(4), Rational(5, 3))->toString(), "10.079368399158985318137684858225826805");
  EXPECT_EQ(Pow()(Integer(4), Rational(5, 4))->toString(), "5.656854249492380195206754896838792314");
  EXPECT_EQ(Pow()(Integer(8), Rational(5, 3))->toString(), "32");
  EXPECT_EQ(Pow()(Integer(16), Rational(5, 4))->toString(), "32");
  EXPECT_EQ(Pow()(Integer(7), Rational(3, 1000))->toString(), "1.005854803201430554046280293844745209");
  EXPECT_EQ(Pow()(*Pow()(Integer(10), Integer(300)), Rational(1, 100))->toString(), "1000");
  EXPECT_EQ(Pow()(Integer(1), Rational(1, 1234))->toString(), "1");
  EXPECT_EQ(Pow()(Integer(10000000000), Rational(1, 100))->toString(), "1.258925411794167210423954106395800606");

  EXPECT_ANY_THROW(Pow()(Integer(3), Variable("a")));

  std::unique_ptr<Operator> o = std::make_unique<Pow>();
  EXPECT_ANY_THROW((*o)(Integer(1)));
  EXPECT_ANY_THROW((*o)(Rational(2, 3)));
  EXPECT_ANY_THROW((*o)());
  EXPECT_ANY_THROW((*o)(Integer(1), Integer(1), Integer(1)));
}
