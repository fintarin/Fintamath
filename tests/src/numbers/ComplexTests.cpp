#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/Complex.hpp"

using namespace fintamath;

TEST(ComplexTests, constructorTest) {
  EXPECT_EQ(Complex(), 0);
}

TEST(ComplexTests, moveTest) {
  auto a = Complex(3);
  EXPECT_EQ(a.toString(), "3");

  auto b = std::move(a);
  EXPECT_TRUE(b.toString() == "3" && &a != &b);

  a = std::move(b);
  EXPECT_TRUE(a.toString() == "3" && &a != &b);

  a = std::move(a);
  EXPECT_TRUE(a.toString() == "3" && &a == &a);
}

TEST(ComplexTests, copyTest) {
  auto a = Complex("3");
  EXPECT_EQ(a.toString(), "3");

  auto b = a;
  EXPECT_TRUE(a == b && &a != &b);

  a = b;
  EXPECT_TRUE(a == b && &a != &b);

  a = a;
  EXPECT_TRUE(a == a && &a == &a);
}

TEST(ComplexTests, stringConstructorTest) {
  EXPECT_EQ(Complex("0"), 0);
  EXPECT_EQ(Complex("1"), 1);
  EXPECT_EQ(Complex("2"), 2);
  EXPECT_EQ(Complex("-93"), -93);
  EXPECT_EQ(Complex("-9.3").toString(), "-93/10");
  EXPECT_EQ(Complex("0989929039237832000.9302930929333").toString(), "9899290392378320009302930929333/10000000000000");
  EXPECT_EQ(Complex(".1").toString(), "1/10");
  EXPECT_EQ(Complex("1.").toString(), "1");

  EXPECT_EQ(Complex("0I"), 0);
  EXPECT_EQ(Complex("1I").toString(), "I");
  EXPECT_EQ(Complex("2I").toString(), "2 I");
  EXPECT_EQ(Complex("-93I").toString(), "-93 I");
  EXPECT_EQ(Complex("-9.3I").toString(), "-93/10 I");
  EXPECT_EQ(Complex("0989929039237832000.9302930929333I").toString(), "9899290392378320009302930929333/10000000000000 I");
  EXPECT_EQ(Complex(".1I").toString(), "1/10 I");
  EXPECT_EQ(Complex("1.I").toString(), "I");

  EXPECT_THROW(Complex("--10"), InvalidInputException);
  EXPECT_THROW(Complex("test"), InvalidInputException);
  EXPECT_THROW(Complex(""), InvalidInputException);
  EXPECT_THROW(Complex("+"), InvalidInputException);
  EXPECT_THROW(Complex("939849.0-0023"), InvalidInputException);
  EXPECT_THROW(Complex("a"), InvalidInputException);
  EXPECT_THROW(Complex("a.1"), InvalidInputException);
  EXPECT_THROW(Complex("1.a"), InvalidInputException);
  EXPECT_THROW(Complex("1a.1"), InvalidInputException);
  EXPECT_THROW(Complex("1.1a"), InvalidInputException);
  EXPECT_THROW(Complex(".1."), InvalidInputException);
  EXPECT_THROW(Complex("."), InvalidInputException);
  EXPECT_THROW(Complex("--10.-1"), InvalidInputException);
  EXPECT_THROW(Complex("10.-1"), InvalidInputException);
  EXPECT_THROW(Complex("1-0.1"), InvalidInputException);
  EXPECT_THROW(Complex("10-.1"), InvalidInputException);
  EXPECT_THROW(Complex("10.--1"), InvalidInputException);
  EXPECT_THROW(Complex("1.10.1"), InvalidInputException);
  EXPECT_THROW(Complex("0II"), InvalidInputException);
}

TEST(ComplexTests, intIntConstructorTest) {
  EXPECT_EQ(Complex(2, 1).toString(), "2 + I");
  EXPECT_EQ(Complex(2, -1).toString(), "2 - I");
  EXPECT_EQ(Complex(-2, 1).toString(), "-2 + I");
  EXPECT_EQ(Complex(-2, -1).toString(), "-2 - I");
}

TEST(ComplexTests, numberNumberConstructorTest) {
  EXPECT_EQ(Complex(Integer(2), Integer(1)).toString(), "2 + I");
  EXPECT_EQ(Complex(Integer(2), Integer(-1)).toString(), "2 - I");
  EXPECT_EQ(Complex(Integer(-2), Integer(1)).toString(), "-2 + I");
  EXPECT_EQ(Complex(Integer(-2), Integer(-1)).toString(), "-2 - I");

  EXPECT_EQ(Complex(Rational(2, 3), Rational(1, 2)).toString(), "2/3 + 1/2 I");
  EXPECT_EQ(Complex(Rational(2, 3), Rational(-1, 2)).toString(), "2/3 - 1/2 I");
  EXPECT_EQ(Complex(Rational(-2, 3), Rational(1, 2)).toString(), "-2/3 + 1/2 I");
  EXPECT_EQ(Complex(Rational(-2, 3), Rational(-1, 2)).toString(), "-2/3 - 1/2 I");

  EXPECT_EQ(Complex(Real("2.2"), Real("2.3545")).toString(), "2.2 + 2.3545 I");
  EXPECT_EQ(Complex(Real("-2.2"), Real("2.3545")).toString(), "-2.2 + 2.3545 I");
  EXPECT_EQ(Complex(Real("2.2"), Real("-2.3545")).toString(), "2.2 - 2.3545 I");
  EXPECT_EQ(Complex(Real("-2.2"), Real("-2.3545")).toString(), "-2.2 - 2.3545 I");

  EXPECT_EQ(Complex(Rational(2, 3), Integer(2)).toString(), "2/3 + 2 I");
  EXPECT_EQ(Complex(Integer(3), Rational(2, 3)).toString(), "3 + 2/3 I");
  EXPECT_EQ(Complex(Real("2.2"), Integer(2)).toString(), "2.2 + 2 I");
  EXPECT_EQ(Complex(Integer(3), Real("2.2")).toString(), "3 + 2.2 I");
  EXPECT_EQ(Complex(Real("2.2"), Rational(2, 3)).toString(), "2.2 + 2/3 I");
  EXPECT_EQ(Complex(Rational(3, 2), Real("2.2")).toString(), "3/2 + 2.2 I");

  EXPECT_THROW(Complex(Complex(), Complex()), InvalidInputException);
  EXPECT_THROW(Complex(Complex(), Integer()), InvalidInputException);
  EXPECT_THROW(Complex(Integer(), Complex()), InvalidInputException);
  EXPECT_THROW(Complex(Complex(), Rational()), InvalidInputException);
  EXPECT_THROW(Complex(Rational(), Complex()), InvalidInputException);
  EXPECT_THROW(Complex(Complex(), Real()), InvalidInputException);
  EXPECT_THROW(Complex(Real(), Complex()), InvalidInputException);
}

