#include <gtest/gtest.h>

#include "fintamath/numbers/Real.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/exceptions/UndefinedException.hpp"

using namespace fintamath;

TEST(RealTests, constructorTest) {
  EXPECT_EQ(Real(), 0);
}

TEST(RealTests, stringConstructorTest) {
  EXPECT_EQ(Real("-93"), -93);
  EXPECT_EQ(Real("-9.3").toString(), "-9.3");
  EXPECT_EQ(Real("0989929039237832000.9302930929333").toString(), "989929039237832000.9302930929333");
  EXPECT_EQ(Real(".1").toString(), "0.1");
  EXPECT_EQ(Real("1.").toString(), "1.0");
  EXPECT_EQ(Real("10000000000200000000000000000000000000000000000000000000000000000000000000000000000000000000000")
                .toString(),
            "1.00000000002*10^94");

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
  EXPECT_THROW(Real("."), InvalidInputException);
  EXPECT_THROW(Real("1.2.1"), InvalidInputException);
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
  EXPECT_EQ(Real("0.66") += Real("0.33"), Real("0.99"));
  EXPECT_EQ(Real("-73.85") += Real("2.55"), Real("-71.3"));
  EXPECT_EQ(Real("73.8") += Real("2.5"), Real("76.3"));
  EXPECT_EQ(Real("-73.8") += Real("-2.5"), Real("-76.3"));
}

TEST(RealTests, rationalPlusAssignmentOperatorTest) {
  EXPECT_EQ(Real("0.66") += Rational(33, 100), Real("0.99"));
  EXPECT_EQ(Real("-73.85") += Rational(51, 20), Real("-71.3"));
  EXPECT_EQ(Real("73.8") += Rational(5, 2), Real("76.3"));
  EXPECT_EQ(Real("-73.8") += Rational(-5, 2), Real("-76.3"));
}

TEST(RealTests, integerPlusAssignmentOperatorTest) {
  EXPECT_EQ(Real(-18) += Integer(2), -16);
  EXPECT_EQ(Real(1009) += Integer(4938493849), 4938494858);
  EXPECT_EQ(Real(6) += Integer(660), Real(666));

  EXPECT_EQ(Real("0.66") += Integer(6), Real("6.66"));
  EXPECT_EQ(Real("-73.85") += Integer(5), Real("-68.85"));
  EXPECT_EQ(Real("73.8") += Integer(5), Real("78.8"));
  EXPECT_EQ(Real("-73.8") += Integer(-5), Real("-78.8"));

  EXPECT_EQ(Real("0.66") += Integer(6), Real("6.66"));
  EXPECT_EQ(Real("-73.85") += Integer(5), Real("-68.85"));
  EXPECT_EQ(Real("73.8") += Integer(5), Real("78.8"));
  EXPECT_EQ(Real("-73.8") += Integer(-5), Real("-78.8"));
}

TEST(RealTests, doublePlusAssignmentOperatorTest) {
  auto a = Real("0.66") += 0.33;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "0.99");

  a = Real("-73.85") += 2.55;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "-71.3");

  a = Real("73.8") += 2.5;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "76.3");

  a.setPrecision(3);
  a = Real("-73.8") += -2.5;
  EXPECT_EQ(a.toString(), "-76.3");
}

TEST(RealTests, plusOperatorTest) {
  EXPECT_EQ(Real("0.66") + Real("0.33"), Real("0.99"));
  EXPECT_EQ(Real("-73.85") + Real("2.55"), Real("-71.3"));
  EXPECT_EQ(Real("73.8") + Real("2.5"), Real("76.3"));
  EXPECT_EQ(Real("-73.8") + Real("-2.5"), Real("-76.3"));
}

TEST(RealTests, rationalPlusOperatorTest) {
  EXPECT_EQ(Real("0.66") + Rational(33, 100), Real("0.99"));
  EXPECT_EQ(Real("-73.85") + Rational(51, 20), Real("-71.3"));
  EXPECT_EQ(Real("73.8") + Rational(5, 2), Real("76.3"));
  EXPECT_EQ(Real("-73.8") + Rational(-5, 2), Real("-76.3"));
}

TEST(RealTests, integerPlusOperatorTest) {
  EXPECT_EQ(Real(-18) + Integer(2), -16);
  EXPECT_EQ(Real(1009) + Integer(4938493849), 4938494858);
  EXPECT_EQ(Real(6) + Integer(660), Real(666));

  EXPECT_EQ(Real("0.66") + Integer(6), Real("6.66"));
  EXPECT_EQ(Real("-73.85") + Integer(5), Real("-68.85"));
  EXPECT_EQ(Real("73.8") + Integer(5), Real("78.8"));
  EXPECT_EQ(Real("-73.8") + Integer(-5), Real("-78.8"));

  EXPECT_EQ(Real("0.66") + Integer(6), Real("6.66"));
  EXPECT_EQ(Real("-73.85") + Integer(5), Real("-68.85"));
  EXPECT_EQ(Real("73.8") + Integer(5), Real("78.8"));
  EXPECT_EQ(Real("-73.8") + Integer(-5), Real("-78.8"));
}

