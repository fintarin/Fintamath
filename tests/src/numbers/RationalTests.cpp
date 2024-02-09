#include <gtest/gtest.h>

#include <unordered_set>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(RationalTests, constructorTest) {
  EXPECT_EQ(Rational(), 0);
}

TEST(RationalTests, stringConstructorTest) {
  EXPECT_EQ(Rational("0"), 0);
  EXPECT_EQ(Rational("2"), 2);
  EXPECT_EQ(Rational("-93"), -93);
  EXPECT_EQ(Rational("-9.3").toString(), "-93/10");
  EXPECT_EQ(Rational("0989929039237832000.9302930929333").toString(), "9899290392378320009302930929333/10000000000000");
  EXPECT_EQ(Rational(".1").toString(), "1/10");
  EXPECT_EQ(Rational("1.").toString(), "1");

  EXPECT_THROW(Rational("--10"), InvalidInputException);
  EXPECT_THROW(Rational("test"), InvalidInputException);
  EXPECT_THROW(Rational(""), InvalidInputException);
  EXPECT_THROW(Rational("+"), InvalidInputException);
  EXPECT_THROW(Rational("939849.0-0023"), InvalidInputException);
  EXPECT_THROW(Rational("a"), InvalidInputException);
  EXPECT_THROW(Rational("a.1"), InvalidInputException);
  EXPECT_THROW(Rational("1.a"), InvalidInputException);
  EXPECT_THROW(Rational("1a.1"), InvalidInputException);
  EXPECT_THROW(Rational("1.1a"), InvalidInputException);
  EXPECT_THROW(Rational(".1."), InvalidInputException);
  EXPECT_THROW(Rational("."), InvalidInputException);
  EXPECT_THROW(Rational("--10.-1"), InvalidInputException);
  EXPECT_THROW(Rational("10.-1"), InvalidInputException);
  EXPECT_THROW(Rational("1-0.1"), InvalidInputException);
  EXPECT_THROW(Rational("10-.1"), InvalidInputException);
  EXPECT_THROW(Rational("10.--1"), InvalidInputException);
  EXPECT_THROW(Rational("1.10.1"), InvalidInputException);
}

TEST(RationalTests, integerIntegerConstructorTest) {
  EXPECT_EQ(Rational(-380, -608).toString(), "5/8");
  EXPECT_EQ(Rational(2849300, 18493).toString(), "2849300/18493");
  EXPECT_EQ(Rational(2849300, -1893).toString(), "-2849300/1893");

  EXPECT_THROW(Rational(23070, 0), UndefinedBinaryOperatorException);
}

TEST(RationalTests, integerConstructorTest) {
  EXPECT_EQ(Rational(Integer("122432964238764283746823")), Integer("122432964238764283746823"));
}

TEST(RationalTests, integerAssignmentOperatorTest) {
  Rational b;
  EXPECT_EQ(b = Integer("39743491820370928039"), Rational("39743491820370928039"));
}

TEST(RationalTests, intConstructorTest) {
  EXPECT_EQ(Rational(2), 2);
}

TEST(RationalTests, intAssignmentOperatorTest) {
  Rational a;
  EXPECT_EQ(a = 2, 2);
}

TEST(RationalTests, plusAssignmentOperatorTest) {
  EXPECT_EQ(Rational(2, 3) += Rational(5, 2), Rational(19, 6));
  EXPECT_EQ(Rational(-738, 10) += Rational(5, 2), Rational(-713, 10));
  EXPECT_EQ(Rational(738, 10) += Rational(5, 2), Rational(763, 10));
  EXPECT_EQ(Rational(-738, 10) += Rational(-5, 2), Rational(-763, 10));
}

TEST(RationalTests, integerPlusAssignmentOperatorTest) {
  EXPECT_EQ(Rational(-10) += Integer(5), -5);
  EXPECT_EQ(Rational(2, 3) += Integer(-5), Rational(-13, 3));
}

TEST(RationalTests, intPlusAssignmentOperatorTest) {
  EXPECT_EQ(Rational(-10) += 5, -5);
  EXPECT_EQ(Rational(2, 3) += -5, Rational(-13, 3));
}

TEST(RationalTests, plusOperatorTest) {
  EXPECT_EQ(Rational(170, 15) + Rational(-5, 2), Rational(53, 6));
  EXPECT_EQ(Rational(17, 19) + Rational(53, 5), Rational(1092, 95));
  EXPECT_EQ(Rational(170, 12) + Rational(2, 5), Rational(437, 30));
}