TEST(ComplexTests, integerConstructorTest) {
  EXPECT_EQ(Complex(Integer("122432964238764283746823")), Integer("122432964238764283746823"));
}

TEST(ComplexTests, integerAssignmentOperatorTest) {
  Complex b;
  EXPECT_EQ(b = Integer("39743491820370928039"), Complex("39743491820370928039"));
}

TEST(ComplexTests, rationalConstructorTest) {
  EXPECT_EQ(Complex(Rational("122432964.238764283746823")), Rational(Integer("122432964238764283746823"), Integer("1000000000000000")));
}

TEST(ComplexTests, rationalAssignmentOperatorTest) {
  Complex b;
  EXPECT_EQ(b = Rational("3974349182.0370928039"), Rational(Integer("39743491820370928039"), Integer("10000000000")));
}

TEST(ComplexTests, realConstructorTest) {
  EXPECT_EQ(Complex(Real("12243296423876.4283746823")), Real("12243296423876.4283746823"));
}

TEST(ComplexTests, realAssignmentOperatorTest) {
  Complex b;
  EXPECT_EQ(b = Real("3974349182.0370928039"), Real("3974349182.0370928039"));
}

TEST(ComplexTests, intConstructorTest) {
  EXPECT_EQ(Complex(2), 2);
}

TEST(ComplexTests, intAssignmentOperatorTest) {
  Complex a;
  EXPECT_EQ(a = 2, 2);
}

TEST(ComplexTests, plusAssignmentOperatorTest) {
  EXPECT_EQ(Complex(2, 3) += Complex(5, 2), Complex(7, 5));
  EXPECT_EQ(Complex(-738, 10) += Complex(5, 2), Complex(-733, 12));
  EXPECT_EQ(Complex(738, 10) += Complex(5, 2), Complex(743, 12));
  EXPECT_EQ(Complex(-738, 10) += Complex(-5, 2), Complex(-743, 12));
}

TEST(ComplexTests, integerPlusAssignmentOperatorTest) {
  EXPECT_EQ(Complex(-10) += Integer(5), Integer(-5));
  EXPECT_EQ(Complex(2, 3) += Integer(-5), Complex(-3, 3));
}

TEST(ComplexTests, rationalPlusAssignmentOperatorTest) {
  EXPECT_EQ(Complex(-10) += Rational(5, 2), Rational(-15, 2));
  EXPECT_EQ(Complex(2, 3) += Rational(-5, 2), Complex(Rational(-1, 2), Integer(3)));
}

TEST(ComplexTests, realPlusAssignmentOperatorTest) {
  EXPECT_EQ((Complex(-10) += Real("2.2")).toString(), "-7.8");
  EXPECT_EQ((Complex(2, 3) += Real("-2.2")).toString(), "-0.2 + 3 I");
}

TEST(ComplexTests, intPlusAssignmentOperatorTest) {
  EXPECT_EQ(Complex(-10) += 5, -5);
  EXPECT_EQ(Complex(2, 3) += -5, Complex(-3, 3));
}

TEST(ComplexTests, plusOperatorTest) {
  EXPECT_EQ(Complex(170, 15) + Complex(-5, 2), Complex(165, 17));
  EXPECT_EQ(Complex(17, 19) + Complex(53, 5), Complex(70, 24));
  EXPECT_EQ(Complex(170, 12) + Complex(2, 5), Complex(172, 17));
}

TEST(ComplexTests, integerPlusOperatorTest) {
  EXPECT_EQ(Complex(170) + Integer(-5), 165);
  EXPECT_EQ(Complex(170, 12) + Integer(2), Complex(172, 12));
}

TEST(ComplexTests, rationalPlusOperatorTest) {
  EXPECT_EQ(Complex(170) + Rational(-5, 2), Rational(335, 2));
  EXPECT_EQ(Complex(170, 12) + Rational(2, 5), Complex(Rational(852, 5), Integer(12)));
}

TEST(ComplexTests, realPlusOperatorTest) {
  EXPECT_EQ((Complex(170) + Real("2.4")).toString(), "172.4");
  EXPECT_EQ((Complex(170, 12) + Real("2.5")).toString(), "172.5 + 12 I");
}

TEST(ComplexTests, intPlusOperatorTest) {
  EXPECT_EQ(Complex(170) + -5, 165);
  EXPECT_EQ(Complex(170, 12) + 2, Complex(172, 12));
}

TEST(ComplexTests, integerFriendPlusOperatorTest) {
  EXPECT_EQ(Integer(-5) + Complex(170), 165);
  EXPECT_EQ(Integer(2) + Complex(170, 12), Complex(172, 12));
}

TEST(ComplexTests, rationalFriendPlusOperatorTest) {
  EXPECT_EQ(Rational(-5, 2) + Complex(170), Rational(335, 2));
  EXPECT_EQ(Rational(2, 5) + Complex(170, 12), Complex(Rational(852, 5), Integer(12)));
}

TEST(ComplexTests, realFriendPlusOperatorTest) {
  EXPECT_EQ((Real("2.4") + Complex(170)).toString(), "172.4");
  EXPECT_EQ((Real("2.5") + Complex(170, 12)).toString(), "172.5 + 12 I");
}

TEST(ComplexTests, intFriendPlusOperatorTest) {
  EXPECT_EQ(-5 + Complex(170), 165);
  EXPECT_EQ(2 + Complex(170, 12), Complex(172, 12));
}

TEST(ComplexTests, minusAssignmentOperatorTest) {
  EXPECT_EQ(Complex(2, 3) -= Complex(5, 2), Complex(-3, 1));
  EXPECT_EQ(Complex(-738, 10) -= Complex(5, 2), Complex(-743, 8));
  EXPECT_EQ(Complex(738, 10) -= Complex(5, 2), Complex(733, 8));
  EXPECT_EQ(Complex(-738, 10) -= Complex(-5, 2), Complex(-733, 8));
}

TEST(ComplexTests, integerMinusAssignmentOperatorTest) {
  EXPECT_EQ(Complex(-10) -= Integer(5), Integer(-15));
  EXPECT_EQ(Complex(2, 3) -= Integer(-5), Complex(7, 3));
}