TEST(RealTests, doublePlusOperatorTest) {
  auto a = Real("0.66") + 0.33;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "0.99");

  a = Real("-73.85") + 2.55;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "-71.3");

  a = Real("73.8") + 2.5;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "76.3");

  a = Real("-73.8") + -2.5;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "-76.3");
}

TEST(RealTests, rationalFriendPlusOperatorTest) {
  EXPECT_EQ(Rational(33, 100) + Real("0.66"), Real("0.99"));
  EXPECT_EQ(Rational(51, 20) + Real("-73.85"), Real("-71.3"));
  EXPECT_EQ(Rational(5, 2) + Real("73.8"), Real("76.3"));
  EXPECT_EQ(Rational(-5, 2) + Real("-73.8"), Real("-76.3"));
}

TEST(RealTests, integerFriendPlusOperatorTest) {
  EXPECT_EQ(Integer(2) + Real(-18), -16);
  EXPECT_EQ(Integer(4938493849) + Real(1009), 4938494858);
  EXPECT_EQ(Integer(660) + Real(6), Real(666));

  EXPECT_EQ(Integer(6) + Real("0.66"), Real("6.66"));
  EXPECT_EQ(Integer(5) + Real("-73.85"), Real("-68.85"));
  EXPECT_EQ(Integer(5) + Real("73.8"), Real("78.8"));
  EXPECT_EQ(Integer(-5) + Real("-73.8"), Real("-78.8"));

  EXPECT_EQ(Integer(6) + Real("0.66"), Real("6.66"));
  EXPECT_EQ(Integer(5) + Real("-73.85"), Real("-68.85"));
  EXPECT_EQ(Integer(5) + Real("73.8"), Real("78.8"));
  EXPECT_EQ(Integer(-5) + Real("-73.8"), Real("-78.8"));
}

TEST(RealTests, doubleFriendPlusOperatorTest) {
  auto a = 0.33 + Real("0.66");
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "0.99");

  a = 2.55 + Real("-73.85");
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "-71.3");

  a = 2.5 + Real("73.8");
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "76.3");

  a = -2.5 + Real("-73.8");
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "-76.3");
}

TEST(RealTests, minusAssignmentOperatorTest) {
  EXPECT_EQ(Real("0.66") -= Real("0.22"), Real("0.44"));
  EXPECT_EQ(Real("-73.85") -= Real("2.55"), Real("-76.4"));
  EXPECT_EQ(Real("73.8") -= Real("2.5"), Real("71.3"));
  EXPECT_EQ(Real("-73.8") -= Real("-2.5"), Real("-71.3"));
}

TEST(RealTests, rationalMinusAssignmentOperatorTest) {
  EXPECT_EQ(Real("0.66") -= Rational(22, 100), Real("0.44"));
  EXPECT_EQ(Real("-73.85") -= Rational(51, 20), Real("-76.4"));
  EXPECT_EQ(Real("73.8") -= Rational(5, 2), Real("71.3"));
  EXPECT_EQ(Real("-73.8") -= Rational(-5, 2), Real("-71.3"));
}

TEST(RealTests, integerMinusAssignmentOperatorTest) {
  EXPECT_EQ(Real(-20) -= Integer(2), -22);
  EXPECT_EQ(Real(4938493849) -= Integer(1009), 4938492840);
  EXPECT_EQ(Real(6) -= Integer(666), Real(-660));

  EXPECT_EQ(Real("6.66") -= Integer(6), Real("0.66"));
  EXPECT_EQ(Real("-73.85") -= Integer(5), Real("-78.85"));
  EXPECT_EQ(Real("73.8") -= Integer(5), Real("68.8"));
  EXPECT_EQ(Real("-73.8") -= Integer(-5), Real("-68.8"));

  EXPECT_EQ(Real("6.66") -= Integer(6), Real("0.66"));
  EXPECT_EQ(Real("-73.85") -= Integer(5), Real("-78.85"));
  EXPECT_EQ(Real("73.8") -= Integer(5), Real("68.8"));
  EXPECT_EQ(Real("-73.8") -= Integer(-5), Real("-68.8"));
}

TEST(RealTests, doubleMinusAssignmentOperatorTest) {
  auto a = Real("0.66") -= 0.22;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "0.44");

  a = Real("-73.85") -= 2.55;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "-76.4");

  a = Real("73.8") -= 2.5;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "71.3");

  a = Real("-73.8") -= -2.5;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "-71.3");
}

TEST(RealTests, minusOperatorTest) {
  EXPECT_EQ(Real("0.66") - Real("0.22"), Real("0.44"));
  EXPECT_EQ(Real("-73.85") - Real("2.55"), Real("-76.4"));
  EXPECT_EQ(Real("73.8") - Real("2.5"), Real("71.3"));
  EXPECT_EQ(Real("-73.8") - Real("-2.5"), Real("-71.3"));
}