TEST(RationalTests, integerPlusOperatorTest) {
  EXPECT_EQ(Rational(170) + Integer(-5), 165);
  EXPECT_EQ(Rational(17) + Integer(53), 70);
  EXPECT_EQ(Rational(170, 12) + Integer(2), Rational(194, 12));
}

TEST(RationalTests, intPlusOperatorTest) {
  EXPECT_EQ(Rational(170) + -5, 165);
  EXPECT_EQ(Rational(17) + 53, 70);
  EXPECT_EQ(Rational(170, 12) + 2, Rational(194, 12));
}

TEST(RationalTests, integerFriendPlusOperatorTest) {
  EXPECT_EQ(Integer(2) + Rational(-18), -16);
  EXPECT_EQ(Integer(4938493849) + Rational(1009), 4938494858);
}

TEST(RationalTests, intFriendPlusOperatorTest) {
  EXPECT_EQ(2 + Rational(-18), -16);
  EXPECT_EQ(4938493849 + Rational(1009), 4938494858);
}

TEST(RationalTests, minusAssignmentOperatorTest) {
  EXPECT_EQ(Rational(2, 3) -= Rational(5, 2), Rational(-11, 6));
  EXPECT_EQ(Rational(-738, 10) -= Rational(5, 2), Rational(-763, 10));
  EXPECT_EQ(Rational(738, 10) -= Rational(5, 2), Rational(713, 10));
  EXPECT_EQ(Rational(-738, 10) -= Rational(-5, 2), Rational(-713, 10));
}

TEST(RationalTests, integerMinusAssignmentOperatorTest) {
  EXPECT_EQ(Rational(-738, -10) -= Integer(-5), Rational(394, 5));
  EXPECT_EQ(Rational(-738, 10) -= Integer(5), Rational(-394, 5));
}

TEST(RationalTests, intMinusAssignmentOperatorTest) {
  EXPECT_EQ(Rational(-738, -10) -= -5, Rational(394, 5));
  EXPECT_EQ(Rational(-738, 10) -= 5, Rational(-394, 5));
}

TEST(RationalTests, minusOperatorTest) {
  EXPECT_EQ(Rational(170, 15) - Rational(-5, 2), Rational(83, 6));
  EXPECT_EQ(Rational(17, 19) - Rational(53, 5), Rational(-922, 95));
  EXPECT_EQ(Rational(170, 12) - Rational(2, 5), Rational(413, 30));
}

TEST(RationalTests, integerMinusOperatorTest) {
  EXPECT_EQ(Rational(170) - Integer(5), 165);
  EXPECT_EQ(Rational(17) - Integer(53), -36);
  EXPECT_EQ(Rational(170, 12) - Integer(-2), Rational(194, 12));
}

TEST(RationalTests, intMinusOperatorTest) {
  EXPECT_EQ(Rational(170) - 5, 165);
  EXPECT_EQ(Rational(17) - 53, -36);
  EXPECT_EQ(Rational(170, 12) - -2, Rational(194, 12));
}

TEST(RationalTests, integerFriendMinusOperatorTest) {
  EXPECT_EQ(Integer(2) - Rational(-18), 20);
  EXPECT_EQ(Integer(4938493849) - Rational(1009), 4938492840);
}

TEST(RationalTests, intFriendMinusOperatorTest) {
  EXPECT_EQ(2 - Rational(-18), 20);
  EXPECT_EQ(4938493849 - Rational(1009), 4938492840);
}

TEST(RationalTests, multiplyAssignmentOperatorTest) {
  EXPECT_EQ(Rational(2, 3) *= Rational(5, 2), Rational(5, 3));
  EXPECT_EQ(Rational(-738, 10) *= Rational(5, 2), Rational(-369, 2));
  EXPECT_EQ(Rational(738, 10) *= Rational(5, 2), Rational(369, 2));
  EXPECT_EQ(Rational(-738, 10) *= Rational(-5, 2), Rational(369, 2));
}

TEST(RationalTests, integerMultiplyAssignmentOperatorTest) {
  EXPECT_EQ(Rational(2, 3) *= Integer(-5), Rational(-10, 3));
  EXPECT_EQ(Rational(738, -10) *= Integer(5894), Rational(-4349772, 10));
  EXPECT_EQ(Rational(-738, -10) *= Integer(10), 738);
}