TEST(ComplexTests, rationalMinusAssignmentOperatorTest) {
  EXPECT_EQ(Complex(-10) -= Rational(5, 2), Rational(-25, 2));
  EXPECT_EQ(Complex(2, 3) -= Rational(-5, 2), Complex(Rational(9, 2), Integer(3)));
}

TEST(ComplexTests, realMinusAssignmentOperatorTest) {
  EXPECT_EQ((Complex(-10) -= Real("2.2")).toString(), "-12.2");
  EXPECT_EQ((Complex(2, 3) -= Real("-2.2")).toString(), "4.2 + 3 I");
}

TEST(ComplexTests, intMinusAssignmentOperatorTest) {
  EXPECT_EQ(Complex(-10) -= 5, -15);
  EXPECT_EQ(Complex(2, 3) -= -5, Complex(7, 3));
}

TEST(ComplexTests, minusOperatorTest) {
  EXPECT_EQ(Complex(170, 15) - Complex(-5, 2), Complex(175, 13));
  EXPECT_EQ(Complex(17, 19) - Complex(53, 5), Complex(-36, 14));
  EXPECT_EQ(Complex(170, 12) - Complex(2, 5), Complex(168, 7));
}

TEST(ComplexTests, integerMinusOperatorTest) {
  EXPECT_EQ(Complex(170) - Integer(-5), 175);
  EXPECT_EQ(Complex(170, 12) - Integer(2), Complex(168, 12));
}

TEST(ComplexTests, rationalMinusOperatorTest) {
  EXPECT_EQ(Complex(170) - Rational(-5, 2), Rational(345, 2));
  EXPECT_EQ(Complex(170, 12) - Rational(2, 5), Complex(Rational(848, 5), Integer(12)));
}

TEST(ComplexTests, realMinusOperatorTest) {
  EXPECT_EQ((Complex(170) - Real("2.4")).toString(), "167.6");
  EXPECT_EQ((Complex(170, 12) - Real("2.5")).toString(), "167.5 + 12 I");
}

TEST(ComplexTests, intMinusOperatorTest) {
  EXPECT_EQ(Complex(170) - -5, 175);
  EXPECT_EQ(Complex(170, 12) - 2, Complex(168, 12));
}

TEST(ComplexTests, integerFriendMinusOperatorTest) {
  EXPECT_EQ(Integer(-5) - Complex(170), -175);
  EXPECT_EQ(Integer(2) - Complex(170, 12), Complex(-168, -12));
}

TEST(ComplexTests, rationalFriendMinusOperatorTest) {
  EXPECT_EQ(Rational(-5, 2) - Complex(170), Rational(-345, 2));
  EXPECT_EQ(Rational(2, 5) - Complex(170, 12), Complex(Rational(-848, 5), Integer(-12)));
}

TEST(ComplexTests, realFriendMinusOperatorTest) {
  EXPECT_EQ((Real("2.4") - Complex(170)).toString(), "-167.6");
  EXPECT_EQ((Real("2.5") - Complex(170, 12)).toString(), "-167.5 - 12 I");
}

TEST(ComplexTests, intFriendMinusOperatorTest) {
  EXPECT_EQ(-5 - Complex(170), -175);
  EXPECT_EQ(2 - Complex(170, 12), Complex(-168, -12));
}

TEST(ComplexTests, multiplyAssignmentOperatorTest) {
  EXPECT_EQ(Complex(0, 0) *= Complex(0, 0), Complex(0));
  EXPECT_EQ(Complex(0, 0) *= Complex(0, 2), Complex(0));
  EXPECT_EQ(Complex(0, 0) *= Complex(2, 0), Complex(0));
  EXPECT_EQ(Complex(0, 0) *= Complex(2, 2), Complex(0));
  EXPECT_EQ(Complex(0, 2) *= Complex(0, 0), Complex(0));
  EXPECT_EQ(Complex(0, 2) *= Complex(0, 2), Complex(-4));
  EXPECT_EQ(Complex(0, 2) *= Complex(2, 0), Complex(0, 4));
  EXPECT_EQ(Complex(0, 2) *= Complex(2, 2), Complex(-4, 4));
  EXPECT_EQ(Complex(2, 0) *= Complex(0, 0), Complex(0));
  EXPECT_EQ(Complex(2, 0) *= Complex(0, 2), Complex(0, 4));
  EXPECT_EQ(Complex(2, 0) *= Complex(2, 0), Complex(4));
  EXPECT_EQ(Complex(2, 0) *= Complex(2, 2), Complex(4, 4));
  EXPECT_EQ(Complex(2, 2) *= Complex(0, 0), Complex(0));
  EXPECT_EQ(Complex(2, 2) *= Complex(0, 2), Complex(-4, 4));
  EXPECT_EQ(Complex(2, 2) *= Complex(2, 0), Complex(4, 4));
  EXPECT_EQ(Complex(2, 2) *= Complex(2, 2), Complex(0, 8));

  EXPECT_EQ(Complex(0, 0) *= Complex(0, 0), Complex(0));
  EXPECT_EQ(Complex(0, 0) *= Complex(0, -2), Complex(0));
  EXPECT_EQ(Complex(0, 0) *= Complex(-2, 0), Complex(0));
  EXPECT_EQ(Complex(0, 0) *= Complex(-2, -2), Complex(0));
  EXPECT_EQ(Complex(0, 2) *= Complex(0, 0), Complex(0));
  EXPECT_EQ(Complex(0, 2) *= Complex(0, -2), Complex(4));
  EXPECT_EQ(Complex(0, 2) *= Complex(-2, 0), Complex(0, -4));
  EXPECT_EQ(Complex(0, 2) *= Complex(-2, -2), Complex(4, -4));
  EXPECT_EQ(Complex(2, 0) *= Complex(0, 0), Complex(0));
  EXPECT_EQ(Complex(2, 0) *= Complex(0, -2), Complex(0, -4));
  EXPECT_EQ(Complex(2, 0) *= Complex(-2, 0), Complex(-4));
  EXPECT_EQ(Complex(2, 0) *= Complex(-2, -2), Complex(-4, -4));
  EXPECT_EQ(Complex(2, 2) *= Complex(0, 0), Complex(0));
  EXPECT_EQ(Complex(2, 2) *= Complex(0, -2), Complex(4, -4));
  EXPECT_EQ(Complex(2, 2) *= Complex(-2, 0), Complex(-4, -4));
  EXPECT_EQ(Complex(2, 2) *= Complex(-2, -2), Complex(0, -8));

  EXPECT_EQ(Complex(2, 3) *= Complex(1, 0), Complex(2, 3));
  EXPECT_EQ(Complex(2, 3) *= Complex(0, 1), Complex(-3, 2));
  EXPECT_EQ(Complex(2, 3) *= Complex(1, 1), Complex(-1, 5));

  EXPECT_EQ(Complex(738, 10) *= Complex(5, 2), Complex(3670, 1526));
  EXPECT_EQ(Complex(-738, 10) *= Complex(5, 2), Complex(-3710, -1426));
  EXPECT_EQ(Complex(-738, 10) *= Complex(-5, 2), Complex(3670, -1526));
}