TEST(RealTests, rationalMinusOperatorTest) {
  EXPECT_EQ(Real("0.66") - Rational(22, 100), Real("0.44"));
  EXPECT_EQ(Real("-73.85") - Rational(51, 20), Real("-76.4"));
  EXPECT_EQ(Real("73.8") - Rational(5, 2), Real("71.3"));
  EXPECT_EQ(Real("-73.8") - Rational(-5, 2), Real("-71.3"));
}

TEST(RealTests, integerMinusOperatorTest) {
  EXPECT_EQ(Real(-20) - Integer(2), -22);
  EXPECT_EQ(Real(4938493849) - Integer(1009), 4938492840);
  EXPECT_EQ(Real(6) - Integer(666), Real(-660));

  EXPECT_EQ(Real("6.66") - Integer(6), Real("0.66"));
  EXPECT_EQ(Real("-73.85") - Integer(5), Real("-78.85"));
  EXPECT_EQ(Real("73.8") - Integer(5), Real("68.8"));
  EXPECT_EQ(Real("-73.8") - Integer(-5), Real("-68.8"));

  EXPECT_EQ(Real("6.66") - Integer(6), Real("0.66"));
  EXPECT_EQ(Real("-73.85") - Integer(5), Real("-78.85"));
  EXPECT_EQ(Real("73.8") - Integer(5), Real("68.8"));
  EXPECT_EQ(Real("-73.8") - Integer(-5), Real("-68.8"));
}

TEST(RealTests, doubleMinusOperatorTest) {
  auto a = Real("0.66") - 0.22;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "0.44");

  a = Real("-73.85") - 2.55;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "-76.4");

  a = Real("73.8") - 2.5;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "71.3");

  a = Real("-73.8") - -2.5;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "-71.3");
}

TEST(RealTests, rationalFriendMinusOperatorTest) {
  EXPECT_EQ(Rational(22, 100) - Real("0.66"), Real("-0.44"));
  EXPECT_EQ(Rational(51, 20) - Real("-73.85"), Real("76.4"));
  EXPECT_EQ(Rational(5, 2) - Real("73.8"), Real("-71.3"));
  EXPECT_EQ(Rational(-5, 2) - Real("-73.8"), Real("71.3"));
}

TEST(RealTests, integerFriendMinusOperatorTest) {
  EXPECT_EQ(Integer(2) - Real(-20), 22);
  EXPECT_EQ(Integer(1009) - Real(4938493849), -4938492840);
  EXPECT_EQ(Integer(666) - Real(6), Real(660));

  EXPECT_EQ(Integer(6) - Real("6.66"), Real("-0.66"));
  EXPECT_EQ(Integer(5) - Real("-73.85"), Real("78.85"));
  EXPECT_EQ(Integer(5) - Real("73.8"), Real("-68.8"));
  EXPECT_EQ(Integer(-5) - Real("-73.8"), Real("68.8"));

  EXPECT_EQ(Integer(6) - Real("6.66"), Real("-0.66"));
  EXPECT_EQ(Integer(5) - Real("-73.85"), Real("78.85"));
  EXPECT_EQ(Integer(5) - Real("73.8"), Real("-68.8"));
  EXPECT_EQ(Integer(-5) - Real("-73.8"), Real("68.8"));
}

TEST(RealTests, doubleFriendMinusOperatorTest) {
  auto a = 0.22 - Real("0.66");
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "-0.44");

  a = 2.55 - Real("-73.85");
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "76.4");

  a = 2.5 - Real("73.8");
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "-71.3");

  a = -2.5 - Real("-73.8");
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "71.3");
}

TEST(RealTests, multiplyAssignmentOperatorTest) {
  EXPECT_EQ(Real(5) *= Real(2), 10);
  EXPECT_EQ(Real("-2.05") *= Real("-1.1"), Real("2.255"));
  EXPECT_EQ(Real("2.5") *= Real("-1.1"), Real("-2.75"));
}

TEST(RealTests, rationalMultiplyAssignmentOperatorTest) {
  EXPECT_EQ(Real(5) *= Rational(5, 2), Real("12.5"));
  EXPECT_EQ(Real("-2.05") *= Rational(-11, 10), Real("2.255"));
  EXPECT_EQ(Real("2.5") *= Rational(-11, 10), Real("-2.75"));
}

TEST(RealTests, integerMultiplyAssignmentOperatorTest) {
  EXPECT_EQ(Real(5) *= Integer(2), 10);
  EXPECT_EQ(Real(5) *= Integer(-2), -10);
  EXPECT_EQ(Real("-2.05") *= Integer(-11), Real("22.55"));
  EXPECT_EQ(Real("2.5") *= Integer(-11), Real("-27.5"));
}

TEST(RealTests, doubleMultiplyAssignmentOperatorTest) {
  auto a = Real(5) *= 2.5;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "12.5");

  a = Real("-2.05") *= -1.1;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "2.26");

  a = Real("2.5") *= -1.1;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "-2.75");
}