TEST(RationalTests, intMultiplyAssignmentOperatorTest) {
  EXPECT_EQ(Rational(2, 3) *= -5, Rational(-10, 3));
  EXPECT_EQ(Rational(738, -10) *= 5894, Rational(-4349772, 10));
  EXPECT_EQ(Rational(-738, -10) *= 10, 738);
}

TEST(RationalTests, multiplyOperatorTest) {
  EXPECT_EQ(Rational(170, 15) * Rational(-5, 2), Rational(-85, 3));
  EXPECT_EQ(Rational(17, 19) * Rational(53, 5), Rational(901, 95));
  EXPECT_EQ(Rational(170, 12) * Rational(2, 5), Rational(17, 3));
}

TEST(RationalTests, integerMultiplyOperatorTest) {
  EXPECT_EQ(Rational(2, 3) * Integer(-5), Rational(-10, 3));
  EXPECT_EQ(Rational(738, -10) * Integer(5894), Rational(-4349772, 10));
  EXPECT_EQ(Rational(-738, -10) * Integer(10), 738);
}

TEST(RationalTests, intMultiplyOperatorTest) {
  EXPECT_EQ(Rational(2, 3) * -5, Rational(-10, 3));
  EXPECT_EQ(Rational(738, -10) * 5894, Rational(-4349772, 10));
  EXPECT_EQ(Rational(-738, -10) * 10, 738);
}

TEST(RationalTests, integerFriendMultiplyOperatorTest) {
  EXPECT_EQ(Integer(-5) * Rational(2, 3), Rational(-10, 3));
  EXPECT_EQ(Integer(589398724) * Rational(1, 8372738), Rational(589398724, 8372738));
  EXPECT_EQ(Integer(10) * Rational(-738, -10), 738);
}

TEST(RationalTests, intFriendMultiplyOperatorTest) {
  EXPECT_EQ(-5 * Rational(2, 3), Rational(-10, 3));
  EXPECT_EQ(589398724 * Rational(1, 8372738), Rational(589398724, 8372738));
  EXPECT_EQ(10 * Rational(-738, -10), 738);
}

TEST(RationalTests, divideAssignmentOperatorTest) {
  EXPECT_EQ(Rational(2, 3) /= Rational(5, 2), Rational(4, 15));
  EXPECT_EQ(Rational(-738, 10) /= Rational(5, 2), Rational(-738, 25));
  EXPECT_EQ(Rational(738, 10) /= Rational(5, 2), Rational(738, 25));
  EXPECT_EQ(Rational(-738, 10) /= Rational(-5, 2), Rational(738, 25));

  EXPECT_THROW(Rational(-738, -10) /= Rational("0"), UndefinedBinaryOperatorException);
}

TEST(RationalTests, integerDivideAssignmentOperatorTest) {
  EXPECT_EQ(Rational(2, 3) /= Integer(-2), Rational(1, -3));
  EXPECT_EQ(Rational(738, -10) /= Integer(5894), Rational(-738, 58940));
  EXPECT_EQ(Rational(-738, -10) /= Integer(10), Rational(369, 50));
}

TEST(RationalTests, intDivideAssignmentOperatorTest) {
  EXPECT_EQ(Rational(2, 3) /= -2, Rational(1, -3));
  EXPECT_EQ(Rational(738, -10) /= 5894, Rational(-738, 58940));
  EXPECT_EQ(Rational(-738, -10) /= 10, Rational(369, 50));
}

TEST(RationalTests, divideOperatorTest) {
  EXPECT_EQ(Rational(170, 15) / Rational(-5, 2), Rational(-68, 15));
  EXPECT_EQ(Rational(17, 19) / Rational(53, 5), Rational(85, 1007));
  EXPECT_EQ(Rational(170, 12) / Rational(2, 5), Rational(425, 12));
}

TEST(RationalTests, integerDivideOperatorTest) {
  EXPECT_EQ(Rational(2, 3) / Integer(-5), Rational(-2, 15));
  EXPECT_EQ(Rational(738, -10) / Integer(5894), Rational(738, -58940));
}

TEST(RationalTests, intDivideOperatorTest) {
  EXPECT_EQ(Rational(2, 3) / -5, Rational(-2, 15));
  EXPECT_EQ(Rational(738, -10) / 5894, Rational(738, -58940));
}