TEST(ComplexTests, integerMultiplyAssignmentOperatorTest) {
  EXPECT_EQ(Complex(-10) *= Integer(5), Integer(-50));
  EXPECT_EQ(Complex(2, 3) *= Integer(-5), Complex(-10, -15));
}

TEST(ComplexTests, rationalMultiplyAssignmentOperatorTest) {
  EXPECT_EQ(Complex(-10) *= Rational(5, 2), Integer(-25));
  EXPECT_EQ(Complex(2, 3) *= Rational(-5, 2), Complex(Integer(-5), Rational(-15, 2)));
}

TEST(ComplexTests, realMultiplyAssignmentOperatorTest) {
  EXPECT_EQ((Complex(-10) *= Real("2.2")).toString(), "-22.0");
  EXPECT_EQ((Complex(2, 3) *= Real("-2.2")).toString(), "-4.4 - 6.6 I");
}

TEST(ComplexTests, intMultiplyAssignmentOperatorTest) {
  EXPECT_EQ(Complex(-10) *= 5, -50);
  EXPECT_EQ(Complex(2, 3) *= -5, Complex(-10, -15));
}

TEST(ComplexTests, multiplyOperatorTest) {
  EXPECT_EQ(Complex(170, 15) * Complex(-5, 2), Complex(-880, 265));
  EXPECT_EQ(Complex(17, 19) * Complex(53, 5), Complex(806, 1092));
  EXPECT_EQ(Complex(170, 12) * Complex(2, 5), Complex(280, 874));
}

TEST(ComplexTests, integerMultiplyOperatorTest) {
  EXPECT_EQ(Complex(170) * Integer(-5), -850);
  EXPECT_EQ(Complex(170, 12) * Integer(2), Complex(340, 24));
}

TEST(ComplexTests, rationalMultiplyOperatorTest) {
  EXPECT_EQ(Complex(170) * Rational(-5, 2), Integer(-425));
  EXPECT_EQ(Complex(170, 12) * Rational(2, 5), Complex(Integer(68), Rational(24, 5)));
}

TEST(ComplexTests, realMultiplyOperatorTest) {
  EXPECT_EQ((Complex(170) * Real("2.4")).toString(), "408.0");
  EXPECT_EQ((Complex(170, 12) * Real("2.5")).toString(), "425.0 + 30.0 I");
}

TEST(ComplexTests, intMultiplyOperatorTest) {
  EXPECT_EQ(Complex(170) * -5, -850);
  EXPECT_EQ(Complex(170, 12) * 2, Complex(340, 24));
}

TEST(ComplexTests, integerFriendMultiplyOperatorTest) {
  EXPECT_EQ(Integer(-5) * Complex(170), -850);
  EXPECT_EQ(Integer(2) * Complex(170, 12), Complex(340, 24));
}

TEST(ComplexTests, rationalFriendMultiplyOperatorTest) {
  EXPECT_EQ(Rational(-5, 2) * Complex(170), Rational(-425));
  EXPECT_EQ(Rational(2, 5) * Complex(170, 12), Complex(Integer(68), Rational(24, 5)));
}

TEST(ComplexTests, realFriendMultiplyOperatorTest) {
  EXPECT_EQ((Real("2.4") * Complex(170)).toString(), "408.0");
  EXPECT_EQ((Real("2.5") * Complex(170, 12)).toString(), "425.0 + 30.0 I");
}

TEST(ComplexTests, intFriendMultiplyOperatorTest) {
  EXPECT_EQ(-5 * Complex(170), -850);
  EXPECT_EQ(2 * Complex(170, 12), Complex(340, 24));
}

TEST(ComplexTests, divideAssignmentOperatorTest) {
  EXPECT_EQ(Complex(0, 0) /= Complex(0, 2), Complex(0));
  EXPECT_EQ(Complex(0, 0) /= Complex(2, 0), Complex(0));
  EXPECT_EQ(Complex(0, 0) /= Complex(2, 2), Complex(0));
  EXPECT_EQ(Complex(0, 2) /= Complex(0, 2), Complex(1));
  EXPECT_EQ(Complex(0, 2) /= Complex(2, 0), Complex(0, 1));
  EXPECT_EQ(Complex(0, 2) /= Complex(2, 2), Complex(Rational(1, 2), Rational(1, 2)));
  EXPECT_EQ(Complex(2, 0) /= Complex(0, 2), Complex(0, -1));
  EXPECT_EQ(Complex(2, 0) /= Complex(2, 0), Complex(1));
  EXPECT_EQ(Complex(2, 0) /= Complex(2, 2), Complex(Rational(1, 2), Rational(-1, 2)));
  EXPECT_EQ(Complex(2, 2) /= Complex(0, 2), Complex(1, -1));
  EXPECT_EQ(Complex(2, 2) /= Complex(2, 0), Complex(1, 1));
  EXPECT_EQ(Complex(2, 2) /= Complex(2, 2), Complex(1));

  EXPECT_EQ(Complex(0, 0) /= Complex(0, -2), Complex(0));
  EXPECT_EQ(Complex(0, 0) /= Complex(-2, 0), Complex(0));
  EXPECT_EQ(Complex(0, 0) /= Complex(-2, -2), Complex(0));
  EXPECT_EQ(Complex(0, 2) /= Complex(0, -2), Complex(-1));
  EXPECT_EQ(Complex(0, 2) /= Complex(-2, 0), Complex(0, -1));
  EXPECT_EQ(Complex(0, 2) /= Complex(-2, -2), Complex(Rational(-1, 2), Rational(-1, 2)));
  EXPECT_EQ(Complex(2, 0) /= Complex(0, -2), Complex(0, 1));
  EXPECT_EQ(Complex(2, 0) /= Complex(-2, 0), Complex(-1));
  EXPECT_EQ(Complex(2, 0) /= Complex(-2, -2), Complex(Rational(-1, 2), Rational(1, 2)));
  EXPECT_EQ(Complex(2, 2) /= Complex(0, -2), Complex(-1, 1));
  EXPECT_EQ(Complex(2, 2) /= Complex(-2, 0), Complex(-1, -1));
  EXPECT_EQ(Complex(2, 2) /= Complex(-2, -2), Complex(-1));

  EXPECT_EQ(Complex(2, 3) /= Complex(1, 0), Complex(2, 3));
  EXPECT_EQ(Complex(2, 3) /= Complex(0, 1), Complex(3, -2));
  EXPECT_EQ(Complex(2, 3) /= Complex(1, 1), Complex(Rational(5, 2), Rational(1, 2)));

  EXPECT_EQ(Complex(738, 10) /= Complex(5, 2), Complex(Rational(3710, 29), Rational(-1426, 29)));
  EXPECT_EQ(Complex(-738, 10) /= Complex(5, 2), Complex(Rational(-3670, 29), Rational(1526, 29)));
  EXPECT_EQ(Complex(-738, 10) /= Complex(-5, 2), Complex(Rational(3710, 29), Rational(1426, 29)));

  EXPECT_THROW(Complex(0, 0) /= Complex(0, 0), UndefinedException);
  EXPECT_THROW(Complex(2, 3) /= Complex(0, 0), UndefinedException);
}

