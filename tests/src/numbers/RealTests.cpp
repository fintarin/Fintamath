#include <gtest/gtest.h>

#include "fintamath/numbers/Real.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"

using namespace fintamath;

TEST(RealTests, constructorTest) {
  EXPECT_EQ(Real(), 0);
}

TEST(RealTests, stringConstructorTest) {
  EXPECT_EQ(Real("-93"), -93);
  EXPECT_EQ(Real("-9.3").toString(), "-9.3");
  EXPECT_EQ(Real("0989929039237832000.9302930929333").toString(), "989929039237832000.9302930929333");
  EXPECT_EQ(Real(".1").toString(), "0.1");
  EXPECT_EQ(Real("1.").toString(), "1");

  EXPECT_THROW(Real("--10"), InvalidInputException);
  EXPECT_THROW(Real("test"), InvalidInputException);
  EXPECT_THROW(Real(""), InvalidInputException);
  EXPECT_THROW(Real("+"), InvalidInputException);
  EXPECT_THROW(Real("939849.0-0023"), InvalidInputException);
  EXPECT_THROW(Real("a"), InvalidInputException);
  EXPECT_THROW(Real("a.1"), InvalidInputException);
  EXPECT_THROW(Real("1.a"), InvalidInputException);
  EXPECT_THROW(Real("1a.1"), InvalidInputException);
  EXPECT_THROW(Real("1.1a"), InvalidInputException);
  EXPECT_THROW(Real("--10.-1"), InvalidInputException);
  EXPECT_THROW(Real("10.-1"), InvalidInputException);
  EXPECT_THROW(Real("1-0.1"), InvalidInputException);
  EXPECT_THROW(Real("10-.1"), InvalidInputException);
  EXPECT_THROW(Real("10.--1"), InvalidInputException);
}

TEST(RealTests, rationalConstructorTest) {
  EXPECT_EQ(Real(Rational(2, 5)).toString(), "0.4");
  EXPECT_EQ(Real(Rational(-2, 5)).toString(), "-0.4");
  EXPECT_EQ(Real(Rational(30, 10)), 3);
}

TEST(RealTests, rationalAssignmentOperatorConstructorTest) {
  Real a;
  EXPECT_EQ(a = Rational(2, 4), 0.5);

  Real b;
  EXPECT_EQ(b = Rational(1, 3), Real(1) / 3);
}

TEST(RealTests, integerConstructorTest) {
  EXPECT_EQ(Real(Integer(2)), 2);
  EXPECT_EQ(Real(Integer(10)), 10);
}

TEST(RealTests, integerAssignmentOperatorTest) {
  Real a;
  EXPECT_EQ(a = Integer(2), 2);

  Real b;
  EXPECT_EQ(b = Integer(91820370928039), Real("91820370928039"));
}

TEST(RealTests, doubleConstructorTest) {
  EXPECT_EQ(Real(2), 2);
  EXPECT_EQ(Real(0.33), 0.33);
}

TEST(RealTests, doubleAssignmentOperatorTest) {
  Real a;
  EXPECT_EQ(a = 2.2, 2.2);
}

TEST(RealTests, plusAssignmentOperatorTest) {
  // EXPECT_EQ(Real(2, 3) += Real(5, 2), Real(19, 6));
  // EXPECT_EQ(Real(-738, 10) += Real(5, 2), Real(-713, 10));
  // EXPECT_EQ(Real(738, 10) += Real(5, 2), Real(763, 10));
  // EXPECT_EQ(Real(-738, 10) += Real(-5, 2), Real(-763, 10));
}

TEST(RealTests, rationalPlusAssignmentOperatorTest) {
}

TEST(RealTests, integerPlusAssignmentOperatorTest) {
  EXPECT_EQ(Real(-10) += Integer(5), -5);
  // EXPECT_EQ(Real(2, 3) += Integer(-5), Real(-13, 3));
}

TEST(RealTests, doublePlusAssignmentOperatorTest) {
}

TEST(RealTests, plusOperatorTest) {
  // EXPECT_EQ(Real(170, 15) + Real(-5, 2), Real(53, 6));
  // EXPECT_EQ(Real(17, 19) + Real(53, 5), Real(1092, 95));
  // EXPECT_EQ(Real(170, 12) + Real(2, 5), Real(437, 30));
}

TEST(RealTests, rationalPlusOperatorTest) {
}

