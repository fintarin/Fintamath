#include <gtest/gtest.h>

#include "fintamath/math_objects/nodes/terms/numbers/Rational.hpp"

TEST(RationalTests, integerAssignmentOperatorsTest) {
  Rational ratVal;
  ratVal = Integer(2);
  EXPECT_EQ(ratVal, 2);
}

TEST(RationalTests, plusAssignmentOperatorsTest) {
  Rational ratVal;
  Integer intVal(2);
  EXPECT_EQ(ratVal += intVal, 2);
  EXPECT_EQ(ratVal += 2, 4);
}

TEST(RationalTests, plusOperatorsTest) {
  Rational ratVal;
  Integer intVal(2);
  EXPECT_EQ(ratVal + intVal, 2);
  EXPECT_EQ(intVal + ratVal, 2);
  EXPECT_EQ(ratVal + 2, 2);
  EXPECT_EQ(2 + ratVal, 2);
}

TEST(RationalTests, minusAssignmentOperatorsTest) {
  Rational ratVal;
  Integer intVal(2);
  EXPECT_EQ(ratVal -= intVal, -2);
  EXPECT_EQ(ratVal -= 2, -4);
}

TEST(RationalTests, minusOperatorsTest) {
  Rational ratVal;
  Integer intVal(2);
  EXPECT_EQ(ratVal - intVal, -2);
  EXPECT_EQ(intVal - ratVal, 2);
  EXPECT_EQ(ratVal - 2, -2);
  EXPECT_EQ(2 - ratVal, 2);
}

TEST(RationalTests, multiplyAssignmentOperatorsTest) {
  Rational ratVal(2);
  Integer intVal(2);
  EXPECT_EQ(ratVal *= intVal, 4);
  EXPECT_EQ(ratVal *= 2, 8);
}

TEST(RationalTests, multiplyOperatorsTest) {
  Rational ratVal(2);
  Integer intVal(2);
  EXPECT_EQ(ratVal * intVal, 4);
  EXPECT_EQ(intVal * ratVal, 4);
  EXPECT_EQ(ratVal * 2, 4);
  EXPECT_EQ(2 * ratVal, 4);
}

TEST(RationalTests, divideAssignmentOperatorsTest) {
  Rational ratVal(2);
  Integer intVal(2);
  EXPECT_EQ(ratVal /= intVal, 1);
  EXPECT_EQ(ratVal /= 2, Rational(1, 2));
}

TEST(RationalTests, divideOperatorsTest) {
  Rational ratVal(2);
  Integer intVal(2);
  EXPECT_EQ(ratVal / intVal, 1);
  EXPECT_EQ(intVal / ratVal, 1);
  EXPECT_EQ(ratVal / 2, 1);
  EXPECT_EQ(2 / ratVal, 1);
}

TEST(RationalTests, incrementDecrementOperatorsTest) {
  Rational ratVal;
  EXPECT_EQ(++ratVal, 1);
  EXPECT_EQ(ratVal++, 1);
  EXPECT_EQ(ratVal, 2);
  EXPECT_EQ(--ratVal, 1);
  EXPECT_EQ(ratVal--, 1);
  EXPECT_EQ(ratVal, 0);
}

TEST(RationalTests, unaryMinusPlusOperatorsTest) {
  Rational ratVal(2);
  EXPECT_EQ(+ratVal, 2);
  EXPECT_EQ(-ratVal, -2);
}

TEST(RationalTests, equalOperatorsTest) {
  Rational ratVal(2);
  Integer intVal(2);
  EXPECT_EQ(ratVal == intVal, true);
  EXPECT_EQ(intVal == ratVal, true);
  EXPECT_EQ(ratVal == 2, true);
  EXPECT_EQ(2 == ratVal, true);
}

TEST(RationalTests, notEqualOperatorsTest) {
  Rational ratVal(2);
  Integer intVal(1);
  EXPECT_EQ(ratVal != intVal, true);
  EXPECT_EQ(intVal != ratVal, true);
  EXPECT_EQ(ratVal != 1, true);
  EXPECT_EQ(1 != ratVal, true);
}

TEST(RationalTests, lessOperatorsTest) {
  Rational ratVal(2);
  Integer intVal(1);
  EXPECT_EQ(ratVal < intVal, false);
  EXPECT_EQ(intVal < ratVal, true);
  EXPECT_EQ(ratVal < 2, false);
  EXPECT_EQ(2 < ratVal, false);
}

TEST(RationalTests, moreOperatorsTest) {
  Rational ratVal(2);
  Integer intVal(1);
  EXPECT_EQ(ratVal > intVal, true);
  EXPECT_EQ(intVal > ratVal, false);
  EXPECT_EQ(ratVal > 1, true);
  EXPECT_EQ(1 > ratVal, false);
}

TEST(RationalTests, lessEqualOperatorsTest) {
  Rational ratVal(2);
  Integer intVal(1);
  EXPECT_EQ(ratVal <= intVal, false);
  EXPECT_EQ(intVal <= ratVal, true);
  EXPECT_EQ(ratVal <= 1, false);
  EXPECT_EQ(1 <= ratVal, true);
}

TEST(RationalTests, moreEqualOperatorsTest) {
  Rational ratVal(2);
  Integer intVal(1);
  EXPECT_EQ(ratVal >= intVal, true);
  EXPECT_EQ(intVal >= ratVal, false);
  EXPECT_EQ(ratVal >= 1, true);
  EXPECT_EQ(1 >= ratVal, false);
}

TEST(RationalTests, inOperatorsTest) {
  Rational ratVal;
  std::stringstream in;
  in << 2;
  in >> ratVal;
  EXPECT_EQ(ratVal, 2);
}

TEST(RationalTests, outOperatorsTest) {
  Rational ratVal(2);
  std::stringstream out;
  out << ratVal;
  EXPECT_EQ(out.str(), "2");
}

TEST(RationalTests, getDenominatorTest) {
  EXPECT_EQ(Rational(1, -2).getDenominator().toString(), "2");
}

TEST(RationalTests, negativeDenominatorTest) {
  EXPECT_EQ(Rational(1, -2).toString(), "-0.5");
}