TEST(ComplexTests, integerDivideAssignmentOperatorTest) {
  EXPECT_EQ(Complex(-10) /= Integer(5), Integer(-2));
  EXPECT_EQ(Complex(2, 3) /= Integer(-5), Complex(Rational(-2, 5), Rational(-3, 5)));
}

TEST(ComplexTests, rationalDivideAssignmentOperatorTest) {
  EXPECT_EQ(Complex(-10) /= Rational(5, 2), Integer(-4));
  EXPECT_EQ(Complex(2, 3) /= Rational(-5, 2), Complex(Rational(-4, 5), Rational(-6, 5)));
}

TEST(ComplexTests, realDivideAssignmentOperatorTest) {
  EXPECT_EQ((Complex(-10) /= Real("2.2")).toString(), "-4.5454545454545454545454545454545454545454545454545454545454545454545454545454545");
  EXPECT_EQ((Complex(2, 3) /= Real("-2.2")).toString(), "-0.90909090909090909090909090909090909090909090909090909090909090909090909090909091 - 1.3636363636363636363636363636363636363636363636363636363636363636363636363636364 I");
}

TEST(ComplexTests, intDivideAssignmentOperatorTest) {
  EXPECT_EQ(Complex(-10) /= 5, -2);
  EXPECT_EQ(Complex(2, 3) /= -5, Complex(Rational(-2, 5), Rational(-3, 5)));
}

TEST(ComplexTests, divideOperatorTest) {
  EXPECT_EQ(Complex(170, 15) / Complex(-5, 2), Complex(Rational(-820, 29), Rational(-415, 29)));
  EXPECT_EQ(Complex(17, 19) / Complex(53, 5), Complex(Rational(498, 1417), Rational(461, 1417)));
  EXPECT_EQ(Complex(170, 12) / Complex(2, 5), Complex(Rational(400, 29), Rational(-826, 29)));
}

TEST(ComplexTests, integerDivideOperatorTest) {
  EXPECT_EQ(Complex(170) / Integer(-5), -34);
  EXPECT_EQ(Complex(170, 12) / Integer(2), Complex(85, 6));
}

TEST(ComplexTests, rationalDivideOperatorTest) {
  EXPECT_EQ(Complex(170) / Rational(-5, 2), Integer(-68));
  EXPECT_EQ(Complex(170, 12) / Rational(2, 5), Complex(425, 30));
}

TEST(ComplexTests, realDivideOperatorTest) {
  EXPECT_EQ((Complex(170) / Real("2.4")).toString(), "70.833333333333333333333333333333333333333333333333333333333333333333333333333333");
  EXPECT_EQ((Complex(170, 12) / Real("2.5")).toString(), "68.0 + 4.8 I");
}

TEST(ComplexTests, intDivideOperatorTest) {
  EXPECT_EQ(Complex(170) / -5, -34);
  EXPECT_EQ(Complex(170, 12) / 2, Complex(85, 6));
}

TEST(ComplexTests, integerFriendDivideOperatorTest) {
  EXPECT_EQ(Integer(-5) / Complex(170), Rational(-1, 34));
  EXPECT_EQ(Integer(2) / Complex(170, 12), Complex(Rational(85, 7261), Rational(-6, 7261)));
}

TEST(ComplexTests, rationalFriendDivideOperatorTest) {
  EXPECT_EQ(Rational(-5, 2) / Complex(170), Rational(-1, 68));
  EXPECT_EQ(Rational(2, 5) / Complex(170, 12), Complex(Rational(17, 7261), Rational(-6, 36305)));
}

TEST(ComplexTests, realFriendDivideOperatorTest) {
  EXPECT_EQ((Real("2.4") / Complex(170)).toString(), "0.014117647058823529411764705882352941176470588235294117647058823529411764705882353");
  EXPECT_EQ((Real("2.5") / Complex(170, 12)).toString(), "0.014632970665197631180278198595234816141027406693292934857457650461368957443878254 - 0.0010329155763668916127255199008401046687784051783500895193499517972731028783914061 I");
}

TEST(ComplexTests, intFriendDivideOperatorTest) {
  EXPECT_EQ(-5 / Complex(170), Rational(-1, 34));
  EXPECT_EQ(2 / Complex(170, 12), Complex(Rational(85, 7261), Rational(-6, 7261)));
}

TEST(ComplexTests, unaryPlusOperatorTest) {
  EXPECT_EQ(+Complex(-5), -5);
  EXPECT_EQ(+Complex(-5, 2), Complex(-5, 2));
}

TEST(ComplexTests, unaryMinusOperatorTest) {
  EXPECT_EQ(-Complex(5), -5);
  EXPECT_EQ(-Complex(-5, 2), Complex(5, -2));
}

TEST(ComplexTests, equalOperatorTest) {
  EXPECT_TRUE(Complex(1, 2) == Complex(1, 2));
  EXPECT_TRUE(Complex(2, 0) == Complex(2, 0));
  EXPECT_TRUE(Complex(0, 2) == Complex(0, 2));

  EXPECT_FALSE(Complex(1, 2) == Complex(1, 3));
  EXPECT_FALSE(Complex(1, 2) == Complex(2, 2));
  EXPECT_FALSE(Complex(3, 2) == Complex(2, 3));
}