TEST(RealTests, integerPlusOperatorTest) {
  EXPECT_EQ(Real(170) + Integer(-5), 165);
  EXPECT_EQ(Real(17) + Integer(53), 70);
  // EXPECT_EQ(Real(170, 12) + Integer(2), Real(194, 12));
}

TEST(RealTests, doublePlusOperatorTest) {
}

TEST(RealTests, rationalFriendPlusOperatorTest) {
}

TEST(RealTests, integerFriendPlusOperatorTest) {
  EXPECT_EQ(Integer(2) + Real(-18), -16);
  EXPECT_EQ(Integer(4938493849) + Real(1009), 4938494858);
}

TEST(RealTests, doubleFriendPlusOperatorTest) {
}

TEST(RealTests, minusAssignmentOperatorTest) {
  // EXPECT_EQ(Real(2, 3) -= Real(5, 2), Real(-11, 6));
  // EXPECT_EQ(Real(-738, 10) -= Real(5, 2), Real(-763, 10));
  // EXPECT_EQ(Real(738, 10) -= Real(5, 2), Real(713, 10));
  // EXPECT_EQ(Real(-738, 10) -= Real(-5, 2), Real(-713, 10));
}

TEST(RealTests, rationalMinusAssignmentOperatorTest) {
}

TEST(RealTests, integerMinusAssignmentOperatorTest) {
  // EXPECT_EQ(Real(-738, -10) -= Integer(-5), Real(394, 5));
  // EXPECT_EQ(Real(-738, 10) -= Integer(5), Real(-394, 5));
}

TEST(RealTests, doubleMinusAssignmentOperatorTest) {
}

TEST(RealTests, minusOperatorTest) {
  // EXPECT_EQ(Real(170, 15) - Real(-5, 2), Real(83, 6));
  // EXPECT_EQ(Real(17, 19) - Real(53, 5), Real(-922, 95));
  // EXPECT_EQ(Real(170, 12) - Real(2, 5), Real(413, 30));
}

TEST(RealTests, rationalMinusOperatorTest) {
}

TEST(RealTests, integerMinusOperatorTest) {
  // EXPECT_EQ(Real(170) - Integer(5), 165);
  // EXPECT_EQ(Real(17) - Integer(53), -36);
  // EXPECT_EQ(Real(170, 12) - Integer(-2), Real(194, 12));
}

TEST(RealTests, doubleMinusOperatorTest) {
}

TEST(RealTests, rationalFriendMinusOperatorTest) {
}

TEST(RealTests, integerFriendMinusOperatorTest) {
  EXPECT_EQ(Integer(2) - Real(-18), 20);
  EXPECT_EQ(Integer(4938493849) - Real(1009), 4938492840);
}

TEST(RealTests, doubleFriendMinusOperatorTest) {
}

TEST(RealTests, multiplyAssignmentOperatorTest) {
  // EXPECT_EQ(Real(2, 3) *= Real(5, 2), Real(5, 3));
  // EXPECT_EQ(Real(-738, 10) *= Real(5, 2), Real(-369, 2));
  // EXPECT_EQ(Real(738, 10) *= Real(5, 2), Real(369, 2));
  // EXPECT_EQ(Real(-738, 10) *= Real(-5, 2), Real(369, 2));
}

TEST(RealTests, rationalMultiplyAssignmentOperatorTest) {
}

TEST(RealTests, integerMultiplyAssignmentOperatorTest) {
  // EXPECT_EQ(Real(2, 3) *= Integer(-5), Real(-10, 3));
  // EXPECT_EQ(Real(738, -10) *= Integer(5894), Real(-4349772, 10));
  // EXPECT_EQ(Real(-738, -10) *= Integer(10), 738);
}

TEST(RealTests, doubleMultiplyAssignmentOperatorTest) {
}

TEST(RealTests, multiplyOperatorTest) {
  // EXPECT_EQ(Real(170, 15) * Real(-5, 2), Real(-85, 3));
  // EXPECT_EQ(Real(17, 19) * Real(53, 5), Real(901, 95));
  // EXPECT_EQ(Real(170, 12) * Real(2, 5), Real(17, 3));
}

TEST(RealTests, rationalMultiplyOperatorTest) {
}

