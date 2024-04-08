#include <gtest/gtest.h>

#include "fintamath/numbers/Real.hpp"

#include <unordered_set>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/exceptions/UndefinedException.hpp"

using namespace fintamath;

TEST(RealTests, constructorTest) {
  EXPECT_EQ(Real(), 0);
}

TEST(RealTests, stringConstructorTest) {
  EXPECT_EQ(Real("0").toString(), "0.0");
  EXPECT_EQ(Real("-0").toString(), "-0.0");
  EXPECT_EQ(Real("-93").toString(), "-93.0");
  EXPECT_EQ(Real("-9.3").toString(), "-9.3");
  EXPECT_EQ(Real("0989929039237832000.9302930929333").toString(), "989929039237832000.93");
  EXPECT_EQ(Real(".1").toString(), "0.1");
  EXPECT_EQ(Real("1.").toString(), "1.0");
  EXPECT_EQ(Real("10000000000200000000000000000000000000000000000000000000000000000000000000000000000000000000000").toString(), "1.00000000002*10^94");
  EXPECT_EQ(Real("2*10^2").toString(), "200.0");
  EXPECT_EQ(Real("-2*10^2").toString(), "-200.0");
  EXPECT_EQ(Real("2*10^-2").toString(), "0.02");
  EXPECT_EQ(Real("-2*10^-2").toString(), "-0.02");
  EXPECT_EQ(Real("123.456*10^1000").toString(), "1.23456*10^1002");
  EXPECT_EQ(Real("-123.456*10^1000").toString(), "-1.23456*10^1002");
  EXPECT_EQ(Real("123.456*10^-1000").toString(), "1.23456*10^-998");
  EXPECT_EQ(Real("-123.456*10^-1000").toString(), "-1.23456*10^-998");
  EXPECT_EQ(Real("0.123456*10^1000").toString(), "1.23456*10^999");
  EXPECT_EQ(Real("-0.123456*10^1000").toString(), "-1.23456*10^999");
  EXPECT_EQ(Real("0.123456*10^-1000").toString(), "1.23456*10^-1001");
  EXPECT_EQ(Real("-0.123456*10^-1000").toString(), "-1.23456*10^-1001");

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
  EXPECT_THROW(Real("2*10^2.2"), InvalidInputException);
  EXPECT_THROW(Real("0*10^0"), InvalidInputException);

  EXPECT_THROW(Real("10*10^100000000000000000000"), UndefinedException);
}

TEST(RealTests, rationalConstructorTest) {
  EXPECT_EQ(Real(Rational(2, 5)).toString(), "0.4");
  EXPECT_EQ(Real(Rational(-2, 5)).toString(), "-0.4");
  EXPECT_EQ(Real(Rational(30, 10)).toString(), "3.0");
}

TEST(RealTests, rationalAssignmentOperatorConstructorTest) {
  Real a;
  EXPECT_EQ((a = Rational(2, 4)).toString(), "0.5");

  Real b;
  EXPECT_EQ((b = Rational(1, 3)).toString(5), "0.33333");
}

TEST(RealTests, integerConstructorTest) {
  EXPECT_EQ(Real(Integer(2)).toString(), "2.0");
  EXPECT_EQ(Real(Integer(10)).toString(), "10.0");
}

TEST(RealTests, integerAssignmentOperatorTest) {
  Real a;
  EXPECT_EQ((a = Integer(2)).toString(), "2.0");

  Real b;
  EXPECT_EQ((b = Integer("9182037092803932425434")).toString(), "9.1820370928039324254*10^21");
}

TEST(RealTests, intConstructorTest) {
  EXPECT_EQ(Real(2).toString(), "2.0");
  EXPECT_EQ(Real(-2).toString(), "-2.0");
}

TEST(RealTests, intAssignmentOperatorTest) {
  Real a;
  EXPECT_EQ((a = 2).toString(), "2.0");
}

TEST(RealTests, plusAssignmentOperatorTest) {
  EXPECT_EQ((Real("0.66") += Real("0.33")).toString(), "0.99");
  EXPECT_EQ((Real("-73.85") += Real("2.55")).toString(), "-71.3");
  EXPECT_EQ((Real("73.8") += Real("2.5")).toString(), "76.3");
  EXPECT_EQ((Real("-73.8") += Real("-2.5")).toString(), "-76.3");

  EXPECT_EQ((Real("0") += Real("-0")).toString(), "-0.0");
  EXPECT_EQ((Real("-0") += Real("0")).toString(), "-0.0");
  EXPECT_EQ((Real("-0") += -Real("-0")).toString(), "-0.0");
}

TEST(RealTests, rationalPlusAssignmentOperatorTest) {
  EXPECT_EQ((Real("0.66") += Rational(33, 100)).toString(), "0.99");
  EXPECT_EQ((Real("-73.85") += Rational(51, 20)).toString(), "-71.3");
  EXPECT_EQ((Real("73.8") += Rational(5, 2)).toString(), "76.3");
  EXPECT_EQ((Real("-73.8") += Rational(-5, 2)).toString(), "-76.3");
}

TEST(RealTests, integerPlusAssignmentOperatorTest) {
  EXPECT_EQ((Real(-18) += Integer(2)).toString(), "-16.0");
  EXPECT_EQ((Real(1009) += Integer(4938493849)).toString(), "4938494858.0");
  EXPECT_EQ((Real(6) += Integer(660)).toString(), "666.0");

  EXPECT_EQ((Real("0.66") += Integer(6)).toString(), "6.66");
  EXPECT_EQ((Real("-73.85") += Integer(5)).toString(), "-68.85");
  EXPECT_EQ((Real("73.8") += Integer(5)).toString(), "78.8");
  EXPECT_EQ((Real("-73.8") += Integer(-5)).toString(), "-78.8");
}