TEST(RationalTests, integerFriendDivideOperatorTest) {
  EXPECT_EQ(Integer(-5) / Rational(2, 3), Rational(-15, 2));
  EXPECT_EQ(Integer(589398724) / Rational(8372738), Rational(589398724, 8372738));
  EXPECT_EQ(Integer(10) / Rational(-10, -738), 738);
}

TEST(RationalTests, intFriendDivideOperatorTest) {
  EXPECT_EQ(-5 / Rational(2, 3), Rational(-15, 2));
  EXPECT_EQ(589398724 / Rational(8372738), Rational(589398724, 8372738));
  EXPECT_EQ(10 / Rational(-10, -738), 738);
}

TEST(RationalTests, unaryPlusOperatorTest) {
  EXPECT_EQ(+Rational(-5), -5);
}

TEST(RationalTests, unaryMinusOperatorTest) {
  EXPECT_EQ(-Rational(5), -5);
}

TEST(RationalTests, equalOperatorTest) {
  EXPECT_TRUE(Rational(1, 2) == Rational(1, 2));
  EXPECT_TRUE(Rational(5, 10) == Rational(1, 2));
  EXPECT_TRUE(Rational(5, -10) == Rational(-5, 10));

  EXPECT_FALSE(Rational(1, 2) == Rational(1, 3));
  EXPECT_FALSE(Rational(3, 2) == Rational(1, 3));
  EXPECT_FALSE(Rational(55, 10) == Rational(-1, 10));
}

TEST(RationalTests, integerEqualOperatorTest) {
  EXPECT_TRUE(Rational(500) == Integer(500));
  EXPECT_TRUE(Rational(50, -10) == Integer(-5));
}

TEST(RationalTests, intEqualOperatorTest) {
  EXPECT_TRUE(Rational(500) == 500);
  EXPECT_TRUE(Rational(50, -10) == -5);
}

TEST(RationalTests, integerFriendEqualOperatorTest) {
  EXPECT_TRUE(Integer(500) == Rational(500));
  EXPECT_TRUE(Integer(-5) == Rational(50, -10));
}

TEST(RationalTests, intFriendEqualOperatorTest) {
  EXPECT_TRUE(500 == Rational(500));
  EXPECT_TRUE(-5 == Rational(50, -10));
}

TEST(RationalTests, notEqualOperatorTest) {
  EXPECT_TRUE(Rational(55, 10) != Rational(-1, 10));

  EXPECT_FALSE(Rational(5, 10) != Rational(1, 2));
  EXPECT_FALSE(Rational(5, -10) != Rational(-5, 10));
}

TEST(RationalTests, integerNotEqualOperatorTest) {
  EXPECT_TRUE(Rational(50, 10) != Integer(-5));

  EXPECT_FALSE(Rational(500) != Integer(500));
}

TEST(RationalTests, intNotEqualOperatorTest) {
  EXPECT_TRUE(Rational(50, 10) != -5);

  EXPECT_FALSE(Rational(500) != 500);
}

TEST(RationalTests, integerFriendNotEqualOperatorTest) {
  EXPECT_TRUE(Integer(50) != Rational(3920));

  EXPECT_FALSE(Integer(500) != Rational(500));
  EXPECT_FALSE(Integer(-5) != Rational(50, -10));
}

TEST(RationalTests, intFriendNotEqualOperatorTest) {
  EXPECT_TRUE(50 != Rational(3920));

  EXPECT_FALSE(500 != Rational(500));
  EXPECT_FALSE(-5 != Rational(50, -10));
}

TEST(RationalTests, lessOperatorTest) {
  EXPECT_TRUE(Rational(5, -10) < Rational(50, 10));

  EXPECT_FALSE(Rational(5, 10) < Rational(1, 2));
  EXPECT_FALSE(Rational(5, -10) < Rational(-50, 10));
  EXPECT_FALSE(Rational(55, 10) < Rational(1, 10));
}

TEST(RationalTests, integerLessOperatorTest) {
  EXPECT_TRUE(Rational(500) < Integer(3283));

  EXPECT_FALSE(Rational(50, -10) < Integer(-5));
}

TEST(RationalTests, intLessOperatorTest) {
  EXPECT_TRUE(Rational(500) < 3283);

  EXPECT_FALSE(Rational(50, -10) < -5);
}

TEST(RationalTests, integerFriendLessOperatorTest) {
  EXPECT_TRUE(Integer(-5) < Rational(50, 10));
  EXPECT_TRUE(Integer(7387) < Rational(3983920));

  EXPECT_FALSE(Integer(500) < Rational(500));
}