TEST(RealTests, integerMultiplyOperatorTest) {
  // EXPECT_EQ(Real(2, 3) * Integer(-5), Real(-10, 3));
  // EXPECT_EQ(Real(738, -10) * Integer(5894), Real(-4349772, 10));
  // EXPECT_EQ(Real(-738, -10) * Integer(10), 738);
}

TEST(RealTests, doubleMultiplyOperatorTest) {
}

TEST(RealTests, rationalFriendMultiplyOperatorTest) {
}

TEST(RealTests, integerFriendMultiplyOperatorTest) {
  // EXPECT_EQ(Integer(-5) * Real(2, 3), Real(-10, 3));
  // EXPECT_EQ(Integer(589398724) * Real(1, 8372738), Real(589398724, 8372738));
  // EXPECT_EQ(Integer(10) * Real(-738, -10), 738);
}

TEST(RealTests, doubleFriendMultiplyOperatorTest) {
}

TEST(RealTests, divideAssignmentOperatorTest) {
  // EXPECT_EQ(Real(2, 3) /= Real(5, 2), Real(4, 15));
  // EXPECT_EQ(Real(-738, 10) /= Real(5, 2), Real(-738, 25));
  // EXPECT_EQ(Real(738, 10) /= Real(5, 2), Real(738, 25));
  // EXPECT_EQ(Real(-738, 10) /= Real(-5, 2), Real(738, 25));

  // EXPECT_THROW(Real(-738, -10) /= Real("0"), UndefinedBinaryOpearatorException);
}

TEST(RealTests, rationalDivideAssignmentOperatorTest) {
}

TEST(RealTests, integerDivideAssignmentOperatorTest) {
  // EXPECT_EQ(Real(2, 3) /= Integer(-2), Real(1, -3));
  // EXPECT_EQ(Real(738, -10) /= Integer(5894), Real(-738, 58940));
  // EXPECT_EQ(Real(-738, -10) /= Integer(10), Real(369, 50));
}

TEST(RealTests, doubleDivideAssignmentOperatorTest) {
}

TEST(RealTests, divideOperatorTest) {
  // EXPECT_EQ(Real(170, 15) / Real(-5, 2), Real(-68, 15));
  // EXPECT_EQ(Real(17, 19) / Real(53, 5), Real(85, 1007));
  // EXPECT_EQ(Real(170, 12) / Real(2, 5), Real(425, 12));
}

TEST(RealTests, rationalDivideOperatorTest) {
}

TEST(RealTests, integerDivideOperatorTest) {
  // EXPECT_EQ(Real(2, 3) / Integer(-5), Real(-2, 15));
  // EXPECT_EQ(Real(738, -10) / Integer(5894), Real(738, -58940));
}

TEST(RealTests, doubleDivideOperatorTest) {
}

TEST(RealTests, rationalFriendDivideOperatorTest) {
}

TEST(RealTests, integerFriendDivideOperatorTest) {
  // EXPECT_EQ(Integer(-5) / Real(2, 3), Real(-15, 2));
  // EXPECT_EQ(Integer(589398724) / Real(8372738), Real(589398724, 8372738));
  // EXPECT_EQ(Integer(10) / Real(-10, -738), 738);
}

TEST(RealTests, doubleFriendDivideOperatorTest) {
}

TEST(RealTests, preIncrementOperatorTest) {
  EXPECT_EQ(++Real(-10), -9);
  // EXPECT_EQ(++Real(1, 2), Real(3, 2));
}

TEST(RealTests, postIncrementOperatorTest) {
  Real a = {5};
  EXPECT_EQ(a++, 5);
  EXPECT_EQ(a, 6);

  // Real b(2, 3);
  // EXPECT_EQ(b++, Real(2, 3));
  // EXPECT_EQ(b, Real(5, 3));
}

TEST(RealTests, preDecrementOperatorTest) {
  EXPECT_EQ(--Real(-10), -11);
  // EXPECT_EQ(--Real(1, 2), Real(-1, 2));
}

TEST(RealTests, postDecrementOperatorTest) {
  Real a = {5};
  EXPECT_EQ(a--, 5);
  EXPECT_EQ(a, 4);

  // Real b(2, 3);
  // EXPECT_EQ(b--, Real(2, 3));
  // EXPECT_EQ(b, Real(-1, 3));
}

TEST(RealTests, unaryPlusOperatorTest) {
  EXPECT_EQ(+Real(-5), -5);
}