TEST(RealTests, intPlusAssignmentOperatorTest) {
  EXPECT_EQ((Real("0.66") += 1).toString(), "1.66");
  EXPECT_EQ((Real("-73.85") += 2).toString(), "-71.85");
  EXPECT_EQ((Real("73.8") += -2).toString(), "71.8");
  EXPECT_EQ((Real("-73.8") += -2).toString(), "-75.8");
}

TEST(RealTests, plusOperatorTest) {
  EXPECT_EQ((Real("0.66") + Real("0.33")).toString(), "0.99");
  EXPECT_EQ((Real("-73.85") + Real("2.55")).toString(), "-71.3");
  EXPECT_EQ((Real("73.8") + Real("2.5")).toString(), "76.3");
  EXPECT_EQ((Real("-73.8") + Real("-2.5")).toString(), "-76.3");
}

TEST(RealTests, rationalPlusOperatorTest) {
  EXPECT_EQ((Real("0.66") + Rational(33, 100)).toString(), "0.99");
  EXPECT_EQ((Real("-73.85") + Rational(51, 20)).toString(), "-71.3");
  EXPECT_EQ((Real("73.8") + Rational(5, 2)).toString(), "76.3");
  EXPECT_EQ((Real("-73.8") + Rational(-5, 2)).toString(), "-76.3");
}

TEST(RealTests, integerPlusOperatorTest) {
  EXPECT_EQ((Real(-18) + Integer(2)).toString(), "-16.0");
  EXPECT_EQ((Real(1009) + Integer(4938493849)).toString(), "4938494858.0");
  EXPECT_EQ((Real(6) + Integer(660)).toString(), "666.0");

  EXPECT_EQ((Real("0.66") + Integer(6)).toString(), "6.66");
  EXPECT_EQ((Real("-73.85") + Integer(5)).toString(), "-68.85");
  EXPECT_EQ((Real("73.8") + Integer(5)).toString(), "78.8");
  EXPECT_EQ((Real("-73.8") + Integer(-5)).toString(), "-78.8");
}

TEST(RealTests, intPlusOperatorTest) {
  EXPECT_EQ((Real("0.66") + 1).toString(), "1.66");
  EXPECT_EQ((Real("-73.85") + 2).toString(), "-71.85");
  EXPECT_EQ((Real("73.8") + -2).toString(), "71.8");
  EXPECT_EQ((Real("-73.8") + -2).toString(), "-75.8");
}

TEST(RealTests, rationalFriendPlusOperatorTest) {
  EXPECT_EQ((Rational(33, 100) + Real("0.66")).toString(), "0.99");
  EXPECT_EQ((Rational(51, 20) + Real("-73.85")).toString(), "-71.3");
  EXPECT_EQ((Rational(5, 2) + Real("73.8")).toString(), "76.3");
  EXPECT_EQ((Rational(-5, 2) + Real("-73.8")).toString(), "-76.3");
}

TEST(RealTests, integerFriendPlusOperatorTest) {
  EXPECT_EQ((Integer(2) + Real(-18)).toString(), "-16.0");
  EXPECT_EQ((Integer(4938493849) + Real(1009)).toString(), "4938494858.0");
  EXPECT_EQ((Integer(660) + Real(6)).toString(), "666.0");

  EXPECT_EQ((Integer(6) + Real("0.66")).toString(), "6.66");
  EXPECT_EQ((Integer(5) + Real("-73.85")).toString(), "-68.85");
  EXPECT_EQ((Integer(5) + Real("73.8")).toString(), "78.8");
  EXPECT_EQ((Integer(-5) + Real("-73.8")).toString(), "-78.8");
}

TEST(RealTests, intFriendPlusOperatorTest) {
  EXPECT_EQ((1 + Real("0.66")).toString(), "1.66");
  EXPECT_EQ((2 + Real("-73.85")).toString(), "-71.85");
  EXPECT_EQ((-2 + Real("73.8")).toString(), "71.8");
  EXPECT_EQ((-2 + Real("-73.8")).toString(), "-75.8");
}

TEST(RealTests, minusAssignmentOperatorTest) {
  EXPECT_EQ((Real("0.66") -= Real("0.22")).toString(), "0.44");
  EXPECT_EQ((Real("-73.85") -= Real("2.55")).toString(), "-76.4");
  EXPECT_EQ((Real("73.8") -= Real("2.5")).toString(), "71.3");
  EXPECT_EQ((Real("-73.8") -= Real("-2.5")).toString(), "-71.3");

  EXPECT_EQ((Real("0") -= Real("0")).toString(), "-0.0");
  EXPECT_EQ((Real("-0") -= Real("-0")).toString(), "-0.0");
  EXPECT_EQ((Real("-0") -= -Real("0")).toString(), "-0.0");
}

TEST(RealTests, rationalMinusAssignmentOperatorTest) {
  EXPECT_EQ((Real("0.66") -= Rational(22, 100)).toString(), "0.44");
  EXPECT_EQ((Real("-73.85") -= Rational(51, 20)).toString(), "-76.4");
  EXPECT_EQ((Real("73.8") -= Rational(5, 2)).toString(), "71.3");
  EXPECT_EQ((Real("-73.8") -= Rational(-5, 2)).toString(), "-71.3");
}