TEST(RealTests, multiplyOperatorTest) {
  EXPECT_EQ(Real(5) * Real(2), 10);
  EXPECT_EQ(Real("-2.05") * Real("-1.1"), Real("2.255"));
  EXPECT_EQ(Real("2.5") * Real("-1.1"), Real("-2.75"));
}

TEST(RealTests, rationalMultiplyOperatorTest) {
  EXPECT_EQ(Real(5) * Rational(5, 2), Real("12.5"));
  EXPECT_EQ(Real("-2.05") * Rational(-11, 10), Real("2.255"));
  EXPECT_EQ(Real("2.5") * Rational(-11, 10), Real("-2.75"));
}

TEST(RealTests, integerMultiplyOperatorTest) {
  EXPECT_EQ(Real(5) * Integer(2), 10);
  EXPECT_EQ(Real(5) * Integer(-2), -10);
  EXPECT_EQ(Real("-2.05") * Integer(-11), Real("22.55"));
  EXPECT_EQ(Real("2.5") * Integer(-11), Real("-27.5"));
}

TEST(RealTests, doubleMultiplyOperatorTest) {
  auto a = Real(5) * 2.5;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "12.5");

  a = Real("-2.05") * -1.1;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "2.26");

  a = Real("2.5") * -1.1;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "-2.75");
}

TEST(RealTests, rationalFriendMultiplyOperatorTest) {
  EXPECT_EQ(Rational(5, 2) * Real(5), Real("12.5"));
  EXPECT_EQ(Rational(-11, 10) * Real("-2.05"), Real("2.255"));
  EXPECT_EQ(Rational(-11, 10) * Real("2.5"), Real("-2.75"));
}

TEST(RealTests, integerFriendMultiplyOperatorTest) {
  EXPECT_EQ(Integer(2) * Real(5), 10);
  EXPECT_EQ(Integer(-2) * Real(5), -10);
  EXPECT_EQ(Integer(-11) * Real("-2.05"), Real("22.55"));
  EXPECT_EQ(Integer(-11) * Real("2.5"), Real("-27.5"));
}

TEST(RealTests, doubleFriendMultiplyOperatorTest) {
  auto a = 2.5 * Real(5);
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "12.5");

  a = -1.1 * Real("-2.05");
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "2.26");

  a = -1.1 * Real("2.5");
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "-2.75");
}

TEST(RealTests, divideAssignmentOperatorTest) {
  auto a = Real(10) /= Real(2);
  EXPECT_EQ(a.toString(), "5.0");
  a = Real("-2.255") /= Real("-1.1");
  EXPECT_EQ(a.toString(), "2.05");
  a = Real("12.1") /= Real("-1.1");
  EXPECT_EQ(a.toString(), "-11.0");
}

TEST(RealTests, rationalDivideAssignmentOperatorTest) {
  auto a = Real(5) /= Rational(2, 5);
  EXPECT_EQ(a.toString(), "12.5");
  a = Real("-2.255") /= Rational(-11, 10);
  EXPECT_EQ(a.toString(), "2.05");
  a = Real("12.1") /= Rational(-11, 10);
  EXPECT_EQ(a.toString(), "-11.0");
}

TEST(RealTests, integerDivideAssignmentOperatorTest) {
  auto a = Real(10) /= Integer(2);
  EXPECT_EQ(a.toString(), "5.0");
  a = Real(10) /= Integer(-2);
  EXPECT_EQ(a.toString(), "-5.0");
  a = Real("22.5") /= Integer(-11);
  EXPECT_EQ(a.toString(), "-2.0454545454545454545454545454545454545454545454545454545454545454545454545454545");
  a = Real("-27.5") /= Integer(-11);
  EXPECT_EQ(a.toString(), "2.5");
}

TEST(RealTests, doubleDivideAssignmentOperatorTest) {
  auto a = Real("12.5") /= 2.5;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "5.0");

  a = Real("2.255") /= -1.1;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "-2.05");

  a = Real("-2.75") /= -1.1;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "2.5");
}

TEST(RealTests, divideOperatorTest) {
  auto a = Real(10) / Real(2);
  EXPECT_EQ(a.toString(), "5.0");
  a = Real("-2.255") / Real("-1.1");
  EXPECT_EQ(a.toString(), "2.05");
  a = Real("12.1") / Real("-1.1");
  EXPECT_EQ(a.toString(), "-11.0");
}

TEST(RealTests, rationalDivideOperatorTest) {
  auto a = Real(5) / Rational(2, 5);
  EXPECT_EQ(a.toString(), "12.5");
  a = Real("-2.255") / Rational(-11, 10);
  EXPECT_EQ(a.toString(), "2.05");
  a = Real("12.1") / Rational(-11, 10);
  EXPECT_EQ(a.toString(), "-11.0");
}

TEST(RealTests, integerDivideOperatorTest) {
  auto a = Real(10) / Integer(2);
  EXPECT_EQ(a.toString(), "5.0");
  a = Real(10) / Integer(-2);
  EXPECT_EQ(a.toString(), "-5.0");
  a = Real("22.5") / Integer(-11);
  EXPECT_EQ(a.toString(), "-2.0454545454545454545454545454545454545454545454545454545454545454545454545454545");
  a = Real("-27.5") / Integer(-11);
  EXPECT_EQ(a.toString(), "2.5");
}