TEST(ComplexTests, integerEqualOperatorTest) {
  EXPECT_TRUE(Complex(500) == Integer(500));
}

TEST(ComplexTests, rationalEqualOperatorTest) {
  EXPECT_TRUE(Complex(Rational(1, 2)) == Rational(1, 2));
}

TEST(ComplexTests, realEqualOperatorTest) {
  EXPECT_TRUE(Complex(Real("2.2")) == Real("2.2"));
}

TEST(ComplexTests, intEqualOperatorTest) {
  EXPECT_TRUE(Complex(500) == 500);
}

TEST(ComplexTests, integerFriendEqualOperatorTest) {
  EXPECT_TRUE(Integer(500) == Complex(500));
}

TEST(ComplexTests, rationalFriendEqualOperatorTest) {
  EXPECT_TRUE(Rational(1, 2) == Complex(Rational(1, 2)));
}

TEST(ComplexTests, realFriendEqualOperatorTest) {
  EXPECT_TRUE(Real("2.2") == Complex(Real("2.2")));
}

TEST(ComplexTests, intFriendEqualOperatorTest) {
  EXPECT_TRUE(500 == Complex(500));
}

TEST(ComplexTests, notEqualOperatorTest) {
  EXPECT_FALSE(Complex(1, 2) != Complex(1, 2));
  EXPECT_FALSE(Complex(2, 0) != Complex(2, 0));
  EXPECT_FALSE(Complex(0, 2) != Complex(0, 2));

  EXPECT_TRUE(Complex(1, 2) != Complex(1, 3));
  EXPECT_TRUE(Complex(1, 2) != Complex(2, 2));
  EXPECT_TRUE(Complex(3, 2) != Complex(2, 3));
}

TEST(ComplexTests, integerNotEqualOperatorTest) {
  EXPECT_FALSE(Complex(500) != Integer(500));
}

TEST(ComplexTests, rationalNotEqualOperatorTest) {
  EXPECT_FALSE(Complex(Rational(1, 2)) != Rational(1, 2));
}

TEST(ComplexTests, realNotEqualOperatorTest) {
  EXPECT_FALSE(Complex(Real("2.2")) != Real("2.2"));
}

TEST(ComplexTests, intNotEqualOperatorTest) {
  EXPECT_FALSE(Complex(500) != 500);
}

TEST(ComplexTests, integerFriendNotEqualOperatorTest) {
  EXPECT_FALSE(Integer(500) != Complex(500));
}

TEST(ComplexTests, rationalFriendNotEqualOperatorTest) {
  EXPECT_FALSE(Rational(1, 2) != Complex(Rational(1, 2)));
}

TEST(ComplexTests, realFriendNotEqualOperatorTest) {
  EXPECT_FALSE(Real("2.2") != Complex(Real("2.2")));
}

TEST(ComplexTests, intFriendNotEqualOperatorTest) {
  EXPECT_FALSE(500 != Complex(500));
}

TEST(ComplexTests, lessOperatorTest) {
  EXPECT_FALSE(Complex(0, 0) < Complex(0, 0));
  EXPECT_TRUE(Complex(0, 0) < Complex(0, 1));
  EXPECT_TRUE(Complex(0, 0) < Complex(1, 0));
  EXPECT_TRUE(Complex(0, 0) < Complex(1, 1));

  EXPECT_FALSE(Complex(1, 1) < Complex(1, 1));
  EXPECT_TRUE(Complex(1, 1) < Complex(1, 2));
  EXPECT_TRUE(Complex(1, 1) < Complex(2, 1));
  EXPECT_TRUE(Complex(1, 1) < Complex(2, 2));

  EXPECT_TRUE(Complex(1, 2) < Complex(2, 1));
  EXPECT_FALSE(Complex(2, 1) < Complex(1, 2));

  EXPECT_FALSE(Complex(0, 0) < Complex(0, -1));
  EXPECT_FALSE(Complex(0, 0) < Complex(-1, 0));
  EXPECT_FALSE(Complex(0, 0) < Complex(-1, -1));

  EXPECT_FALSE(Complex(-1, -1) < Complex(-1, -1));
  EXPECT_FALSE(Complex(-1, -1) < Complex(-1, -2));
  EXPECT_FALSE(Complex(-1, -1) < Complex(-2, -1));
  EXPECT_FALSE(Complex(-1, -1) < Complex(-2, -2));

  EXPECT_FALSE(Complex(-1, -2) < Complex(-2, -1));
  EXPECT_TRUE(Complex(-2, -1) < Complex(-1, -2));
}

TEST(ComplexTests, integerLessOperatorTest) {
  EXPECT_TRUE(Complex(500, 1) < Integer(501));
}

TEST(ComplexTests, rationalLessOperatorTest) {
  EXPECT_FALSE(Complex(Rational(1, 2), Integer(1)) < Rational(1, 3));
}

TEST(ComplexTests, realLessOperatorTest) {
  EXPECT_TRUE(Complex(Real("2.2"), Integer(1)) < Real("2.3"));
}

TEST(ComplexTests, intLessOperatorTest) {
  EXPECT_TRUE(Complex(500, 1) < 501);
}

TEST(ComplexTests, integerFriendLessOperatorTest) {
  EXPECT_TRUE(Integer(500) < Complex(501, 1));
}

TEST(ComplexTests, rationalFriendLessOperatorTest) {
  EXPECT_FALSE(Rational(1, 2) < Complex(Rational(1, 3), Integer(1)));
}

TEST(ComplexTests, realFriendLessOperatorTest) {
  EXPECT_TRUE(Real("2.2") < Complex(Real("2.3"), Integer(1)));
}

TEST(ComplexTests, intFriendLessOperatorTest) {
  EXPECT_TRUE(500 < Complex(501, 1));
}