TEST(RealTests, unaryMinusOperatorTest) {
  EXPECT_EQ(-Real(5), -5);
}

TEST(RealTests, equalOperatorTest) {
  // EXPECT_TRUE(Real(1, 2) == Real(1, 2));
  // EXPECT_TRUE(Real(5, 10) == Real(1, 2));
  // EXPECT_TRUE(Real(5, -10) == Real(-5, 10));

  // EXPECT_FALSE(Real(1, 2) == Real(1, 3));
  // EXPECT_FALSE(Real(3, 2) == Real(1, 3));
  // EXPECT_FALSE(Real(55, 10) == Real(-1, 10));
}

TEST(RealTests, rationalEqualOperatorTest) {
}

TEST(RealTests, integerEqualOperatorTest) {
  EXPECT_TRUE(Real(500) == Integer(500));
  // EXPECT_TRUE(Real(50, -10) == Integer(-5));
}

TEST(RealTests, doubleEqualOperatorTest) {
}

TEST(RealTests, rationalFriendEqualOperatorTest) {
}

TEST(RealTests, integerFriendEqualOperatorTest) {
  EXPECT_TRUE(Integer(500) == Real(500));
  // EXPECT_TRUE(Integer(-5) == Real(50, -10));
}

TEST(RealTests, doubleFriendEqualOperatorTest) {
}

TEST(RealTests, notEqualOperatorTest) {
  // EXPECT_TRUE(Real(55, 10) != Real(-1, 10));

  // EXPECT_FALSE(Real(5, 10) != Real(1, 2));
  // EXPECT_FALSE(Real(5, -10) != Real(-5, 10));
}

TEST(RealTests, rationalNotEqualOperatorTest) {
}

TEST(RealTests, integerNotEqualOperatorTest) {
  // EXPECT_TRUE(Real(50, 10) != Integer(-5));

  EXPECT_FALSE(Real(500) != Integer(500));
}

TEST(RealTests, doubleNotEqualOperatorTest) {
}

TEST(RealTests, rationalFriendNotEqualOperatorTest) {
}

TEST(RealTests, integerFriendNotEqualOperatorTest) {
  EXPECT_TRUE(Integer(50) != Real(3920));

  EXPECT_FALSE(Integer(500) != Real(500));
  // EXPECT_FALSE(-5 != Real(50, -10));
}

TEST(RealTests, doubleFriendNotEqualOperatorTest) {
}

TEST(RealTests, lessOperatorTest) {
  // EXPECT_TRUE(Real(5, -10) < Real(50, 10));

  // EXPECT_FALSE(Real(5, 10) < Real(1, 2));
  // EXPECT_FALSE(Real(5, -10) < Real(-50, 10));
  // EXPECT_FALSE(Real(55, 10) < Real(1, 10));
}

TEST(RealTests, rationalLessOperatorTest) {
}

TEST(RealTests, integerLessOperatorTest) {
  EXPECT_TRUE(Real(500) < Integer(3283));

  // EXPECT_FALSE(Real(50, -10) < -5);
}

TEST(RealTests, doubleLessOperatorTest) {
}

TEST(RealTests, rationalFriendLessOperatorTest) {
}

TEST(RealTests, integerFriendLessOperatorTest) {
  // EXPECT_TRUE(Integer(-5) < Real(50, 10));
  EXPECT_TRUE(Integer(7387) < Real(3983920));

  EXPECT_FALSE(Integer(500) < Real(500));
}

TEST(RealTests, doubleFriendLessOperatorTest) {
}

TEST(RealTests, moreOperatorTest) {
  // EXPECT_TRUE(Real(5, -10) > Real(-50, 10));
  // EXPECT_TRUE(Real(55, 10) > Real(1, 10));

  // EXPECT_FALSE(Real(5, 10) > Real(1, 2));
  // EXPECT_FALSE(Real(5, -10) > Real(50, 10));
}

TEST(RealTests, rationalMoreOperatorTest) {
}

TEST(RealTests, integerMoreOperatorTest) {
  EXPECT_FALSE(Real(500) > Integer(3283));
  // EXPECT_FALSE(Real(50, -10) > Integer(-5));
}

TEST(RealTests, doubleMoreOperatorTest) {
}

TEST(RealTests, rationalFriendMoreOperatorTest) {
}