TEST(RealTests, doubleDivideOperatorTest) {
  auto a = Real("12.5") / 2.5;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "5.0");

  a = Real("2.255") / -1.1;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "-2.05");

  a = Real("-2.75") / -1.1;
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "2.5");
}

TEST(RealTests, rationalFriendDivideOperatorTest) {
  auto a = Rational(5, 2) / Real(5);
  EXPECT_EQ(a.toString(), "0.5");
  a = Rational(-11, 10) / Real("-2.5");
  EXPECT_EQ(a.toString(), "0.44");
  a = Rational(-11, 10) / Real("0.1");
  EXPECT_EQ(a.toString(), "-11.0");
}

TEST(RealTests, integerFriendDivideOperatorTest) {
  auto a = Integer(10) / Real(2);
  EXPECT_EQ(a.toString(), "5.0");
  a = Integer(10) / Real(-2);
  EXPECT_EQ(a.toString(), "-5.0");
  a = Integer(-6) / Real("1.6");
  EXPECT_EQ(a.toString(), "-3.75");
  a = Integer(-6) / Real("-1.6");
  EXPECT_EQ(a.toString(), "3.75");
}

TEST(RealTests, doubleFriendDivideOperatorTest) {
  auto a = 2.5 / Real("5");
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "0.5");

  a = -1.1 / Real("-2.5");
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "0.44");

  a = -1.1 / Real("0.1");
  a.setPrecision(3);
  EXPECT_EQ(a.toString(), "-11.0");
}

TEST(RealTests, unaryPlusOperatorTest) {
  EXPECT_EQ(+Real(-5), -5);
  EXPECT_EQ(+Real(5), 5);
}

TEST(RealTests, unaryMinusOperatorTest) {
  EXPECT_EQ(-Real(5), -5);
  EXPECT_EQ(-Real(-5), 5);
}

TEST(RealTests, equalOperatorTest) {
  EXPECT_TRUE(Real("0.5") == Real("0.5"));
  EXPECT_TRUE(Real(-5) == Real(-5));
  EXPECT_TRUE(Real("5.0") == Real(5));

  EXPECT_FALSE(Real("0.5") == Real("1.5"));
  EXPECT_FALSE(Real("-0.5") == Real("0.5"));
}

TEST(RealTests, rationalEqualOperatorTest) {
  EXPECT_TRUE(Real("0.5") == Rational(1, 2));
  EXPECT_TRUE(Real(-5) == Rational(10, -2));

  EXPECT_FALSE(Real("0.5") == Rational(2, 1));
  EXPECT_FALSE(Real("-0.5") == Rational(1, 2));
}

TEST(RealTests, integerEqualOperatorTest) {
  EXPECT_TRUE(Real(500) == Integer(500));
  EXPECT_TRUE(Real("5.0") == Integer(5));
  EXPECT_TRUE(Real("-5.0") == Integer(-5));

  EXPECT_FALSE(Real("0.5") == Integer(5));
  EXPECT_FALSE(Real("-5") == Integer(5));
}

TEST(RealTests, doubleEqualOperatorTest) {
  EXPECT_TRUE(Real(2.55) == 2.55);

  EXPECT_FALSE(Real("2.55") == 2.55);
  EXPECT_FALSE(Real(-2.55) == 2.55);
}

TEST(RealTests, rationalFriendEqualOperatorTest) {
  EXPECT_TRUE(Rational(1, 2) == Real("0.5"));
  EXPECT_TRUE(Rational(10, -2) == Real(-5));

  EXPECT_FALSE(Rational(2, 1) == Real("0.5"));
  EXPECT_FALSE(Rational(1, 2) == Real("-0.5"));
}

TEST(RealTests, integerFriendEqualOperatorTest) {
  EXPECT_TRUE(Integer(500) == Real(500));
  EXPECT_TRUE(Integer(5) == Real("5.0"));
  EXPECT_TRUE(Integer(-5) == Real("-5"));

  EXPECT_FALSE(Integer(5) == Real("0.5"));
  EXPECT_FALSE(Integer(5) == Real("-5"));
}

TEST(RealTests, doubleFriendEqualOperatorTest) {
  EXPECT_TRUE(2.55 == Real(2.55));

  EXPECT_FALSE(2.55 == Real("2.55"));
  EXPECT_FALSE(2.55 == Real(-2.55));
}

TEST(RealTests, notEqualOperatorTest) {
  EXPECT_TRUE(Real("0.5") != Real("1.5"));
  EXPECT_TRUE(Real("-0.5") != Real("0.5"));

  EXPECT_FALSE(Real("0.5") != Real("0.5"));
  EXPECT_FALSE(Real(-5) != Real(-5));
  EXPECT_FALSE(Real("5.0") != Real(5));
}