TEST(ComplexTests, moreOperatorTest) {
  EXPECT_FALSE(Complex(0, 0) > Complex(0, 0));
  EXPECT_FALSE(Complex(0, 0) > Complex(0, 1));
  EXPECT_FALSE(Complex(0, 0) > Complex(1, 0));
  EXPECT_FALSE(Complex(0, 0) > Complex(1, 1));

  EXPECT_FALSE(Complex(1, 1) > Complex(1, 1));
  EXPECT_FALSE(Complex(1, 1) > Complex(1, 2));
  EXPECT_FALSE(Complex(1, 1) > Complex(2, 1));
  EXPECT_FALSE(Complex(1, 1) > Complex(2, 2));

  EXPECT_FALSE(Complex(1, 2) > Complex(2, 1));
  EXPECT_TRUE(Complex(2, 1) > Complex(1, 2));

  EXPECT_TRUE(Complex(0, 0) > Complex(0, -1));
  EXPECT_TRUE(Complex(0, 0) > Complex(-1, 0));
  EXPECT_TRUE(Complex(0, 0) > Complex(-1, -1));

  EXPECT_FALSE(Complex(-1, -1) > Complex(-1, -1));
  EXPECT_TRUE(Complex(-1, -1) > Complex(-1, -2));
  EXPECT_TRUE(Complex(-1, -1) > Complex(-2, -1));
  EXPECT_TRUE(Complex(-1, -1) > Complex(-2, -2));

  EXPECT_TRUE(Complex(-1, -2) > Complex(-2, -1));
  EXPECT_FALSE(Complex(-2, -1) > Complex(-1, -2));
}

TEST(ComplexTests, integerMoreOperatorTest) {
  EXPECT_FALSE(Complex(500, 1) > Integer(501));
}

TEST(ComplexTests, rationalMoreOperatorTest) {
  EXPECT_TRUE(Complex(Rational(1, 2), Integer(1)) > Rational(1, 3));
}

TEST(ComplexTests, realMoreOperatorTest) {
  EXPECT_FALSE(Complex(Real("2.2"), Integer(1)) > Real("2.3"));
}

TEST(ComplexTests, intMoreOperatorTest) {
  EXPECT_FALSE(Complex(500, 1) > 501);
}

TEST(ComplexTests, integerFriendMoreOperatorTest) {
  EXPECT_FALSE(Integer(500) > Complex(501, 1));
}

TEST(ComplexTests, rationalFriendMoreOperatorTest) {
  EXPECT_TRUE(Rational(1, 2) > Complex(Rational(1, 3), Integer(1)));
}

TEST(ComplexTests, realFriendMoreOperatorTest) {
  EXPECT_FALSE(Real("2.2") > Complex(Real("2.3"), Integer(1)));
}

TEST(ComplexTests, intFriendMoreOperatorTest) {
  EXPECT_FALSE(500 > Complex(501, 1));
}

TEST(ComplexTests, lessEqvOperatorTest) {
  EXPECT_TRUE(Complex(0, 0) <= Complex(0, 0));
  EXPECT_TRUE(Complex(0, 0) <= Complex(0, 1));
  EXPECT_TRUE(Complex(0, 0) <= Complex(1, 0));
  EXPECT_TRUE(Complex(0, 0) <= Complex(1, 1));

  EXPECT_TRUE(Complex(1, 1) <= Complex(1, 1));
  EXPECT_TRUE(Complex(1, 1) <= Complex(1, 2));
  EXPECT_TRUE(Complex(1, 1) <= Complex(2, 1));
  EXPECT_TRUE(Complex(1, 1) <= Complex(2, 2));

  EXPECT_TRUE(Complex(1, 2) <= Complex(2, 1));
  EXPECT_FALSE(Complex(2, 1) <= Complex(1, 2));

  EXPECT_FALSE(Complex(0, 0) <= Complex(0, -1));
  EXPECT_FALSE(Complex(0, 0) <= Complex(-1, 0));
  EXPECT_FALSE(Complex(0, 0) <= Complex(-1, -1));

  EXPECT_TRUE(Complex(-1, -1) <= Complex(-1, -1));
  EXPECT_FALSE(Complex(-1, -1) <= Complex(-1, -2));
  EXPECT_FALSE(Complex(-1, -1) <= Complex(-2, -1));
  EXPECT_FALSE(Complex(-1, -1) <= Complex(-2, -2));

  EXPECT_FALSE(Complex(-1, -2) <= Complex(-2, -1));
  EXPECT_TRUE(Complex(-2, -1) <= Complex(-1, -2));
}

TEST(ComplexTests, integerLessEqvOperatorTest) {
  EXPECT_TRUE(Complex(500, 1) <= Integer(501));
}

TEST(ComplexTests, rationalLessEqvOperatorTest) {
  EXPECT_FALSE(Complex(Rational(1, 2), Integer(1)) <= Rational(1, 3));
}

TEST(ComplexTests, realLessEqvOperatorTest) {
  EXPECT_TRUE(Complex(Real("2.2"), Integer(1)) <= Real("2.3"));
}

TEST(ComplexTests, intLessEqvOperatorTest) {
  EXPECT_TRUE(Complex(500, 1) <= 501);
}

TEST(ComplexTests, integerFriendLessEqvOperatorTest) {
  EXPECT_TRUE(Integer(500) <= Complex(501, 1));
}

TEST(ComplexTests, rationalFriendLessEqvOperatorTest) {
  EXPECT_FALSE(Rational(1, 2) <= Complex(Rational(1, 3), Integer(1)));
}

TEST(ComplexTests, realFriendLessEqvOperatorTest) {
  EXPECT_TRUE(Real("2.2") <= Complex(Real("2.3"), Integer(1)));
}

TEST(ComplexTests, intFriendLessEqvOperatorTest) {
  EXPECT_TRUE(500 <= Complex(501, 1));
}

TEST(ComplexTests, moreEqvOperatorTest) {
  EXPECT_TRUE(Complex(0, 0) >= Complex(0, 0));
  EXPECT_FALSE(Complex(0, 0) >= Complex(0, 1));
  EXPECT_FALSE(Complex(0, 0) >= Complex(1, 0));
  EXPECT_FALSE(Complex(0, 0) >= Complex(1, 1));

  EXPECT_TRUE(Complex(1, 1) >= Complex(1, 1));
  EXPECT_FALSE(Complex(1, 1) >= Complex(1, 2));
  EXPECT_FALSE(Complex(1, 1) >= Complex(2, 1));
  EXPECT_FALSE(Complex(1, 1) >= Complex(2, 2));

  EXPECT_FALSE(Complex(1, 2) >= Complex(2, 1));
  EXPECT_TRUE(Complex(2, 1) >= Complex(1, 2));

  EXPECT_TRUE(Complex(0, 0) >= Complex(0, -1));
  EXPECT_TRUE(Complex(0, 0) >= Complex(-1, 0));
  EXPECT_TRUE(Complex(0, 0) >= Complex(-1, -1));

  EXPECT_TRUE(Complex(-1, -1) >= Complex(-1, -1));
  EXPECT_TRUE(Complex(-1, -1) >= Complex(-1, -2));
  EXPECT_TRUE(Complex(-1, -1) >= Complex(-2, -1));
  EXPECT_TRUE(Complex(-1, -1) >= Complex(-2, -2));

  EXPECT_TRUE(Complex(-1, -2) >= Complex(-2, -1));
  EXPECT_FALSE(Complex(-2, -1) >= Complex(-1, -2));
}