TEST(RationalTests, intFriendLessOperatorTest) {
  EXPECT_TRUE(-5 < Rational(50, 10));
  EXPECT_TRUE(7387 < Rational(3983920));

  EXPECT_FALSE(500 < Rational(500));
}

TEST(RationalTests, moreOperatorTest) {
  EXPECT_TRUE(Rational(5, -10) > Rational(-50, 10));
  EXPECT_TRUE(Rational(55, 10) > Rational(1, 10));

  EXPECT_FALSE(Rational(5, 10) > Rational(1, 2));
  EXPECT_FALSE(Rational(5, -10) > Rational(50, 10));
}

TEST(RationalTests, integerMoreOperatorTest) {
  EXPECT_FALSE(Rational(500) > Integer(3283));
  EXPECT_FALSE(Rational(50, -10) > Integer(-5));
}

TEST(RationalTests, intMoreOperatorTest) {
  EXPECT_FALSE(Rational(500) > 3283);
  EXPECT_FALSE(Rational(50, -10) > -5);
}

TEST(RationalTests, integerFriendMoreOperatorTest) {
  EXPECT_TRUE(Integer(738657) > Rational(320));

  EXPECT_FALSE(Integer(500) > Rational(500));
  EXPECT_FALSE(Integer(-5) > Rational(50, 10));
}

TEST(RationalTests, intFriendMoreOperatorTest) {
  EXPECT_TRUE(738657 > Rational(320));

  EXPECT_FALSE(500 > Rational(500));
  EXPECT_FALSE(-5 > Rational(50, 10));
}

TEST(RationalTests, lessEqualOperatorTest) {
  EXPECT_TRUE(Rational(5, 10) <= Rational(1, 2));
  EXPECT_TRUE(Rational(5, -10) <= Rational(50, 10));

  EXPECT_FALSE(Rational(5, -10) <= Rational(-50, 10));
  EXPECT_FALSE(Rational(55, 10) <= Rational(1, 10));
}

TEST(RationalTests, integerLessEqualOperatorTest) {
  EXPECT_TRUE(Rational(500) <= Integer(3283));
  EXPECT_TRUE(Rational(50, -10) <= Integer(-5));
}

TEST(RationalTests, intLessEqualOperatorTest) {
  EXPECT_TRUE(Rational(500) <= 3283);
  EXPECT_TRUE(Rational(50, -10) <= -5);
}

TEST(RationalTests, integerFriendLessEqualOperatorTest) {
  EXPECT_TRUE(Integer(500) <= Rational(500));
  EXPECT_TRUE(Integer(-5) <= Rational(50, 10));

  EXPECT_FALSE(Integer(73687) <= Rational(30));
}

TEST(RationalTests, intFriendLessEqualOperatorTest) {
  EXPECT_TRUE(500 <= Rational(500));
  EXPECT_TRUE(-5 <= Rational(50, 10));

  EXPECT_FALSE(73687 <= Rational(30));
}

TEST(RationalTests, moreEqualOperatorTest) {
  EXPECT_TRUE(Rational(5, 10) >= Rational(1, 2));
  EXPECT_TRUE(Rational(5, -10) >= Rational(-50, 10));
  EXPECT_TRUE(Rational(55, 10) >= Rational(1, 10));

  EXPECT_FALSE(Rational(5, -10) >= Rational(50, 10));
}

TEST(RationalTests, integerMoreEqualOperatorTest) {
  EXPECT_TRUE(Rational(50, -10) >= Integer(-5));

  EXPECT_FALSE(Rational(500) >= Integer(3283));
}

TEST(RationalTests, intMoreEqualOperatorTest) {
  EXPECT_TRUE(Rational(50, -10) >= -5);

  EXPECT_FALSE(Rational(500) >= 3283);
}

TEST(RationalTests, integerFriendMoreEqualOperatorTest) {
  EXPECT_TRUE(Integer(500) >= Rational(500));
  EXPECT_TRUE(Integer(738657) >= Rational(320));

  EXPECT_FALSE(Integer(-5) >= Rational(50, 10));
}

TEST(RationalTests, intFriendMoreEqualOperatorTest) {
  EXPECT_TRUE(500 >= Rational(500));
  EXPECT_TRUE(738657 >= Rational(320));

  EXPECT_FALSE(-5 >= Rational(50, 10));
}

