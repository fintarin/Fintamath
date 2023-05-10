#include <gtest/gtest.h>

#include "fintamath/numbers/NumberFunctions.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

TEST(NumberFunctionsTests, absTest) {
  EXPECT_EQ(abs(cast<INumber>(Integer("-210")))->toString(), "210");
  EXPECT_EQ(abs(cast<INumber>(Integer("4545628562")))->toString(), "4545628562");

  EXPECT_EQ(abs(cast<INumber>(Rational(-1, 100)))->toString(), "1/100");
  EXPECT_EQ(abs(cast<INumber>(Rational(1, -100)))->toString(), "1/100");
  EXPECT_EQ(abs(cast<INumber>(Rational(10, 1000)))->toString(), "1/100");

  EXPECT_EQ(abs(cast<INumber>(Real("8465132.321651651")))->toString(), "8465132.321651651");
  EXPECT_EQ(abs(cast<INumber>(Real("-98465136846516354684651.351")))->toString(), "98465136846516354684651.351");
}

TEST(NumberFunctionsTests, sqrtTest) {
  EXPECT_EQ(sqrt(Integer(25))->toString(), "5");
  EXPECT_EQ(sqrt(Integer(100))->toString(), "10");
  EXPECT_EQ(sqrt(Integer(144))->toString(), "12");
  EXPECT_EQ(sqrt(Integer("10000000000000000000000000000000000000000000000000000"))->toString(),
            "100000000000000000000000000");
  EXPECT_EQ(sqrt(Integer(35))->toString(),
            "5.916079783099616042567328291561617048415501230794340322879719669142822459105653");
  EXPECT_EQ(sqrt(Integer(4212))->toString(),
            "64.899922958351807276145982814468927032523338329214431828788155012089005069274188");
  EXPECT_EQ(sqrt(Integer("992188888888"))->toString(),
            "996086.7878292533601855411744463733737437739712744225743190752774953323543572221");
  EXPECT_EQ(sqrt(Integer("68732648273642987365932706179432649827364"))->toString(),
            "262169121510606178721.58566765529332797469887558257026225414531129497927294552571");

  EXPECT_EQ(sqrt(Rational(25))->toString(), "5");
  EXPECT_EQ(sqrt(Rational(25, 169))->toString(), "5/13");
  EXPECT_EQ(sqrt(Rational(144, 49))->toString(), "12/7");
  EXPECT_EQ(sqrt(Rational(144, 49))->toString(), "12/7");
  EXPECT_EQ(sqrt(Rational("1.44"))->toString(), "6/5");
  EXPECT_EQ(sqrt(Rational(25, 48))->toString(),
            "0.72168783648703220563643597562744681955950218908765859502325290810497209037866668");
  EXPECT_EQ(sqrt(Rational(26, 49))->toString(),
            "0.72843135908468354714688915843182599850911013515708520108356725777513337600888917");
  EXPECT_EQ(sqrt(Rational(45, 67))->toString(),
            "0.81953754706222955297929294102425245239518786681123328404647027909565181499392632");
  EXPECT_EQ(sqrt(Rational("68732648273642987365932706179432649827364.144"))->toString(),
            "262169121510606178721.5856676552933279746991502144551506779910090326304113931067");

  EXPECT_EQ(sqrt(cast<INumber>(Real(144)))->toString(), "12");
  EXPECT_EQ(sqrt(cast<INumber>(Real(2)))->toString(),
            "1.414213562373095048801688724209698078569671875376948073176679737990732478462107");

  EXPECT_THROW(sqrt(Rational(-9289, 10)), UndefinedException);
  EXPECT_THROW(sqrt(Integer(-9289)), UndefinedException);
  EXPECT_THROW(sqrt(*INumber::parse("-9289")), UndefinedException);
}