TEST(ComplexTests, integerEqvMoreOperatorTest) {
  EXPECT_FALSE(Complex(500, 1) >= Integer(501));
}

TEST(ComplexTests, rationalMoreEqvOperatorTest) {
  EXPECT_TRUE(Complex(Rational(1, 2), Integer(1)) >= Rational(1, 3));
}

TEST(ComplexTests, realMoreEqvOperatorTest) {
  EXPECT_FALSE(Complex(Real("2.2"), Integer(1)) >= Real("2.3"));
}

TEST(ComplexTests, intMoreEqvOperatorTest) {
  EXPECT_FALSE(Complex(500, 1) >= 501);
}

TEST(ComplexTests, integerFriendMoreEqvOperatorTest) {
  EXPECT_FALSE(Integer(500) >= Complex(501, 1));
}

TEST(ComplexTests, rationalFriendMoreEqvOperatorTest) {
  EXPECT_TRUE(Rational(1, 2) >= Complex(Rational(1, 3), Integer(1)));
}

TEST(ComplexTests, realFriendMoreEqvOperatorTest) {
  EXPECT_FALSE(Real("2.2") >= Complex(Real("2.3"), Integer(1)));
}

TEST(ComplexTests, intFriendMoreEqvOperatorTest) {
  EXPECT_FALSE(500 >= Complex(501, 1));
}

TEST(ComplexTests, realTest) {
  EXPECT_EQ(Complex(5, 2).real(), Integer(5));
  EXPECT_EQ(Complex(55).real(), Integer(55));
  EXPECT_EQ(Complex(-10, 100).real(), Integer(-10));
  EXPECT_EQ(Complex(0, 100).real(), Integer(0));

  EXPECT_TRUE(is<Integer>(Complex(Rational(2, 2), Integer(1)).real()));
}

TEST(ComplexTests, imagTest) {
  EXPECT_EQ(Complex(5, 2).imag(), Integer(2));
  EXPECT_EQ(Complex(55).imag(), Integer(0));
  EXPECT_EQ(Complex(-10, 100).imag(), Integer(100));

  EXPECT_TRUE(is<Integer>(Complex(Integer(1), Rational(2, 2)).imag()));
}

TEST(ComplexTests, toStringTest) {
  EXPECT_EQ(Complex(0, 0).toString(), "0");
  EXPECT_EQ(Complex(1, 0).toString(), "1");
  EXPECT_EQ(Complex(0, 1).toString(), "I");
  EXPECT_EQ(Complex(0, 2).toString(), "2 I");
  EXPECT_EQ(Complex(1, 1).toString(), "1 + I");
  EXPECT_EQ(Complex(1, 2).toString(), "1 + 2 I");
  EXPECT_EQ(Complex(2, 1).toString(), "2 + I");
  EXPECT_EQ(Complex(2, 2).toString(), "2 + 2 I");
  EXPECT_EQ(Complex(-1, 0).toString(), "-1");
  EXPECT_EQ(Complex(0, -1).toString(), "-I");
  EXPECT_EQ(Complex(0, -2).toString(), "-2 I");
  EXPECT_EQ(Complex(-1, -1).toString(), "-1 - I");
  EXPECT_EQ(Complex(-1, -2).toString(), "-1 - 2 I");
  EXPECT_EQ(Complex(-2, -1).toString(), "-2 - I");
  EXPECT_EQ(Complex(-2, -2).toString(), "-2 - 2 I");
}

TEST(ComplexTests, simplifyTest) {
  EXPECT_TRUE(is<Complex>(Complex(5, 2).toMinimalObject()));
  EXPECT_TRUE(is<Integer>(Complex(55, 0).toMinimalObject()));
  EXPECT_TRUE(is<Integer>(Complex(Rational(5, 5), Integer(0)).toMinimalObject()));
  EXPECT_TRUE(is<Rational>(Complex(Rational(5, 2), Integer(0)).toMinimalObject()));
  EXPECT_TRUE(is<Real>(Complex(Real("5.2"), Integer(0)).toMinimalObject()));

  EXPECT_EQ(Complex(5, 2).toMinimalObject()->toString(), "5 + 2 I");
  EXPECT_EQ(Complex(55, 0).toMinimalObject()->toString(), "55");
  EXPECT_EQ(Complex(Rational(5, 5), Integer(0)).toMinimalObject()->toString(), "1");
  EXPECT_EQ(Complex(Rational(5, 2), Integer(0)).toMinimalObject()->toString(), "5/2");
  EXPECT_EQ(Complex(Real("5.2"), Integer(0)).toMinimalObject()->toString(), "5.2");
}

TEST(ComplexTests, isPreciseTest) {
  EXPECT_TRUE(Complex(1, 2).isPrecise());
  EXPECT_TRUE(Complex(Rational(1, 2), Rational(1, 2)).isPrecise());

  EXPECT_FALSE(Complex(Real(1), Real(1)).isPrecise());
  EXPECT_FALSE(Complex(Real(1), Integer(1)).isPrecise());
  EXPECT_FALSE(Complex(Integer(1), Real(1)).isPrecise());
}

TEST(ComplexTests, isComplexTest) {
  EXPECT_TRUE(Complex(1, 1).isComplex());

  EXPECT_FALSE(Complex(1, 0).isComplex());
}

TEST(ComplexTests, equalsTest) {
  Complex a;
  Integer b;
  Integer c(1);

  EXPECT_EQ(a, a);
  EXPECT_EQ(a, Complex());
  EXPECT_EQ(Complex(), a);
  EXPECT_EQ(a, cast<IMathObject>(Complex()));
  EXPECT_EQ(cast<IMathObject>(Complex()), a);
  EXPECT_EQ(a, b);
  EXPECT_EQ(b, a);
  EXPECT_NE(a, c);
  EXPECT_NE(c, a);
}

TEST(ComplexTests, getTypeTest) {
  EXPECT_EQ(Complex::getTypeStatic(), MathObjectType::Complex);
  EXPECT_EQ(Complex().getType(), MathObjectType::Complex);
}