TEST(RealTests, integerFriendMoreOperatorTest) {
  EXPECT_TRUE(Integer(738657) > Real(320));

  EXPECT_FALSE(Integer(500) > Real(500));
  // EXPECT_FALSE(Integer(-5) > Real(50, 10));
}

TEST(RealTests, doubleFriendMoreOperatorTest) {
}

TEST(RealTests, lessEqualOperatorTest) {
  // EXPECT_TRUE(Real(5, 10) <= Real(1, 2));
  // EXPECT_TRUE(Real(5, -10) <= Real(50, 10));

  // EXPECT_FALSE(Real(5, -10) <= Real(-50, 10));
  // EXPECT_FALSE(Real(55, 10) <= Real(1, 10));
}

TEST(RealTests, rationalLessEqualOperatorTest) {
}

TEST(RealTests, integerLessEqualOperatorTest) {
  // EXPECT_TRUE(Real(500) <= Integer(3283));
  // EXPECT_TRUE(Real(50, -10) <= Integer(-5));
}

TEST(RealTests, doubleLessEqualOperatorTest) {
}

TEST(RealTests, rationalFriendLessEqualOperatorTest) {
}

TEST(RealTests, integerFriendLessEqualOperatorTest) {
  EXPECT_TRUE(Integer(500) <= Real(500));
  // EXPECT_TRUE(Integer(-5) <= Real(50, 10));

  EXPECT_FALSE(Integer(73687) <= Real(30));
}

TEST(RealTests, doubleFriendLessEqualOperatorTest) {
}

TEST(RealTests, moreEqualOperatorTest) {
  // EXPECT_TRUE(Real(5, 10) >= Real(1, 2));
  // EXPECT_TRUE(Real(5, -10) >= Real(-50, 10));
  // EXPECT_TRUE(Real(55, 10) >= Real(1, 10));

  // EXPECT_FALSE(Real(5, -10) >= Real(50, 10));
}

TEST(RealTests, rationalMoreEqualOperatorTest) {
}

TEST(RealTests, integerMoreEqualOperatorTest) {
  // EXPECT_TRUE(Real(50, -10) >= Integer(-5));

  EXPECT_FALSE(Real(500) >= Integer(3283));
}

TEST(RealTests, doubleMoreEqualOperatorTest) {
}

TEST(RealTests, rationalFriendMoreEqualOperatorTest) {
}

TEST(RealTests, integerFriendMoreEqualOperatorTest) {
  EXPECT_TRUE(Integer(500) >= Real(500));
  EXPECT_TRUE(Integer(738657) >= Real(320));

  // EXPECT_FALSE(Integer(-5) >= Real(50, 10));
}

TEST(RealTests, doubleFriendMoreEqualOperatorTest) {
}

TEST(RealTests, toStringTest) {
}

TEST(RealTests, simplifyTest) {
  EXPECT_TRUE(Real(2.5).simplify()->is<Real>());
  EXPECT_TRUE(Real(11).simplify()->is<Integer>());
  EXPECT_TRUE(Real(-2.5).simplify()->is<Real>());
  EXPECT_TRUE(Real(-11).simplify()->is<Integer>());

  EXPECT_EQ(Real(2.5).simplify()->toString(), "2.5");
  EXPECT_EQ(Real(11).simplify()->toString(), "11");
  EXPECT_EQ(Real(-2.5).simplify()->toString(), "-2.5");
  EXPECT_EQ(Real(-11).simplify()->toString(), "-11");
}

TEST(RealTests, roundTests) {
  Real val = Rational(1, 3);

  EXPECT_EQ(val.round().toString(), "0");
  EXPECT_EQ(val.round(2).toString(), "0.33");
  EXPECT_EQ(val.round(3).toString(), "0.333");
  EXPECT_EQ(val.round(10).toString(), "0.3333333333");

  EXPECT_EQ((-val).round().toString(), "0");
  EXPECT_EQ((-val).round(2).toString(), "-0.33");
  EXPECT_EQ((-val).round(3).toString(), "-0.333");
  EXPECT_EQ((-val).round(10).toString(), "-0.3333333333");

  EXPECT_EQ(Real("10000000000000000000.37841620837012").round(2).toString(), "10000000000000000000.38");
  EXPECT_EQ(Real("10000000000000000000.375").round(2).toString(), "10000000000000000000.38");
}

TEST(RealTests, sqrtTests) {
}