TEST(RealTests, rationalNotEqualOperatorTest) {
  EXPECT_TRUE(Real("0.5") != Rational(2, 1));
  EXPECT_TRUE(Real("-0.5") != Rational(1, 2));

  EXPECT_FALSE(Real("0.5") != Rational(1, 2));
  EXPECT_FALSE(Real(-5) != Rational(10, -2));
}

TEST(RealTests, integerNotEqualOperatorTest) {
  EXPECT_TRUE(Real("0.5") != Integer(5));
  EXPECT_TRUE(Real("-5") != Integer(5));

  EXPECT_FALSE(Real(500) != Integer(500));
  EXPECT_FALSE(Real("5.0") != Integer(5));
  EXPECT_FALSE(Real("-5.0") != Integer(-5));
}

TEST(RealTests, doubleNotEqualOperatorTest) {
  EXPECT_TRUE(Real("2.55") != 2.55);
  EXPECT_TRUE(Real(-2.55) != 2.55);

  EXPECT_FALSE(Real(2.55) != 2.55);
}

TEST(RealTests, rationalFriendNotEqualOperatorTest) {
  EXPECT_TRUE(Rational(2, 1) != Real("0.5"));
  EXPECT_TRUE(Rational(1, 2) != Real("-0.5"));

  EXPECT_FALSE(Rational(1, 2) != Real("0.5"));
  EXPECT_FALSE(Rational(10, -2) != Real(-5));
}

TEST(RealTests, integerFriendNotEqualOperatorTest) {
  EXPECT_TRUE(Integer(5) != Real("0.5"));
  EXPECT_TRUE(Integer(5) != Real("-5"));

  EXPECT_FALSE(Integer(500) != Real(500));
  EXPECT_FALSE(Integer(5) != Real("5.0"));
  EXPECT_FALSE(Integer(-5) != Real("-5"));
}

TEST(RealTests, doubleFriendNotEqualOperatorTest) {
  EXPECT_TRUE(2.55 != Real("2.55"));
  EXPECT_TRUE(2.55 != Real(-2.55));

  EXPECT_FALSE(2.55 != Real(2.55));
}

TEST(RealTests, lessOperatorTest) {
  EXPECT_TRUE(Real(5) < Real(10));

  EXPECT_FALSE(Real("5.1") < Real("5.1"));
  EXPECT_FALSE(Real(5) < Real(-5));
}

TEST(RealTests, rationalLessOperatorTest) {
  EXPECT_TRUE(Real(5) < Rational(51, 10));

  EXPECT_FALSE(Real("5.1") < Rational(51, 10));
  EXPECT_FALSE(Real(5) < Rational(50, -10));
}

TEST(RealTests, integerLessOperatorTest) {
  EXPECT_TRUE(Real(5) < Integer(10));
  EXPECT_TRUE(Real(-5) < Integer(5));

  EXPECT_FALSE(Real("5.1") < Integer(5));
  EXPECT_FALSE(Real(5) < Integer(-5));
}

TEST(RealTests, doubleLessOperatorTest) {
  EXPECT_TRUE(Real(5) < 5.1);

  EXPECT_FALSE(Real("5.2") < 5.01);
  EXPECT_FALSE(Real("5.55") < -5.55);
}

TEST(RealTests, rationalFriendLessOperatorTest) {
  EXPECT_TRUE(Rational(49, 10) < Real(5));

  EXPECT_FALSE(Rational(51, 10) < Real("5.1"));
  EXPECT_FALSE(Rational(50, 10) < Real(-5));
}

TEST(RealTests, integerFriendLessOperatorTest) {
  EXPECT_TRUE(Integer(4) < Real(5));
  EXPECT_TRUE(Integer(-5) < Real(5));

  EXPECT_FALSE(Integer(6) < Real("6.0"));
  EXPECT_FALSE(Integer(5) < Real(-5));
}

TEST(RealTests, doubleFriendLessOperatorTest) {
  EXPECT_TRUE(4.9 < Real(5));

  EXPECT_FALSE(5.2 < Real("5.1"));
  EXPECT_FALSE(5.2 < Real("-5.2"));
}

TEST(RealTests, moreOperatorTest) {
  EXPECT_TRUE(Real(50) > Real(10));

  EXPECT_FALSE(Real("5.1") > Real("5.1"));
  EXPECT_FALSE(Real(-5) > Real(5));
}

TEST(RealTests, rationalMoreOperatorTest) {
  EXPECT_TRUE(Real(50) > Rational(50, 10));

  EXPECT_FALSE(Real("5.1") > Rational(51, 10));
  EXPECT_FALSE(Real("-5.1") > Rational(51, 10));
}

TEST(RealTests, integerMoreOperatorTest) {
  EXPECT_TRUE(Real(50) > Integer(10));
  EXPECT_TRUE(Real(50) > Integer(-50));

  EXPECT_FALSE(Real("5.0") > Integer(5));
  EXPECT_FALSE(Real(-5) > Integer(5));
}

TEST(RealTests, doubleMoreOperatorTest) {
  EXPECT_TRUE(Real(50) > 49.99);

  EXPECT_FALSE(Real(5.1) > 5.1);
  EXPECT_FALSE(Real("-5.1") > 5.1);
}

