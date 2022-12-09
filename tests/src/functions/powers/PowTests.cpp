#include "gtest/gtest.h"

#include "fintamath/functions/powers/Pow.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(PowTests, toStringTest) {
  EXPECT_EQ(Pow().toString(), "^");
}

TEST(PowTests, getFunctionTypeTest) {
  EXPECT_EQ(Pow().getFunctionType(), IFunction::Type::Binary);
}

TEST(PowTests, getOperatorPriorityTest) {
  EXPECT_EQ(Pow().getOperatorPriority(), IOperator::Priority::Exponentiation);
}

TEST(PowTests, callTest) {
  EXPECT_EQ(Pow()(Integer(3), Integer(2)).toString(), "9");
  EXPECT_EQ(Pow()(Integer(-3), Integer(2)).toString(), "9");
  EXPECT_EQ(Pow()(Rational(5, 2), Integer(2)).toString(), "25/4");
  EXPECT_EQ(Pow()(Integer(11), Integer(200)).toString(),
            "1899052764604618242121820463954116340585832240009877848127251456103762646167989140750662066593328455813588"
            "1805238401044949435868367905913020005911442340062387227375955664576836341689587626164144676307968892001");

  EXPECT_EQ(Pow()(Integer(4), Rational(1, 2)).toString(), "2");
  EXPECT_EQ(Pow()(Integer(4), Rational(1, 3)).toString(),
            "1.5874010519681994747517056392723082603914933278998530098082857618252165056242192");
  EXPECT_EQ(Pow()(Integer(4), Rational(1, 4)).toString(),
            "1.414213562373095048801688724209698078569671875376948073176679737990732478462107");
  EXPECT_EQ(Pow()(Integer(8), Rational(1, 3)).toString(), "2");
  EXPECT_EQ(Pow()(Integer(16), Rational(1, 4)).toString(), "2");
  EXPECT_EQ(Pow()(Integer(7), Rational(1, 1000)).toString(),
            "1.0019478046608600325035566282397824682830146541368868842018499358998331147926632");
  EXPECT_EQ(Pow()(Pow()(Integer(10), Integer(100)).to<INumber>(), Rational(1, 100)).toString(), "10");
  EXPECT_EQ(Pow()(Integer(4), Rational(5, 2)).toString(), "32");
  EXPECT_EQ(Pow()(Integer(4), Rational(5, 3)).toString(), "10.079368399158985318137684858225826805");
  EXPECT_EQ(Pow()(Integer(4), Rational(5, 4)).toString(), "5.656854249492380195206754896838792314");
  EXPECT_EQ(Pow()(Integer(8), Rational(5, 3)).toString(), "32");
  EXPECT_EQ(Pow()(Integer(16), Rational(5, 4)).toString(), "32");
  EXPECT_EQ(Pow()(Integer(7), Rational(3, 1000)).toString(), "1.005854803201430554046280293844745209");
  EXPECT_EQ(Pow()(Pow()(Integer(10), Integer(300)).to<INumber>(), Rational(1, 100)).toString(), "1000");
  EXPECT_EQ(Pow()(Integer(1), Rational(1, 1234)).toString(), "1");
  EXPECT_EQ(Pow()(Integer(10000000000), Rational(1, 100)).toString(), "1.258925411794167210423954106395800606");

  EXPECT_EQ(Pow()(Integer(4), Rational(-1, 2)).toString(), "0.5");
  EXPECT_EQ(Pow()(Integer(4), Rational(-1, 3)).toString(), "0.629960524947436582383605303639114175");
  EXPECT_EQ(Pow()(Integer(4), Rational(-1, 4)).toString(), "0.707106781186547524400844362104849039");
  EXPECT_EQ(Pow()(Integer(8), Rational(-1, 3)).toString(), "0.5");
  EXPECT_EQ(Pow()(Integer(16), Rational(-1, 4)).toString(), "0.5");
  EXPECT_EQ(Pow()(Integer(4), Rational(-5, 2)).toString(), "0.03125");
  EXPECT_EQ(Pow()(Integer(4), Rational(-5, 3)).toString(), "0.099212565748012467171981602454519266");
  EXPECT_EQ(Pow()(Integer(4), Rational(-5, 4)).toString(), "0.17677669529663688110021109052621226");
  EXPECT_EQ(Pow()(Integer(8), Rational(-5, 3)).toString(), "0.03125");
  EXPECT_EQ(Pow()(Integer(16), Rational(-5, 4)).toString(), "0.03125");
  EXPECT_EQ(Pow()(Integer(7), Rational(-3, 1000)).toString(), "0.994179275992125393883093456029745344");

  EXPECT_ANY_THROW(Pow()(Integer(0), Integer(0)));

  EXPECT_EQ(Pow()(Integer(3), Variable("a")).toString(), "3^a");

  std::unique_ptr<IOperator> o = std::make_unique<Pow>();
  EXPECT_ANY_THROW((*o)(Integer(1)));
  EXPECT_ANY_THROW((*o)(Rational(2, 3)));
  EXPECT_ANY_THROW((*o)());
  EXPECT_ANY_THROW((*o)(Integer(1), Integer(1), Integer(1)));
}
