#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/powers/Root.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Root f;

TEST(RootTests, toStringTest) {
  EXPECT_EQ(f.toString(), "root");
}

TEST(RootTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic(), INumber::getClassStatic()));
}

TEST(RootTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(RootTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(RootTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(RootTests, callTest) {
  EXPECT_EQ(f(Integer(0), Integer(3))->toString(),
            "0");
  EXPECT_EQ(f(Integer(10), Integer(1))->toString(),
            "10");
  EXPECT_EQ(f(Integer(-10), Integer(1))->toString(),
            "-10");
  EXPECT_EQ(f(Integer(100), Integer(2))->toString(),
            "10");
  EXPECT_EQ(f(Integer(25), Integer(2))->toString(),
            "5");
  EXPECT_EQ(f(Integer(144), Integer(2))->toString(),
            "12");
  EXPECT_EQ(f(Integer("10000000000000000000000000000000000000000000000000000"), Integer(2))->toString(),
            "100000000000000000000000000");
  EXPECT_EQ(f(Integer(10), Integer(2))->toString(),
            "sqrt(10)");
  EXPECT_EQ(f(Integer(35), Integer(2))->toString(),
            "sqrt(35)");
  EXPECT_EQ(f(Integer(4212), Integer(2))->toString(),
            "18 sqrt(13)");
  EXPECT_EQ(f(Integer("992188888888"), Integer(2))->toString(),
            "2 sqrt(248047222222)");
  EXPECT_EQ(f(Integer("68732648273642987365932706179432649827364"), Integer(2))->toString(),
            "2 sqrt(17183162068410746841483176544858162456841)");
  EXPECT_EQ(f(Integer(100), Integer(3))->toString(),
            "root(100, 3)");
  EXPECT_EQ(f(Integer(25), Integer(3))->toString(),
            "root(25, 3)");
  EXPECT_EQ(f(Integer(144), Integer(3))->toString(),
            "2 root(18, 3)");
  EXPECT_EQ(f(Integer("10000000000000000000000000000000000000000000000000000"), Integer(3))->toString(),
            "100000000000000000 root(10, 3)");
  EXPECT_EQ(f(Integer(10), Integer(3))->toString(),
            "root(10, 3)");
  EXPECT_EQ(f(Integer(35), Integer(3))->toString(),
            "root(35, 3)");
  EXPECT_EQ(f(Integer(4212), Integer(3))->toString(),
            "3 root(156, 3)");
  EXPECT_EQ(f(Integer("992188888888"), Integer(3))->toString(),
            "2 root(124023611111, 3)");
  EXPECT_EQ(f(Integer("68732648273642987365932706179432649827364"), Integer(3))->toString(),
            "root(68732648273642987365932706179432649827364, 3)");
  EXPECT_EQ(f(Integer(1024), Integer(3))->toString(),
            "8 root(2, 3)");
  EXPECT_EQ(f(Integer(1024), Integer(5))->toString(),
            "4");
  EXPECT_EQ(f(Integer(1024), Integer(10))->toString(),
            "2");
  EXPECT_EQ(f(Integer(-1000), Integer(3))->toString(),
            "root(-1000, 3)");
  EXPECT_EQ(f(Integer(-10), Integer(3))->toString(),
            "root(-10, 3)");
  EXPECT_EQ(f(Integer(-100000), Integer(5))->toString(),
            "root(-100000, 5)");
  EXPECT_EQ(f(Integer(-10), Integer(5))->toString(),
            "root(-10, 5)");

  EXPECT_EQ(f(Rational(25), Integer(4))->toString(),
            "sqrt(5)");
  EXPECT_EQ(f(Rational(25, 169), Integer(4))->toString(),
            "sqrt(65)/13");
  EXPECT_EQ(f(Rational(144, 49), Integer(4))->toString(),
            "(2 sqrt(21))/7");
  EXPECT_EQ(f(Rational("1.44"), Integer(4))->toString(),
            "sqrt(30)/5");
  EXPECT_EQ(f(Rational(1, 10), Integer(4))->toString(),
            "1/root(10, 4)");
  EXPECT_EQ(f(Rational(25, 48), Integer(4))->toString(),
            "(sqrt(5) root(27, 4))/6");
  EXPECT_EQ(f(Rational(26, 49), Integer(4))->toString(),
            "(root(26, 4) sqrt(7))/7");
  EXPECT_EQ(f(Rational(45, 67), Integer(4))->toString(),
            "(sqrt(3) root(1503815, 4))/67");
  EXPECT_EQ(f(Rational("68732648273642987365932706179432649827364.144"), Integer(4))->toString(),
            "root(16780431707432369962385914594588049274258824218750, 4)/125");

  EXPECT_EQ(f(Rational(25), Rational(4, 3))->toString(),
            "5 sqrt(5)");
  EXPECT_EQ(f(Rational(25, 169), Rational(4, 3))->toString(),
            "(5 sqrt(65))/169");
  EXPECT_EQ(f(Rational(144, 49), Rational(4, 3))->toString(),
            "(24 sqrt(21))/49");
  EXPECT_EQ(f(Rational("1.44"), Rational(4, 3))->toString(),
            "(6 sqrt(30))/25");
  EXPECT_EQ(f(Rational(1, 10), Rational(4, 3))->toString(),
            "1/root(1000, 4)");
  EXPECT_EQ(f(Rational(25, 48), Rational(4, 3))->toString(),
            "(5 sqrt(5) root(19683, 4))/216");
  EXPECT_EQ(f(Rational(26, 49), Rational(4, 3))->toString(),
            "(root(17576, 4) sqrt(7))/49");
  EXPECT_EQ(f(Rational(45, 67), Rational(4, 3))->toString(),
            "(3 sqrt(3) root(3400816799536868375, 4))/300763");
  EXPECT_EQ(f(Rational("68732648273642987365932706179432649827364.144"), Rational(4, 3))->toString(),
            "root(79273728493821852759219484162954910061238025079805909288285023460357068666345126055475627257403374507144013103294156851180403979000, 4)/125");

  EXPECT_EQ(f(Real(144), Integer(2))->toString(),
            "12.0");
  EXPECT_EQ(f(Real(144), Integer(4))->toString(),
            "3.4641016151377545871");
  EXPECT_EQ(f(Real(2), Integer(3))->toString(),
            "1.2599210498948731648");

  EXPECT_EQ(f(Real(144), Rational(2, 3))->toString(),
            "1728.0");
  EXPECT_EQ(f(Real(144), Rational(4, 3))->toString(),
            "41.569219381653055045");
  EXPECT_EQ(f(Real(2), Rational(3, 5))->toString(),
            "3.1748021039363989495");

  EXPECT_EQ(f(Real(2), Real("2.33"))->toString(),
            "1.3464722988167144947");

  EXPECT_EQ(f(Integer(-10), Integer(2))->toString(),
            "I sqrt(10)");
  EXPECT_EQ(f(Integer(-10), Integer(4))->toString(),
            "root(-10, 4)");
  EXPECT_EQ(f(Integer(-10), Integer(6))->toString(),
            "root(-10, 6)");
  EXPECT_EQ(f(Rational(-9289, 10), Rational(2, 3))->toString(),
            "(-9289/10)^(3/2)");
  EXPECT_EQ(f(Real(-9289), Rational(2, 3))->toString(),
            "(-9289.0)^(3/2)"); // TODO: solve this

  EXPECT_EQ(f(Integer(0), Integer(-1))->toString(),
            "ComplexInf");
  EXPECT_EQ(f(Integer(0), Integer(-10))->toString(),
            "ComplexInf");
  EXPECT_EQ(f(Integer(0), Integer(0))->toString(),
            "Undefined");
  EXPECT_EQ(f(Integer(2), Integer(0))->toString(),
            "Undefined");

  EXPECT_EQ(f(Variable("a"), Integer(2))->toString(),
            "sqrt(a)");
  EXPECT_EQ(f(Variable("a"), Integer(3))->toString(),
            "root(a, 3)");
  EXPECT_EQ(f(Variable("a"), Integer(123))->toString(),
            "root(a, 123)");
  EXPECT_EQ(f(Integer(2), Variable("a"))->toString(),
            "root(2, a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(RootTests, exprTest) {
  EXPECT_EQ(rootExpr(Integer(10), Integer(10))->toString(), "root(10, 10)");
}

TEST(RootTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Root");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