TEST(RealTests, rationalFriendMoreOperatorTest) {
  EXPECT_TRUE(Rational(50, 10) > Real(4));

  EXPECT_FALSE(Rational(50, 10) > Real(5));
  EXPECT_FALSE(Rational(50, -10) > Real("5.0"));
}

TEST(RealTests, integerFriendMoreOperatorTest) {
  EXPECT_TRUE(Integer(5) > Real("4.9"));
  EXPECT_TRUE(Integer(5) > Real(-5));

  EXPECT_FALSE(Integer(5) > Real(5));
  EXPECT_FALSE(Integer(-5) > Real("5.0"));
}

TEST(RealTests, doubleFriendMoreOperatorTest) {
  EXPECT_TRUE(4.1 > Real(4));

  EXPECT_FALSE(4.9 > Real(5));
  EXPECT_FALSE(-5.5 > Real("5.5"));
}

TEST(RealTests, lessEqualOperatorTest) {
  EXPECT_TRUE(Real(5) <= Real(10));
  EXPECT_TRUE(Real("5.1") <= Real("5.1"));

  EXPECT_FALSE(Real("5.5") <= Real("5.1"));
  EXPECT_FALSE(Real(5) <= Real(-5));
}

TEST(RealTests, rationalLessEqualOperatorTest) {
  EXPECT_TRUE(Real(5) <= Rational(51, 10));
  EXPECT_TRUE(Real("5.1") <= Rational(51, 10));

  EXPECT_FALSE(Real("5.2") <= Rational(51, 10));
  EXPECT_FALSE(Real(5) <= Rational(50, -10));
}

TEST(RealTests, integerLessEqualOperatorTest) {
  EXPECT_TRUE(Real(5) <= Integer(10));
  EXPECT_TRUE(Real(-5) <= Integer(5));
  EXPECT_TRUE(Real("5") <= Integer(5));

  EXPECT_FALSE(Real("5.1") <= Integer(5));
  EXPECT_FALSE(Real(5) <= Integer(-5));
}

TEST(RealTests, doubleLessEqualOperatorTest) {
  EXPECT_TRUE(Real(5) <= 5.1);
  EXPECT_TRUE(Real(5.01) <= 5.01);

  EXPECT_FALSE(Real("5.1") <= 5.01);
  EXPECT_FALSE(Real("5.55") <= -5.55);
}

TEST(RealTests, rationalFriendLessEqualOperatorTest) {
  EXPECT_TRUE(Rational(49, 10) <= Real(5));
  EXPECT_TRUE(Rational(51, 10) <= Real("5.1"));

  EXPECT_FALSE(Rational(52, 10) <= Real("5.1"));
  EXPECT_FALSE(Rational(50, 10) <= Real(-5));
}

TEST(RealTests, integerFriendLessEqualOperatorTest) {
  EXPECT_TRUE(Integer(4) <= Real(5));
  EXPECT_TRUE(Integer(-5) <= Real(5));
  EXPECT_TRUE(Integer(6) <= Real("6.0"));

  EXPECT_FALSE(Integer(6) <= Real("5.9"));
  EXPECT_FALSE(Integer(5) <= Real(-5));
}

TEST(RealTests, doubleFriendLessEqualOperatorTest) {
  EXPECT_TRUE(4.9 <= Real(5));
  EXPECT_TRUE(5.1 <= Real(5.1));

  EXPECT_FALSE(5.2 <= Real("5.1"));
  EXPECT_FALSE(5.2 <= Real("-5.2"));
}

TEST(RealTests, moreEqualOperatorTest) {
  EXPECT_TRUE(Real(50) >= Real(10));
  EXPECT_TRUE(Real("5.1") >= Real("5.1"));

  EXPECT_FALSE(Real("5.1") >= Real("5.2"));
  EXPECT_FALSE(Real(-5) >= Real(5));
}

TEST(RealTests, rationalMoreEqualOperatorTest) {
  EXPECT_TRUE(Real(50) >= Rational(50, 10));
  EXPECT_TRUE(Real("5.1") >= Rational(51, 10));

  EXPECT_FALSE(Real("5.1") >= Rational(52, 10));
  EXPECT_FALSE(Real("-5.1") >= Rational(51, 10));
}

TEST(RealTests, integerMoreEqualOperatorTest) {
  EXPECT_TRUE(Real(50) >= Integer(10));
  EXPECT_TRUE(Real(50) >= Integer(-50));
  EXPECT_TRUE(Real("5.0") >= Integer(5));

  EXPECT_FALSE(Real("4.9") >= Integer(5));
  EXPECT_FALSE(Real(-5) >= Integer(5));
}

TEST(RealTests, doubleMoreEqualOperatorTest) {
  EXPECT_TRUE(Real(50) >= 49.99);
  EXPECT_TRUE(Real(5.1) >= 5.1);

  EXPECT_FALSE(Real("5.1") >= 5.2);
  EXPECT_FALSE(Real("-5.1") >= 5.1);
}