TEST(RealTests, integerMinusAssignmentOperatorTest) {
  EXPECT_EQ((Real(-20) -= Integer(2)).toString(), "-22.0");
  EXPECT_EQ((Real(4938493849) -= Integer(1009)).toString(), "4938492840.0");
  EXPECT_EQ((Real(6) -= Integer(666)).toString(), "-660.0");

  EXPECT_EQ((Real("6.66") -= Integer(6)).toString(), "0.66");
  EXPECT_EQ((Real("-73.85") -= Integer(5)).toString(), "-78.85");
  EXPECT_EQ((Real("73.8") -= Integer(5)).toString(), "68.8");
  EXPECT_EQ((Real("-73.8") -= Integer(-5)).toString(), "-68.8");
}

TEST(RealTests, intMinusAssignmentOperatorTest) {
  EXPECT_EQ((Real("0.66") -= 1).toString(), "-0.34");
  EXPECT_EQ((Real("-73.85") -= 2).toString(), "-75.85");
  EXPECT_EQ((Real("73.8") -= -2).toString(), "75.8");
  EXPECT_EQ((Real("-73.8") -= -2).toString(), "-71.8");
}

TEST(RealTests, minusOperatorTest) {
  EXPECT_EQ((Real("0.66") - Real("0.22")).toString(), "0.44");
  EXPECT_EQ((Real("-73.85") - Real("2.55")).toString(), "-76.4");
  EXPECT_EQ((Real("73.8") - Real("2.5")).toString(), "71.3");
  EXPECT_EQ((Real("-73.8") - Real("-2.5")).toString(), "-71.3");
}

TEST(RealTests, rationalMinusOperatorTest) {
  EXPECT_EQ((Real("0.66") - Rational(22, 100)).toString(), "0.44");
  EXPECT_EQ((Real("-73.85") - Rational(51, 20)).toString(), "-76.4");
  EXPECT_EQ((Real("73.8") - Rational(5, 2)).toString(), "71.3");
  EXPECT_EQ((Real("-73.8") - Rational(-5, 2)).toString(), "-71.3");
}

TEST(RealTests, integerMinusOperatorTest) {
  EXPECT_EQ((Real(-20) - Integer(2)).toString(), "-22.0");
  EXPECT_EQ((Real(4938493849) - Integer(1009)).toString(), "4938492840.0");
  EXPECT_EQ((Real(6) - Integer(666)).toString(), "-660.0");

  EXPECT_EQ((Real("6.66") - Integer(6)).toString(), "0.66");
  EXPECT_EQ((Real("-73.85") - Integer(5)).toString(), "-78.85");
  EXPECT_EQ((Real("73.8") - Integer(5)).toString(), "68.8");
  EXPECT_EQ((Real("-73.8") - Integer(-5)).toString(), "-68.8");
}

TEST(RealTests, intMinusOperatorTest) {
  EXPECT_EQ((Real("0.66") - 1).toString(), "-0.34");
  EXPECT_EQ((Real("-73.85") - 2).toString(), "-75.85");
  EXPECT_EQ((Real("73.8") - -2).toString(), "75.8");
  EXPECT_EQ((Real("-73.8") - -2).toString(), "-71.8");
}

TEST(RealTests, rationalFriendMinusOperatorTest) {
  EXPECT_EQ((Rational(22, 100) - Real("0.66")).toString(), "-0.44");
  EXPECT_EQ((Rational(51, 20) - Real("-73.85")).toString(), "76.4");
  EXPECT_EQ((Rational(5, 2) - Real("73.8")).toString(), "-71.3");
  EXPECT_EQ((Rational(-5, 2) - Real("-73.8")).toString(), "71.3");
}

TEST(RealTests, integerFriendMinusOperatorTest) {
  EXPECT_EQ((Integer(2) - Real(-20)).toString(), "22.0");
  EXPECT_EQ((Integer(1009) - Real(4938493849)).toString(), "-4938492840.0");
  EXPECT_EQ((Integer(666) - Real(6)).toString(), "660.0");

  EXPECT_EQ((Integer(6) - Real("6.66")).toString(), "-0.66");
  EXPECT_EQ((Integer(5) - Real("-73.85")).toString(), "78.85");
  EXPECT_EQ((Integer(5) - Real("73.8")).toString(), "-68.8");
  EXPECT_EQ((Integer(-5) - Real("-73.8")).toString(), "68.8");
}

TEST(RealTests, intFriendMinusOperatorTest) {
  EXPECT_EQ((1 - Real("0.66")).toString(), "0.34");
  EXPECT_EQ((2 - Real("-73.85")).toString(), "75.85");
  EXPECT_EQ((-2 - Real("73.8")).toString(), "-75.8");
  EXPECT_EQ((-2 - Real("-73.8")).toString(), "71.8");
}

