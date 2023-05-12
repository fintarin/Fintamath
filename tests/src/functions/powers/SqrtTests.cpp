#include "gtest/gtest.h"

#include "fintamath/functions/powers/Sqrt.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Sqrt f;

TEST(SqrtTests, toStringTest) {
  EXPECT_EQ(f.toString(), "sqrt");
}

TEST(SqrtTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(SqrtTests, callTest) {
  EXPECT_EQ(f(Integer(100))->toString(), "10");
  EXPECT_EQ(f(Integer(25))->toString(), "5");
  EXPECT_EQ(f(Integer(100))->toString(), "10");
  EXPECT_EQ(f(Integer(144))->toString(), "12");
  EXPECT_EQ(f(Integer("10000000000000000000000000000000000000000000000000000"))->toString(),
            "100000000000000000000000000");
  EXPECT_EQ(f(Integer(10))->toString(),
            "3.1622776601683793319988935444327185337195551393252168268575048527925944386392382");
  EXPECT_EQ(f(Integer(35))->toString(),
            "5.916079783099616042567328291561617048415501230794340322879719669142822459105653");
  EXPECT_EQ(f(Integer(4212))->toString(),
            "64.899922958351807276145982814468927032523338329214431828788155012089005069274188");
  EXPECT_EQ(f(Integer("992188888888"))->toString(),
            "996086.7878292533601855411744463733737437739712744225743190752774953323543572221");
  EXPECT_EQ(f(Integer("68732648273642987365932706179432649827364"))->toString(),
            "262169121510606178721.58566765529332797469887558257026225414531129497927294552571");

  EXPECT_EQ(f(Rational(25))->toString(), "5");
  EXPECT_EQ(f(Rational(25, 169))->toString(), "5/13");
  EXPECT_EQ(f(Rational(144, 49))->toString(), "12/7");
  EXPECT_EQ(f(Rational(144, 49))->toString(), "12/7");
  EXPECT_EQ(f(Rational("1.44"))->toString(), "6/5");
  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "0.31622776601683793319988935444327185337195551393252168268575048527925944386392382");
  EXPECT_EQ(f(Rational(25, 48))->toString(),
            "0.72168783648703220563643597562744681955950218908765859502325290810497209037866668");
  EXPECT_EQ(f(Rational(26, 49))->toString(),
            "0.72843135908468354714688915843182599850911013515708520108356725777513337600888917");
  EXPECT_EQ(f(Rational(45, 67))->toString(),
            "0.81953754706222955297929294102425245239518786681123328404647027909565181499392632");
  EXPECT_EQ(f(Rational("68732648273642987365932706179432649827364.144"))->toString(),
            "262169121510606178721.5856676552933279746991502144551506779910090326304113931067");

  EXPECT_EQ(f(Real(144))->toString(), "12");
  EXPECT_EQ(f(Real(2))->toString(), "1.414213562373095048801688724209698078569671875376948073176679737990732478462107");

  EXPECT_EQ(f(Variable("a"))->toString(), "sqrt(a)");

  EXPECT_THROW(f(Integer(-10)), UndefinedFunctionException);
  EXPECT_THROW(f(Rational(-9289, 10)), UndefinedException);
  EXPECT_THROW(f(Real(-9289)), UndefinedException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(SqrtTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(SqrtTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Sqrt());
  EXPECT_EQ(Sqrt(), f);
  EXPECT_EQ(f, cast<IMathObject>(Sqrt()));
  EXPECT_EQ(cast<IMathObject>(Sqrt()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(SqrtTests, getTypeIdTest) {
  EXPECT_EQ(Sqrt::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Sqrt));
  EXPECT_EQ(Sqrt().getTypeId(), MathObjectTypeId(MathObjectType::Sqrt));
}