TEST(RealTests, rationalFriendMoreEqualOperatorTest) {
  EXPECT_TRUE(Rational(50, 10) >= Real(4));
  EXPECT_TRUE(Rational(50, 10) >= Real(5));

  EXPECT_FALSE(Rational(49, 10) >= Real(5));
  EXPECT_FALSE(Rational(50, -10) >= Real("5.0"));
}

TEST(RealTests, integerFriendMoreEqualOperatorTest) {
  EXPECT_TRUE(Integer(5) >= Real("4.9"));
  EXPECT_TRUE(Integer(5) >= Real(-5));
  EXPECT_TRUE(Integer(5) >= Real(5));

  EXPECT_FALSE(Integer(5) >= Real("5.1"));
  EXPECT_FALSE(Integer(-5) >= Real("5.0"));
}

TEST(RealTests, doubleFriendMoreEqualOperatorTest) {
  EXPECT_TRUE(4.1 >= Real(4));
  EXPECT_TRUE(5 >= Real(5));

  EXPECT_FALSE(4.9 >= Real(5));
  EXPECT_FALSE(-5.5 >= Real("5.5"));
}

TEST(RealTests, toStringTest) {
  EXPECT_EQ(Real("2.334455").toString(), "2.334455");
  EXPECT_EQ(Real(11).toString(), "11.0");
  EXPECT_EQ(Real(-11).toString(), "-11.0");
  EXPECT_EQ(
      Real("118219374329847329874632874628734532864532645263452364532614523864152352353214454587245272").toString(),
      "1.1821937432984732987463287462873453286453264526345236453261452386415235235321445*10^89");
  EXPECT_EQ(
      Real("-118219374329847329874632874628734532864532645263452364532614523864152352353214454587245272").toString(),
      "-1.1821937432984732987463287462873453286453264526345236453261452386415235235321445*10^89");
  EXPECT_EQ(
      Real("1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000").toString(),
      "1.0*10^90");
  EXPECT_EQ(
      Real("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000").toString(),
      "-1.0*10^90");
}

TEST(RealTests, getPrecisionTests) {
  Real val = Rational(1, 3);
  EXPECT_EQ(val.getPrecision(), FINTAMATH_PRECISION);
  
  val.setPrecision(10);
  EXPECT_EQ(val.getPrecision(), 10);
}

TEST(RealTests, setPrecisionTests) {
  Real val = Rational(1, 3);

  val.setPrecision(1);
  EXPECT_EQ(val.toString(), "0.3");

  val.setPrecision(2);
  EXPECT_EQ(val.toString(), "0.33");

  val.setPrecision(3);
  EXPECT_EQ(val.toString(), "0.333");

  val.setPrecision(10);
  EXPECT_EQ(val.toString(), "0.3333333333");

  val = -val;

  val.setPrecision(1);
  EXPECT_EQ(val.toString(), "-0.3");

  val.setPrecision(2);
  EXPECT_EQ(val.toString(), "-0.33");

  val.setPrecision(3);
  EXPECT_EQ(val.toString(), "-0.333");

  val.setPrecision(10);
  EXPECT_EQ(val.toString(), "-0.3333333333");

  val = Real("10000000000000000000.37841620837012");
  val.setPrecision(22);
  EXPECT_EQ(val.toString(), "10000000000000000000.38");
  
  val = Real("10000000000000000000.375");
  val.setPrecision(22);
  EXPECT_EQ(val.toString(), "10000000000000000000.38");

  val = Real("0.000000001");
  val.setPrecision(1);
  EXPECT_EQ(val.toString(), "1.0*10^-9");
  
  val = Real("1000000000.1");
  val.setPrecision(1);
  EXPECT_EQ(val.toString(), "1.0*10^9");
}

TEST(RealTests, signTests) {
  EXPECT_EQ(Real(-2).sign(), -1);
  EXPECT_EQ(Real(-1).sign(), -1);
  EXPECT_EQ(Real(0).sign(), 0);
  EXPECT_EQ(Real(1).sign(), 1);
  EXPECT_EQ(Real(2).sign(), 1);
}

TEST(RealTests, isPreciseTests) {
  EXPECT_FALSE(Real(2).isPrecise());
}

TEST(RealTests, isComplexTests) {
  EXPECT_FALSE(Real(2).isComplex());
}

TEST(RealTests, equalsTest) {
  Real a;
  Integer b;
  Integer c(1);

  EXPECT_EQ(a, a);
  EXPECT_EQ(a, Real());
  EXPECT_EQ(Real(), a);
  EXPECT_EQ(a, cast<IMathObject>(Real()));
  EXPECT_EQ(cast<IMathObject>(Real()), a);
  EXPECT_EQ(a, b);
  EXPECT_EQ(b, a);
  EXPECT_NE(a, c);
  EXPECT_NE(c, a);
}

TEST(RealTests, getTypeTest) {
  EXPECT_EQ(Real::getTypeStatic(), MathObjectType::Real);
  EXPECT_EQ(Real().getType(), MathObjectType::Real);
}