TEST(NumberFunctionsTests, powTest) {
  EXPECT_EQ(pow(Integer(3), Integer(2))->toString(), "9");
  EXPECT_EQ(pow(Integer(-3), Integer(2))->toString(), "9");
  EXPECT_EQ(pow(Rational(5, 2), Integer(2))->toString(), "25/4");
  EXPECT_EQ(pow(Integer(11), Integer(200))->toString(),
            "1899052764604618242121820463954116340585832240009877848127251456103762646167989140750662066593328455813588"
            "1805238401044949435868367905913020005911442340062387227375955664576836341689587626164144676307968892001");
  EXPECT_EQ(pow(Integer(3), Integer(-2))->toString(), "1/9");
  EXPECT_EQ(pow(Integer(-3), Integer(-2))->toString(), "1/9");
  EXPECT_EQ(pow(Rational(5, 2), Integer(-2))->toString(), "4/25");
  EXPECT_EQ(pow(Integer(11), Integer(-200))->toString(),
            "1/"
            "1899052764604618242121820463954116340585832240009877848127251456103762646167989140750662066593328455813588"
            "1805238401044949435868367905913020005911442340062387227375955664576836341689587626164144676307968892001");

  EXPECT_EQ(pow(Integer(4), Rational(1, 2))->toString(), "2");
  EXPECT_EQ(pow(Integer(4), Rational(1, 3))->toString(),
            "1.5874010519681994747517056392723082603914933278998530098082857618252165056242192");
  EXPECT_EQ(pow(Integer(4), Rational(1, 4))->toString(),
            "1.414213562373095048801688724209698078569671875376948073176679737990732478462107");
  EXPECT_EQ(pow(Integer(8), Rational(1, 3))->toString(), "2");
  EXPECT_EQ(pow(Integer(16), Rational(1, 4))->toString(), "2");
  EXPECT_EQ(pow(Integer(7), Rational(1, 1000))->toString(),
            "1.0019478046608600325035566282397824682830146541368868842018499358998331147926632");
  EXPECT_EQ(pow(*pow(Integer(10), Integer(100)), Rational(1, 100))->toString(), "10");
  EXPECT_EQ(pow(Integer(4), Rational(5, 2))->toString(), "32");
  EXPECT_EQ(pow(Integer(4), Rational(5, 3))->toString(),
            "10.079368399158985318137684858225826804562011717612063840655800897242397412111676");
  EXPECT_EQ(pow(Integer(4), Rational(5, 4))->toString(),
            "5.6568542494923801952067548968387923142786875015077922927067189519629299138484282");
  EXPECT_EQ(pow(Integer(8), Rational(5, 3))->toString(), "32");
  EXPECT_EQ(pow(Integer(16), Rational(5, 4))->toString(), "32");
  EXPECT_EQ(pow(Integer(7), Rational(3, 1000))->toString(),
            "1.0058548032014305540462802938447452087153844969521205792334942435663538095322262");
  EXPECT_EQ(pow(*pow(Integer(10), Integer(300)), Rational(1, 100))->toString(), "1000");
  EXPECT_EQ(pow(Integer(1), Rational(1, 1234))->toString(), "1");
  EXPECT_EQ(pow(Integer(10000000000), Rational(1, 100))->toString(),
            "1.258925411794167210423954106395800606093617409466931069107923019526647615782502");

  EXPECT_EQ(pow(Integer(4), Rational(-1, 2))->toString(), "1/2");
  EXPECT_EQ(pow(Integer(4), Rational(-1, 3))->toString(),
            "0.62996052494743658238360530363911417528512573235075399004098755607764983825697974");
  EXPECT_EQ(pow(Integer(4), Rational(-1, 4))->toString(),
            "0.70710678118654752440084436210484903928483593768847403658833986899536623923105352");
  EXPECT_EQ(pow(Integer(8), Rational(-1, 3))->toString(), "0.5");
  EXPECT_EQ(pow(Integer(16), Rational(-1, 4))->toString(), "0.5");
  EXPECT_EQ(pow(Integer(4), Rational(-5, 2))->toString(), "1/32");
  EXPECT_EQ(pow(Integer(4), Rational(-5, 3))->toString(),
            "0.099212565748012467171981602454519266274468332993740813113017860114076031601513698");
  EXPECT_EQ(pow(Integer(4), Rational(-5, 4))->toString(),
            "0.17677669529663688110021109052621225982120898442211850914708496724884155980776338");
  EXPECT_EQ(pow(Integer(8), Rational(-5, 3))->toString(), "0.03125");
  EXPECT_EQ(pow(Integer(16), Rational(-5, 4))->toString(), "0.03125");
  EXPECT_EQ(pow(Integer(7), Rational(-3, 1000))->toString(),
            "0.99417927599212539388309345602974534386950277212157482682781039330883285005190623");

  EXPECT_EQ(pow(Rational("-10"), Rational("-3"))->toString(), "-1/1000");
  EXPECT_EQ(pow(Rational("-1"), Rational("-25"))->toString(), "-1");
  EXPECT_EQ(pow(Rational("-2.2"), Rational("-5"))->toString(), "-3125/161051");

  EXPECT_EQ(pow(Real("-10"), Rational("-3"))->toString(), "-0.001");
  EXPECT_EQ(pow(Real("-1"), Rational("-25"))->toString(), "-1");
  EXPECT_EQ(pow(Real("-2.2"), Rational("-5"))->toString(),
            "-0.019403791345598599201495178545926445660070412478034908196782385703907457886011264");

  EXPECT_EQ(pow(Rational("-10"), Real("-3"))->toString(), "-0.001");
  EXPECT_EQ(pow(Rational("-1"), Real("-25"))->toString(), "-1");
  EXPECT_EQ(pow(Rational("-2.2"), Real("-5"))->toString(),
            "-0.019403791345598599201495178545926445660070412478034908196782385703907457886011264");

  EXPECT_THROW(pow(Integer(0), Integer(0)), UndefinedException);
  EXPECT_THROW(pow(Rational("0"), Rational("-10")), UndefinedException);
  EXPECT_THROW(pow(Rational("-10"), Rational("-1.5")), UndefinedException);
}