TEST(RealTests, multiplyAssignmentOperatorTest) {
  EXPECT_EQ((Real(5) *= Real(2)).toString(), "10.0");
  EXPECT_EQ((Real("2.5") *= Real("-1.1")).toString(), "-2.75");
  EXPECT_EQ((Real("-2.5") *= Real("1.1")).toString(), "-2.75");
  EXPECT_EQ((Real("-2.05") *= Real("-1.1")).toString(), "2.255");

  EXPECT_EQ((Real("0") *= Real("-2")).toString(), "-0.0");
  EXPECT_EQ((Real("-0") *= Real("2")).toString(), "-0.0");
  EXPECT_EQ((Real("-0") *= Real("-2")).toString(), "0.0");
  EXPECT_EQ((Real("-2") *= Real("0")).toString(), "-0.0");
  EXPECT_EQ((Real("2") *= Real("-0")).toString(), "-0.0");
  EXPECT_EQ((Real("-2") *= Real("-0")).toString(), "0.0");
  EXPECT_EQ((Real("0") *= Real("-0")).toString(), "-0.0");
  EXPECT_EQ((Real("-0") *= Real("0")).toString(), "-0.0");
  EXPECT_EQ((Real("-0") *= Real("-0")).toString(), "0.0");
}

TEST(RealTests, rationalMultiplyAssignmentOperatorTest) {
  EXPECT_EQ((Real(5) *= Rational(5, 2)).toString(), "12.5");
  EXPECT_EQ((Real("-2.05") *= Rational(-11, 10)).toString(), "2.255");
  EXPECT_EQ((Real("2.5") *= Rational(-11, 10)).toString(), "-2.75");
}

TEST(RealTests, integerMultiplyAssignmentOperatorTest) {
  EXPECT_EQ((Real(5) *= Integer(2)).toString(), "10.0");
  EXPECT_EQ((Real(5) *= Integer(-2)).toString(), "-10.0");
  EXPECT_EQ((Real("-2.05") *= Integer(-11)).toString(), "22.55");
  EXPECT_EQ((Real("2.5") *= Integer(-11)).toString(), "-27.5");
}

TEST(RealTests, intMultiplyAssignmentOperatorTest) {
  EXPECT_EQ((Real("0.66") *= 3).toString(), "1.98");
  EXPECT_EQ((Real("-73.85") *= 3).toString(), "-221.55");
  EXPECT_EQ((Real("73.8") *= -71).toString(), "-5239.8");
  EXPECT_EQ((Real("-73.8") *= -71).toString(), "5239.8");
}

TEST(RealTests, multiplyOperatorTest) {
  EXPECT_EQ((Real(5) * Real(2)).toString(), "10.0");
  EXPECT_EQ((Real("-2.05") * Real("-1.1")).toString(), "2.255");
  EXPECT_EQ((Real("2.5") * Real("-1.1")).toString(), "-2.75");
}

TEST(RealTests, rationalMultiplyOperatorTest) {
  EXPECT_EQ((Real(5) * Rational(5, 2)).toString(), "12.5");
  EXPECT_EQ((Real("-2.05") * Rational(-11, 10)).toString(), "2.255");
  EXPECT_EQ((Real("2.5") * Rational(-11, 10)).toString(), "-2.75");
}

TEST(RealTests, integerMultiplyOperatorTest) {
  EXPECT_EQ((Real(5) * Integer(2)).toString(), "10.0");
  EXPECT_EQ((Real(5) * Integer(-2)).toString(), "-10.0");
  EXPECT_EQ((Real("-2.05") * Integer(-11)).toString(), "22.55");
  EXPECT_EQ((Real("2.5") * Integer(-11)).toString(), "-27.5");
}

TEST(RealTests, intMultiplyOperatorTest) {
  EXPECT_EQ((Real("0.66") * 3).toString(), "1.98");
  EXPECT_EQ((Real("-73.85") * 3).toString(), "-221.55");
  EXPECT_EQ((Real("73.8") * -71).toString(), "-5239.8");
  EXPECT_EQ((Real("-73.8") * -71).toString(), "5239.8");
}

TEST(RealTests, rationalFriendMultiplyOperatorTest) {
  EXPECT_EQ((Rational(5, 2) * Real(5)).toString(), "12.5");
  EXPECT_EQ((Rational(-11, 10) * Real("-2.05")).toString(), "2.255");
  EXPECT_EQ((Rational(-11, 10) * Real("2.5")).toString(), "-2.75");
}

TEST(RealTests, integerFriendMultiplyOperatorTest) {
  EXPECT_EQ((Integer(2) * Real(5)).toString(), "10.0");
  EXPECT_EQ((Integer(-2) * Real(5)).toString(), "-10.0");
  EXPECT_EQ((Integer(-11) * Real("-2.05")).toString(), "22.55");
  EXPECT_EQ((Integer(-11) * Real("2.5")).toString(), "-27.5");
}

TEST(RealTests, intFriendMultiplyOperatorTest) {
  EXPECT_EQ((3 * Real("0.66")).toString(), "1.98");
  EXPECT_EQ((3 * Real("-73.85")).toString(), "-221.55");
  EXPECT_EQ((-71 * Real("73.8")).toString(), "-5239.8");
  EXPECT_EQ((-71 * Real("-73.8")).toString(), "5239.8");
}

TEST(RealTests, divideAssignmentOperatorTest) {
  EXPECT_EQ((Real(10) /= Real(2)).toString(), "5.0");
  EXPECT_EQ((Real("2.255") /= Real("-1.1")).toString(), "-2.05");
  EXPECT_EQ((Real("-12.1") /= Real("1.1")).toString(), "-11.0");
  EXPECT_EQ((Real("-11") /= Real("-3")).toString(5), "3.6667");

  EXPECT_EQ(Real("0") /= Real("-2"), Real("-0.0"));
  EXPECT_EQ(Real("-0") /= Real("2"), Real("-0.0"));
  EXPECT_EQ(Real("-0") /= Real("-2"), Real("0.0"));
}