TEST(RationalTests, numeratorTest) {
  EXPECT_EQ(Rational(5, 2).numerator(), 5);
  EXPECT_EQ(Rational(55).numerator(), 55);
  EXPECT_EQ(Rational(-10, 100).numerator(), -1);
}

TEST(RationalTests, denominatorTest) {
  EXPECT_EQ(Rational(5, 2).denominator(), 2);
  EXPECT_EQ(Rational(55).denominator(), 1);
  EXPECT_EQ(Rational(-10, 100).denominator(), 10);
}

TEST(RationalTests, toStringTest) {
  EXPECT_EQ(Rational(5, 2).toString(), "5/2");
  EXPECT_EQ(Rational(55, -10).toString(), "-11/2");
}

TEST(RationalTests, simplifyTest) {
  EXPECT_TRUE(is<Rational>(Rational(5, 2).toMinimalObject()));
  EXPECT_TRUE(is<Integer>(Rational(55, 5).toMinimalObject()));
  EXPECT_TRUE(is<Rational>(Rational(-5, 2).toMinimalObject()));
  EXPECT_TRUE(is<Integer>(Rational(-55, 5).toMinimalObject()));

  EXPECT_EQ(Rational(5, 2).toMinimalObject()->toString(), "5/2");
  EXPECT_EQ(Rational(55, 5).toMinimalObject()->toString(), "11");
  EXPECT_EQ(Rational(-5, 2).toMinimalObject()->toString(), "-5/2");
  EXPECT_EQ(Rational(-55, 5).toMinimalObject()->toString(), "-11");
}

TEST(RationalTests, signTest) {
  EXPECT_EQ(Rational(-2).sign(), -1);
  EXPECT_EQ(Rational(-1).sign(), -1);
  EXPECT_EQ(Rational(0).sign(), 0);
  EXPECT_EQ(Rational(1).sign(), 1);
  EXPECT_EQ(Rational(2).sign(), 1);
}

TEST(RationalTests, isPreciseTest) {
  EXPECT_TRUE(Rational(1, 2).isPrecise());
}

TEST(RationalTests, isComplexTest) {
  EXPECT_FALSE(Rational(1, 2).isComplex());
}

TEST(RationalTests, getTypeTest) {
  EXPECT_EQ(Rational::getTypeStatic(), MathObjectType::Rational);
  EXPECT_EQ(Rational().getType(), MathObjectType::Rational);
}

TEST(RationalTests, hashTest) {
  constexpr auto hash = boost::hash<Rational>{};

  EXPECT_EQ(hash(Rational(0)), hash(Rational(0)));
  EXPECT_EQ(hash(Rational(12)), hash(Rational(12)));
  EXPECT_EQ(hash(Rational(-12)), hash(Rational(-12)));
  EXPECT_EQ(hash(Rational(3, 2)), hash(Rational(3, 2)));
  EXPECT_EQ(hash(Rational(-3, 2)), hash(Rational(-3, 2)));
  EXPECT_EQ(hash(Rational(Integer("452734865298734659873246238756987435"), Integer("39842732658275642342352642634234234"))), hash(Rational(Integer("452734865298734659873246238756987435"), Integer("39842732658275642342352642634234234"))));
  EXPECT_EQ(hash(Rational(-Integer("452734865298734659873246238756987435"), Integer("39842732658275642342352642634234234"))), hash(Rational(-Integer("452734865298734659873246238756987435"), Integer("39842732658275642342352642634234234"))));

  EXPECT_NE(hash(Rational(0)), hash(Rational(1)));
  EXPECT_NE(hash(Rational(12)), hash(Rational(13)));
  EXPECT_NE(hash(Rational(-12)), hash(Rational(-13)));
  EXPECT_NE(hash(Rational(3, 2)), hash(Rational(2, 3)));
  EXPECT_NE(hash(Rational(-3, 2)), hash(Rational(-2, 3)));
  EXPECT_NE(hash(Rational(Integer("39842732658275642342352642634234234"), Integer("452734865298734659873246238756987435"))), Rational(Integer("452734865298734659873246238756987435"), Integer("39842732658275642342352642634234234")));
  EXPECT_NE(hash(Rational(-Integer("39842732658275642342352642634234234"), Integer("452734865298734659873246238756987435"))), Rational(-Integer("452734865298734659873246238756987435"), Integer("39842732658275642342352642634234234")));
}
