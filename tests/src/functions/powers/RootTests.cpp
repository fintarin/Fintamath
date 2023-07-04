#include "gtest/gtest.h"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/powers/Root.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Root f;

TEST(RootTests, toStringTest) {
  EXPECT_EQ(f.toString(), "root");
}

TEST(RootTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(RootTests, callTest) {
  EXPECT_EQ(f(Integer(10), Integer(1))->toString(), "10");
  EXPECT_EQ(f(Integer(-10), Integer(1))->toString(), "-10");
  EXPECT_EQ(f(Integer(100), Integer(2))->toString(), "10");
  EXPECT_EQ(f(Integer(25), Integer(2))->toString(), "5");
  EXPECT_EQ(f(Integer(144), Integer(2))->toString(), "12");
  EXPECT_EQ(f(Integer("10000000000000000000000000000000000000000000000000000"), Integer(2))->toString(),
            "100000000000000000000000000");
  EXPECT_EQ(f(Integer(10), Integer(2))->toString(), "sqrt(10)");
  EXPECT_EQ(f(Integer(35), Integer(2))->toString(), "sqrt(35)");
  EXPECT_EQ(f(Integer(4212), Integer(2))->toString(), "18 sqrt(13)");
  EXPECT_EQ(f(Integer("992188888888"), Integer(2))->toString(), "2 sqrt(248047222222)");
  EXPECT_EQ(f(Integer("68732648273642987365932706179432649827364"), Integer(2))->toString(),
            "2 sqrt(17183162068410746841483176544858162456841)");
  EXPECT_EQ(f(Integer(100), Integer(3))->toString(), "root(100, 3)");
  EXPECT_EQ(f(Integer(25), Integer(3))->toString(), "root(25, 3)");
  EXPECT_EQ(f(Integer(144), Integer(3))->toString(), "2 root(18, 3)");
  EXPECT_EQ(f(Integer("10000000000000000000000000000000000000000000000000000"), Integer(3))->toString(),
            "100000000000000000 root(10, 3)");
  EXPECT_EQ(f(Integer(10), Integer(3))->toString(), "root(10, 3)");
  EXPECT_EQ(f(Integer(35), Integer(3))->toString(), "root(35, 3)");
  EXPECT_EQ(f(Integer(4212), Integer(3))->toString(), "3 root(156, 3)");
  EXPECT_EQ(f(Integer("992188888888"), Integer(3))->toString(), "2 root(124023611111, 3)");
  EXPECT_EQ(f(Integer("68732648273642987365932706179432649827364"), Integer(3))->toString(),
            "root(68732648273642987365932706179432649827364, 3)");
  EXPECT_EQ(f(Integer(1024), Integer(3))->toString(), "8 root(2, 3)");
  EXPECT_EQ(f(Integer(1024), Integer(5))->toString(), "4");
  EXPECT_EQ(f(Integer(1024), Integer(10))->toString(), "2");

  EXPECT_EQ(f(Rational(25), Integer(4))->toString(), "sqrt(5)");
  EXPECT_EQ(f(Rational(25, 169), Integer(4))->toString(), "sqrt(5)/sqrt(13)");
  EXPECT_EQ(f(Rational(144, 49), Integer(4))->toString(), "(2 sqrt(3))/sqrt(7)");
  EXPECT_EQ(f(Rational("1.44"), Integer(4))->toString(), "sqrt(6)/sqrt(5)");
  EXPECT_EQ(f(Rational(1, 10), Integer(4))->toString(), "1/root(10, 4)");
  EXPECT_EQ(f(Rational(25, 48), Integer(4))->toString(), "sqrt(5)/(2 root(3, 4))");
  EXPECT_EQ(f(Rational(26, 49), Integer(4))->toString(), "root(26, 4)/sqrt(7)");
  EXPECT_EQ(f(Rational(45, 67), Integer(4))->toString(), "(sqrt(3) root(5, 4))/root(67, 4)");
  EXPECT_EQ(f(Rational("68732648273642987365932706179432649827364.144"), Integer(4))->toString(),
            "root(8591581034205373420741588272429081228420518, 4)/root(125, 4)");

  EXPECT_EQ(f(Rational(25), Rational(4, 3))->toString(), "5 sqrt(5)");
  EXPECT_EQ(f(Rational(25, 169), Rational(4, 3))->toString(), "(5 sqrt(5))/(13 sqrt(13))");
  EXPECT_EQ(f(Rational(144, 49), Rational(4, 3))->toString(), "(24 sqrt(3))/(7 sqrt(7))");
  EXPECT_EQ(f(Rational("1.44"), Rational(4, 3))->toString(), "(6 sqrt(6))/(5 sqrt(5))");
  EXPECT_EQ(f(Rational(1, 10), Rational(4, 3))->toString(), "1/root(1000, 4)");
  EXPECT_EQ(f(Rational(25, 48), Rational(4, 3))->toString(), "(5 sqrt(5))/(8 root(27, 4))");
  EXPECT_EQ(f(Rational(26, 49), Rational(4, 3))->toString(), "root(17576, 4)/(7 sqrt(7))");
  EXPECT_EQ(f(Rational(45, 67), Rational(4, 3))->toString(), "(3 sqrt(3) root(125, 4))/root(300763, 4)");
  EXPECT_EQ(f(Rational("68732648273642987365932706179432649827364.144"), Rational(4, 3))->toString(),
            "root("
            "6341898279505748220737558733036392804899042006384472743062801876828565493307610084438050180592269960571521"
            "04826353254809443231832, 4)/(25 root(5, 4))");

  EXPECT_EQ(f(Real(144), Integer(2))->toString(), "12");
  EXPECT_EQ(f(Real(144), Integer(4))->toString(),
            "3.4641016151377545870548926830117447338856105076207612561116139589038660338176001");
  EXPECT_EQ(f(Real(2), Integer(3))->toString(),
            "1.2599210498948731647672106072782283505702514647015079800819751121552996765139595");

  EXPECT_EQ(f(Real(144), Rational(2, 3))->toString(), "1728");
  EXPECT_EQ(f(Real(144), Rational(4, 3))->toString(),
            "41.569219381653055044658712196140936806627326091449135073339367506846392405811201");
  EXPECT_EQ(f(Real(2), Rational(3, 5))->toString(),
            "3.1748021039363989495034112785446165207829866557997060196165715236504330112484383");

  EXPECT_EQ(f(Real(2), Real("2.33"))->toString(),
            "1.3464722988167144947473840795888543539968696938592078715906325948094320119117764");

  EXPECT_EQ(f(Variable("a"), Integer(2))->toString(), "sqrt(a)");
  EXPECT_EQ(f(Variable("a"), Integer(3))->toString(), "root(a, 3)");
  EXPECT_EQ(f(Variable("a"), Integer(123))->toString(), "root(a, 123)");
  EXPECT_EQ(f(Integer(2), Variable("a"))->toString(), "2^(1/a)");

  EXPECT_THROW(f(Integer(-10), Integer(2)), UndefinedException);
  EXPECT_THROW(f(Rational(-9289, 10), Rational(2, 3)), UndefinedException);
  EXPECT_THROW(f(Real(-9289), Rational(2, 3)), UndefinedException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