TEST(RealTests, rationalDivideAssignmentOperatorTest) {
  EXPECT_EQ((Real(5) /= Rational(2, 5)).toString(), "12.5");
  EXPECT_EQ((Real("-2.255") /= Rational(-11, 10)).toString(), "2.05");
  EXPECT_EQ((Real("12.1") /= Rational(-11, 10)).toString(), "-11.0");
}

TEST(RealTests, integerDivideAssignmentOperatorTest) {
  EXPECT_EQ((Real(10) /= Integer(2)).toString(), "5.0");
  EXPECT_EQ((Real(10) /= Integer(-2)).toString(), "-5.0");
  EXPECT_EQ((Real("22.5") /= Integer(-11)).toString(5), "-2.0455");
  EXPECT_EQ((Real("-27.5") /= Integer(-11)).toString(), "2.5");
}

TEST(RealTests, intDivideAssignmentOperatorTest) {
  EXPECT_EQ((Real("0.66") /= 3).toString(), "0.22");
  EXPECT_EQ((Real("-73.85") /= 3).toString(5), "-24.617");
  EXPECT_EQ((Real("73.8") /= -71).toString(5), "-1.0394");
  EXPECT_EQ((Real("-73.8") /= -71).toString(5), "1.0394");
}

TEST(RealTests, divideOperatorTest) {
  EXPECT_EQ((Real(10) / Real(2)).toString(), "5.0");
  EXPECT_EQ((Real("-2.255") / Real("-1.1")).toString(), "2.05");
  EXPECT_EQ((Real("12.1") / Real("-1.1")).toString(), "-11.0");
}

TEST(RealTests, rationalDivideOperatorTest) {
  EXPECT_EQ((Real(5) / Rational(2, 5)).toString(), "12.5");
  EXPECT_EQ((Real("-2.255") / Rational(-11, 10)).toString(), "2.05");
  EXPECT_EQ((Real("12.1") / Rational(-11, 10)).toString(), "-11.0");
}

TEST(RealTests, integerDivideOperatorTest) {
  EXPECT_EQ((Real(10) / Integer(2)).toString(), "5.0");
  EXPECT_EQ((Real(10) / Integer(-2)).toString(), "-5.0");
  EXPECT_EQ((Real("22.5") / Integer(-11)).toString(5), "-2.0455");
  EXPECT_EQ((Real("-27.5") / Integer(-11)).toString(), "2.5");
}

TEST(RealTests, intDivideOperatorTest) {
  EXPECT_EQ((Real("0.66") / 3).toString(), "0.22");
  EXPECT_EQ((Real("-73.85") / 3).toString(5), "-24.617");
  EXPECT_EQ((Real("73.8") / -71).toString(5), "-1.0394");
  EXPECT_EQ((Real("-73.8") / -71).toString(5), "1.0394");
}

TEST(RealTests, rationalFriendDivideOperatorTest) {
  EXPECT_EQ((Rational(5, 2) / Real(5)).toString(), "0.5");
  EXPECT_EQ((Rational(-11, 10) / Real("-2.5")).toString(), "0.44");
  EXPECT_EQ((Rational(-11, 10) / Real("0.1")).toString(), "-11.0");
}

TEST(RealTests, integerFriendDivideOperatorTest) {
  EXPECT_EQ((Integer(10) / Real(2)).toString(), "5.0");
  EXPECT_EQ((Integer(10) / Real(-2)).toString(), "-5.0");
  EXPECT_EQ((Integer(-6) / Real("1.6")).toString(), "-3.75");
  EXPECT_EQ((Integer(-6) / Real("-1.6")).toString(), "3.75");
}

TEST(RealTests, intFriendDivideOperatorTest) {
  EXPECT_EQ((3 / Real("0.66")).toString(5), "4.5455");
  EXPECT_EQ((3 / Real("-73.85")).toString(5), "-0.040623");
  EXPECT_EQ((-71 / Real("73.8")).toString(5), "-0.96206");
  EXPECT_EQ((-71 / Real("-73.8")).toString(5), "0.96206");
}

TEST(RealTests, unaryPlusOperatorTest) {
  EXPECT_EQ((+Real(-5)).toString(), "-5.0");
  EXPECT_EQ((+Real(5)).toString(), "5.0");

  EXPECT_EQ((+Real("0")).toString(), "0.0");
  EXPECT_EQ((+Real("-0")).toString(), "-0.0");
}

TEST(RealTests, unaryMinusOperatorTest) {
  EXPECT_EQ((-Real(5)).toString(), "-5.0");
  EXPECT_EQ((-Real(-5)).toString(), "5.0");

  EXPECT_EQ((-Real("0")).toString(), "-0.0");
  EXPECT_EQ((-Real("-0")).toString(), "0.0");
}

TEST(RealTests, equalOperatorTest) {
  EXPECT_TRUE(Real("0.5") == Real("0.5"));
  EXPECT_TRUE(Real(-5) == Real(-5));
  EXPECT_TRUE(Real("5.0") == Real(5));

  EXPECT_FALSE(Real("0.5") == Real("1.5"));
  EXPECT_FALSE(Real("-0.5") == Real("0.5"));

  EXPECT_TRUE(Real("-0") == Real("-0"));
  EXPECT_FALSE(Real("-0") == Real("0"));
  EXPECT_FALSE(Real("0") == Real("-0"));
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

TEST(RealTests, intEqualOperatorTest) {
  EXPECT_TRUE(Real("2") == 2);
  EXPECT_TRUE(Real("-2") == -2);

  EXPECT_FALSE(Real("2.1") == 2);
  EXPECT_FALSE(Real("-2") == 2);
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

TEST(RealTests, intFriendEqualOperatorTest) {
  EXPECT_TRUE(2 == Real("2"));
  EXPECT_TRUE(-2 == Real("-2"));

  EXPECT_FALSE(2 == Real("2.1"));
  EXPECT_FALSE(2 == Real("-2"));
}

TEST(RealTests, notEqualOperatorTest) {
  EXPECT_TRUE(Real("0.5") != Real("1.5"));
  EXPECT_TRUE(Real("-0.5") != Real("0.5"));

  EXPECT_FALSE(Real("0.5") != Real("0.5"));
  EXPECT_FALSE(Real(-5) != Real(-5));
  EXPECT_FALSE(Real("5.0") != Real(5));

  EXPECT_FALSE(Real("-0") != Real("-0"));
  EXPECT_TRUE(Real("-0") != Real("0"));
  EXPECT_TRUE(Real("0") != Real("-0"));
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

TEST(RealTests, intNotEqualOperatorTest) {
  EXPECT_TRUE(Real("2.1") != 2);
  EXPECT_TRUE(Real("-2") != 2);

  EXPECT_FALSE(Real("2") != 2);
  EXPECT_FALSE(Real("-2") != -2);
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

TEST(RealTests, intFriendNotEqualOperatorTest) {
  EXPECT_TRUE(2 != Real("2.1"));
  EXPECT_TRUE(2 != Real("-2"));

  EXPECT_FALSE(2 != Real("2"));
  EXPECT_FALSE(-2 != Real("-2"));
}

TEST(RealTests, lessOperatorTest) {
  EXPECT_TRUE(Real(5) < Real(10));

  EXPECT_FALSE(Real("5.1") < Real("5.1"));
  EXPECT_FALSE(Real(5) < Real(-5));

  EXPECT_FALSE(Real("-0") < Real("-0"));
  EXPECT_TRUE(Real("-0") < Real("0"));
  EXPECT_FALSE(Real("0") < Real("-0"));
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

TEST(RealTests, intLessOperatorTest) {
  EXPECT_TRUE(Real("-2") < 2);

  EXPECT_FALSE(Real("2") < 2);
  EXPECT_FALSE(Real("-2") < -2);
  EXPECT_FALSE(Real("2.1") < 2);
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

TEST(RealTests, intFriendLessOperatorTest) {
  EXPECT_TRUE(2 < Real("2.1"));

  EXPECT_FALSE(2 < Real("2"));
  EXPECT_FALSE(-2 < Real("-2"));
  EXPECT_FALSE(2 < Real("-2"));
}

TEST(RealTests, moreOperatorTest) {
  EXPECT_TRUE(Real(50) > Real(10));

  EXPECT_FALSE(Real("5.1") > Real("5.1"));
  EXPECT_FALSE(Real(-5) > Real(5));

  EXPECT_FALSE(Real("-0") > Real("-0"));
  EXPECT_FALSE(Real("-0") > Real("0"));
  EXPECT_TRUE(Real("0") > Real("-0"));
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

TEST(RealTests, intMoreOperatorTest) {
  EXPECT_TRUE(Real("2.1") > 2);

  EXPECT_FALSE(Real("2") > 2);
  EXPECT_FALSE(Real("-2") > -2);
  EXPECT_FALSE(Real("-2") > 2);
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

TEST(RealTests, intFriendMoreOperatorTest) {
  EXPECT_TRUE(2 > Real("-2"));

  EXPECT_FALSE(2 > Real("2"));
  EXPECT_FALSE(-2 > Real("-2"));
  EXPECT_FALSE(2 > Real("2.1"));
}

TEST(RealTests, lessEqualOperatorTest) {
  EXPECT_TRUE(Real(5) <= Real(10));
  EXPECT_TRUE(Real("5.1") <= Real("5.1"));

  EXPECT_FALSE(Real("5.5") <= Real("5.1"));
  EXPECT_FALSE(Real(5) <= Real(-5));

  EXPECT_TRUE(Real("-0") <= Real("-0"));
  EXPECT_TRUE(Real("-0") <= Real("0"));
  EXPECT_FALSE(Real("0") <= Real("-0"));
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

TEST(RealTests, intLessEqualOperatorTest) {
  EXPECT_TRUE(Real("2") <= 2);
  EXPECT_TRUE(Real("-2") <= -2);
  EXPECT_TRUE(Real("-2") <= 2);

  EXPECT_FALSE(Real("2.1") <= 2);
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

TEST(RealTests, intFriendLessEqualOperatorTest) {
  EXPECT_TRUE(2 <= Real("2.1"));
  EXPECT_TRUE(2 <= Real("2"));
  EXPECT_TRUE(-2 <= Real("-2"));

  EXPECT_FALSE(2 <= Real("-2"));
}

TEST(RealTests, moreEqualOperatorTest) {
  EXPECT_TRUE(Real(50) >= Real(10));
  EXPECT_TRUE(Real("5.1") >= Real("5.1"));

  EXPECT_FALSE(Real("5.1") >= Real("5.2"));
  EXPECT_FALSE(Real(-5) >= Real(5));

  EXPECT_TRUE(Real("-0") >= Real("-0"));
  EXPECT_FALSE(Real("-0") >= Real("0"));
  EXPECT_TRUE(Real("0") >= Real("-0"));
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

TEST(RealTests, intMoreEqualOperatorTest) {
  EXPECT_TRUE(Real("2") >= 2);
  EXPECT_TRUE(Real("-2") >= -2);
  EXPECT_TRUE(Real("2.1") >= 2);

  EXPECT_FALSE(Real("-2") >= 2);
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

TEST(RealTests, intFriendMoreEqualOperatorTest) {
  EXPECT_TRUE(2 >= Real("-2"));
  EXPECT_TRUE(2 >= Real("2"));
  EXPECT_TRUE(-2 >= Real("-2"));

  EXPECT_FALSE(2 >= Real("2.1"));
}

TEST(RealTests, toStringTest) {
  EXPECT_EQ(Real(0).toString(), "0.0");
  EXPECT_EQ((-Real(0)).toString(), "-0.0");
  EXPECT_EQ(Real(11).toString(), "11.0");
  EXPECT_EQ(Real(-11).toString(), "-11.0");
  EXPECT_EQ(Real("2.334455").toString(), "2.334455");
  EXPECT_EQ(Real("11821937432984732987").toString(), "11821937432984732987.0");
  EXPECT_EQ(Real("-1182193743298473298").toString(), "-1182193743298473298.0");
  EXPECT_EQ(Real("1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000").toString(), "1.0*10^90");
  EXPECT_EQ(Real("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000").toString(), "-1.0*10^90");
}

TEST(RealTests, toStringPrecisionPrecisionTest) {
  Real val = Rational(1, 3);
  EXPECT_EQ(val.toString(1), "0.3");
  EXPECT_EQ(val.toString(2), "0.33");
  EXPECT_EQ(val.toString(3), "0.333");
  EXPECT_EQ(val.toString(10), "0.3333333333");

  val = -val;
  EXPECT_EQ(val.toString(1), "-0.3");
  EXPECT_EQ(val.toString(2), "-0.33");
  EXPECT_EQ(val.toString(3), "-0.333");
  EXPECT_EQ(val.toString(10), "-0.3333333333");

  val = Real("100000000000000.37841620837012");
  EXPECT_EQ(val.toString(18), "100000000000000.378");

  val = Real("100000000000000.3775");
  EXPECT_EQ(val.toString(18), "100000000000000.378");

  val = Real("0.000000001");
  EXPECT_EQ(val.toString(1), "1.0*10^-9");

  val = Real("1000000000.1");
  EXPECT_EQ(val.toString(1), "1.0*10^9");

  val = Real("10.1");
  EXPECT_EQ(val.toString(1), "1.0*10");

  val = Real("10.1");
  EXPECT_EQ(val.toString(0), "1.0*10");

  Real::ScopedSetPrecision setPrecision(10);
  val = Real("1.3");
  EXPECT_DEBUG_DEATH(val.toString(20), "");
}

TEST(RealTests, getOutputPrecisionTest) {
  EXPECT_EQ(Real().getOutputPrecision(), Real::getPrecision());
}

TEST(RealTests, setOutputPrecisionTest) {
  Real a;
  EXPECT_EQ(a.getOutputPrecision(), Real::getPrecision());

  a.setOutputPrecision(10);
  EXPECT_EQ(a.getOutputPrecision(), 10);

  a.setOutputPrecision(5);
  EXPECT_EQ(a.getOutputPrecision(), 5);

  a.setOutputPrecision(5);
  EXPECT_EQ(a.getOutputPrecision(), 5);

  EXPECT_DEBUG_DEATH(a.setOutputPrecision(6), "");
  EXPECT_DEBUG_DEATH(a.setOutputPrecision(10), "");
}

TEST(RealTests, updatePrecisionTest) {
  {
    Real a = 1;
    a.setOutputPrecision(10);

    Real b = 1;
    b.setOutputPrecision(5);

    a += b;

    EXPECT_EQ(a.getOutputPrecision(), 5);
    EXPECT_EQ(b.getOutputPrecision(), 5);
  }
  {
    Real a = 1;
    a.setOutputPrecision(10);

    Real b = 1;
    b.setOutputPrecision(5);

    b += a;

    EXPECT_EQ(a.getOutputPrecision(), 10);
    EXPECT_EQ(b.getOutputPrecision(), 5);
  }
  {
    Real a = 1;
    a.setOutputPrecision(10);

    Real b = 1;
    b.setOutputPrecision(5);

    a -= b;

    EXPECT_EQ(a.getOutputPrecision(), 5);
    EXPECT_EQ(b.getOutputPrecision(), 5);
  }
  {
    Real a = 1;
    a.setOutputPrecision(10);

    Real b = 1;
    b.setOutputPrecision(5);

    b -= a;

    EXPECT_EQ(a.getOutputPrecision(), 10);
    EXPECT_EQ(b.getOutputPrecision(), 5);
  }
  {
    Real a = 1;
    a.setOutputPrecision(10);

    Real b = 1;
    b.setOutputPrecision(5);

    a *= b;

    EXPECT_EQ(a.getOutputPrecision(), 5);
    EXPECT_EQ(b.getOutputPrecision(), 5);
  }
  {
    Real a = 1;
    a.setOutputPrecision(10);

    Real b = 1;
    b.setOutputPrecision(5);

    b *= a;

    EXPECT_EQ(a.getOutputPrecision(), 10);
    EXPECT_EQ(b.getOutputPrecision(), 5);
  }
  {
    Real a = 1;
    a.setOutputPrecision(10);

    Real b = 1;
    b.setOutputPrecision(5);

    a /= b;

    EXPECT_EQ(a.getOutputPrecision(), 5);
    EXPECT_EQ(b.getOutputPrecision(), 5);
  }
  {
    Real a = 1;
    a.setOutputPrecision(10);

    Real b = 1;
    b.setOutputPrecision(5);

    b /= a;

    EXPECT_EQ(a.getOutputPrecision(), 10);
    EXPECT_EQ(b.getOutputPrecision(), 5);
  }
}

TEST(RealTests, getPrecisionTest) {
  EXPECT_EQ(Real::getPrecision(), 20);
}

TEST(RealTests, getCalculationPrecisionTest) {
  EXPECT_EQ(Real::getCalculationPrecision(), 50);
}

TEST(RealTests, setPrecisionTest) {
  const unsigned currPrecision = Real::getPrecision();

  Real::setPrecision(10);
  EXPECT_EQ(Real::getPrecision(), 10);

  Real::setPrecision(currPrecision);
  EXPECT_EQ(Real::getPrecision(), 20);
}

TEST(RealTests, scopedSetPrecisionTest) {
  const unsigned currPrecision = Real::getPrecision();

  {
    Real::ScopedSetPrecision setPrecision(123);
    EXPECT_EQ(Real::getPrecision(), 123);
  }

  EXPECT_EQ(Real::getPrecision(), currPrecision);
}

TEST(RealTests, signTest) {
  EXPECT_EQ(Real(-2).sign(), -1);
  EXPECT_EQ(Real(-1).sign(), -1);
  EXPECT_EQ(Real("-0").sign(), -1);
  EXPECT_EQ(Real("0").sign(), 0);
  EXPECT_EQ(Real(1).sign(), 1);
  EXPECT_EQ(Real(2).sign(), 1);
}

TEST(RealTests, isZeroTest) {
  EXPECT_TRUE(Real("0").isZero());
  EXPECT_TRUE(Real("-0").isZero());

  EXPECT_FALSE(Real("1").isZero());
  EXPECT_FALSE(Real("-1").isZero());
}

TEST(RealTests, isPreciseTest) {
  EXPECT_FALSE(Real(2).isPrecise());
}

TEST(RealTests, isComplexTest) {
  EXPECT_FALSE(Real(2).isComplex());
}

TEST(RealTests, getClassTest) {
  EXPECT_EQ(Real().getClass()->getName(), "Real");
  EXPECT_EQ(Real().getClass()->getParent(), INumber::getClassStatic());
}

TEST(RealTests, hashTest) {
  constexpr std::hash<Real> hasher;

  EXPECT_EQ(hasher(Real("0")), hasher(Real("0")));
  EXPECT_EQ(hasher(Real("-0")), hasher(Real("-0")));
  EXPECT_EQ(hasher(Real("12")), hasher(Real("12")));
  EXPECT_EQ(hasher(Real("-12")), hasher(Real("-12")));
  EXPECT_EQ(hasher(Real("452734865298734659873246238756987435")), hasher(Real("452734865298734659873246238756987435")));
  EXPECT_EQ(hasher(Real("-452734865298734659873246238756987435")), hasher(Real("-452734865298734659873246238756987435")));
  EXPECT_EQ(hasher(Real("1.4357")), hasher(Real("1.4357")));
  EXPECT_EQ(hasher(Real("-1.4357")), hasher(Real("-1.4357")));
  EXPECT_EQ(hasher(Real("3.3333")), hasher(Real("3.3333")));
  EXPECT_EQ(hasher(Real("-3.3333")), hasher(Real("-3.3333")));
  EXPECT_EQ(hasher(Real("123.00001")), hasher(Real("123.00001")));
  EXPECT_EQ(hasher(Real("-123.00001")), hasher(Real("-123.00001")));
  EXPECT_EQ(hasher(Real("897259832648723648327648273463287.48732648273652873")), hasher(Real("897259832648723648327648273463287.48732648273652873")));
  EXPECT_EQ(hasher(Real("-897259832648723648327648273463287.48732648273652873")), hasher(Real("-897259832648723648327648273463287.48732648273652873")));

  EXPECT_NE(hasher(Real("0")), hasher(Real("-0")));
  EXPECT_NE(hasher(Real("0")), hasher(Real("1")));
  EXPECT_NE(hasher(Real("12")), hasher(Real("13")));
  EXPECT_NE(hasher(Real("-12")), hasher(Real("-13")));
  EXPECT_NE(hasher(Real("452734865298734659873246238756987435")), hasher(Real("452734865298734659873246238756987436")));
  EXPECT_NE(hasher(Real("-452734865298734659873246238756987435")), hasher(Real("-452734865298734659873246238756987436")));
  EXPECT_NE(hasher(Real("1.4357")), hasher(Real("1.4358")));
  EXPECT_NE(hasher(Real("-1.4357")), hasher(Real("-1.4358")));
  EXPECT_NE(hasher(Real("3.3333")), hasher(Real("3.33333")));
  EXPECT_NE(hasher(Real("-3.3333")), hasher(Real("-3.33333")));
  EXPECT_NE(hasher(Real("123.00001")), hasher(Real("123.000001")));
  EXPECT_NE(hasher(Real("-123.00001")), hasher(Real("-123.000001")));
  EXPECT_NE(hasher(Real("897259832648723648327648273463287.48732648273652873")), hasher(Real("897259832648723648327648273463287.48732648273652874")));
  EXPECT_NE(hasher(Real("-897259832648723648327648273463287.48732648273652873")), hasher(Real("-897259832648723648327648273463287.48732648273652874")));
}
