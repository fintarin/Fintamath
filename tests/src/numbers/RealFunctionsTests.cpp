#include <gtest/gtest.h>

#include "fintamath/numbers/RealFunctions.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"

using namespace fintamath;

TEST(RealFunctionsTests, absTest) {
  EXPECT_EQ(abs(Real("8465132.321651651")).toString(), "8465132.321651651");
  EXPECT_EQ(abs(Real("-98465136846516354684651.351")).toString(), "98465136846516354684651.351");
  EXPECT_EQ(abs(Real("0")).toString(), "0");
}

TEST(RealFunctionsTests, sqrtTest) {
  EXPECT_EQ(sqrt(Real(1)).toString(), "1");
  EXPECT_EQ(sqrt(Real(4)).toString(), "2");
  EXPECT_EQ(sqrt(Real(144)).toString(), "12");
  EXPECT_EQ(sqrt(Real("1000000000000000000")).toString(), "1000000000");

  EXPECT_EQ(sqrt(Real(2)).toString(),
            "1.414213562373095048801688724209698078569671875376948073176679737990732478462107");
  EXPECT_EQ(sqrt(Real(3)).toString(), "1.7320508075688772935274463415058723669428052538103806280558069794519330169088");
  EXPECT_EQ(sqrt(Real(13274)).toString(),
            "115.21284650593439790572652382777691656117309945220258699979613263506905239760152");
  EXPECT_EQ(sqrt(Real("1.44")).toString(), "1.2");
  EXPECT_EQ(sqrt(Real("44.3556")).toString(), "6.66");
  EXPECT_EQ(sqrt(Real("23525.32323")).toString(),
            "153.37967019784597254922041215127507814346477967726767479847319100257746203803536");

  EXPECT_THROW(sqrt(Real(-10)), UndefinedFunctionException);
}

TEST(RealFunctionsTests, powTest) {
  EXPECT_EQ(pow(Real("10"), Real("0")).toString(), "1");
  EXPECT_EQ(pow(Real("-10"), Real("3")).toString(), "-1000");
  EXPECT_EQ(pow(Real("1"), Real("25")).toString(), "1");
  EXPECT_EQ(pow(Real("2.2"), Real("5")).toString(), "51.53632");
  EXPECT_EQ(pow(Real("1.61051"), Real("0.2")).toString(), "1.1");
  EXPECT_EQ(pow(Real("10"), Real("10000")).toString(), "1*10^10000");
  EXPECT_EQ(pow(Real("20"), Real("10000")).toString(),
            "1.9950631168807583848837421626835850838234968318861924548520089498529438830221947*10^13010");
  EXPECT_EQ(pow(Real("10"), Real("-10000")).toString(), "1*10^-10000");
  EXPECT_EQ(pow(Real("-10"), Real("-3")).toString(), "-0.001");
  EXPECT_EQ(pow(Real("-1"), Real("-25")).toString(), "-1");
  EXPECT_EQ(pow(Real("-2.2"), Real("-5")).toString(),
            "-0.019403791345598599201495178545926445660070412478034908196782385703907457886011264");
  EXPECT_EQ(pow(Real("-10"), Real("-10000")).toString(), "1*10^-10000");
  EXPECT_EQ(pow(Real("-20"), Real("-10000")).toString(),
            "5.012372749206452009297555933742977749321567781338425839421429042279239530950784*10^-13011");

  EXPECT_THROW(pow(Real("0"), Real("0")), UndefinedBinaryOperatorException);
  EXPECT_THROW(pow(Real("0"), Real("-10")), UndefinedBinaryOperatorException);
  EXPECT_THROW(pow(Real("-10"), Real("-1.5")), UndefinedBinaryOperatorException);
}

TEST(RealFunctionsTests, expTest) {
  EXPECT_EQ(exp(Real("1")).toString(),
            "2.7182818284590452353602874713526624977572470936999595749669676277240766303535476");
  EXPECT_EQ(exp(Real("0.5")).toString(),
            "1.6487212707001281468486507878141635716537761007101480115750793116406610211942156");
  EXPECT_EQ(exp(Real("10")).toString(),
            "22026.465794806716516957900645284244366353512618556781074235426355225202818570793");
}

TEST(RealFunctionsTests, logTest) {
  EXPECT_EQ(log(Real("2"), Real("32")).toString(), "5");
  EXPECT_EQ(log(Real("6.6"), Real("1897.4736")).toString(), "4");
  EXPECT_EQ(log(Real("25625423589"), Real("1")).toString(), "0");

  EXPECT_THROW(log(Real("1"), Real("66")), UndefinedFunctionException);
  EXPECT_THROW(log(Real("-10"), Real("10")), UndefinedFunctionException);
  EXPECT_THROW(log(Real("1"), Real("-10")), UndefinedFunctionException);
  EXPECT_THROW(log(Real("0"), Real("0")), UndefinedFunctionException);
}

TEST(RealFunctionsTests, lnTest) {
  EXPECT_EQ(ln(Real("1")).toString(), "0");
  EXPECT_EQ(ln(Real("66")).toString(),
            "4.1896547420264255448744209363458315725446975461204218810739420522614615391015404");

  EXPECT_THROW(ln(Real("0")), UndefinedFunctionException);
  EXPECT_THROW(ln(Real("-33")), UndefinedFunctionException);
}

TEST(RealFunctionsTests, lbTest) {
  EXPECT_EQ(lb(Real("2")).toString(), "1");
  EXPECT_EQ(lb(Real("1024")).toString(), "10");

  EXPECT_THROW(lb(Real("-1")), UndefinedFunctionException);
}

TEST(RealFunctionsTests, lgTest) {
  EXPECT_EQ(lg(Real("0.001")).toString(), "-3");
  EXPECT_EQ(lg(Real("25")).toString(),
            "1.397940008672037609572522210551013946463620237075782917379145077745783621451151");

  EXPECT_THROW(lg(Real("0")), UndefinedFunctionException);
}

TEST(RealFunctionsTests, sinTest) {
  EXPECT_EQ(sin(Real("0")).toString(), "0");
  EXPECT_EQ(sin(Real("-1")).toString(),
            "-0.84147098480789650665250232163029899962256306079837106567275170999191040439123967");
  EXPECT_EQ(sin(Real("360")).toString(),
            "0.95891572341430650775887594775378440067396475320176419597230510239310187233155217");
}

TEST(RealFunctionsTests, cosTest) {
  EXPECT_EQ(cos(Real("0")).toString(), "1");
  EXPECT_EQ(cos(Real("1")).toString(),
            "0.54030230586813971740093660744297660373231042061792222767009725538110039477447176");
  EXPECT_EQ(cos(Real("125")).toString(),
            "0.78771451214423447462921467726566085443902399155278651945734350565151508650071467");
}

TEST(RealFunctionsTests, tanTest) {
  EXPECT_EQ(tan(Real("0")).toString(), "0");
  EXPECT_EQ(tan(Real("-10")).toString(),
            "-0.6483608274590866712591249330098086768168743429837249756336279673958556003746239");
  EXPECT_EQ(tan(Real("1.5")).toString(),
            "14.101419947171719387646083651987756445659543577235861866123267586089696270414155");

  EXPECT_THROW(tan(Real(getPi() / 2)), UndefinedFunctionException);
}

TEST(RealFunctionsTests, cotTest) {
  EXPECT_EQ(cot(Real("1")).toString(),
            "0.64209261593433070300641998659426562023027811391817137910116228042627685683916467");
  EXPECT_EQ(cot(Real("200")).toString(),
            "-0.55787150213477006971046091195634798429557648836442892718891989460860978240822024");
  EXPECT_EQ(cot(Real("0.001")).toString(),
            "999.9996666666444444423280421164020950243150821349686957930420507767438195464464");

  EXPECT_THROW(cot(Real("0")), UndefinedFunctionException);
}

TEST(RealFunctionsTests, asinTest) {
  EXPECT_EQ(asin(Real("0")).toString(), "0");
  EXPECT_EQ(
      asin(Real("-0.84147098480789650665250232163029899962256306079837106567275170999191040439123967")).toString(),
      "-1");

  EXPECT_THROW(asin(Real("10")), UndefinedFunctionException);
  EXPECT_THROW(asin(Real("-10")), UndefinedFunctionException);
}

TEST(RealFunctionsTests, acosTest) {
  EXPECT_EQ(acos(Real("-1")).toString(),
            "3.141592653589793238462643383279502884197169399375105820974944592307816406286209");
  EXPECT_EQ(acos(Real("0.54030230586813971740093660744297660373231042061792222767009725538110039477447176")).toString(),
            "1");

  EXPECT_THROW(acos(Real("10")), UndefinedFunctionException);
  EXPECT_THROW(acos(Real("-10")), UndefinedFunctionException);
}

TEST(RealFunctionsTests, atanTest) {
  EXPECT_EQ(atan(Real("0")).toString(), "0");
  EXPECT_EQ(atan(Real("14.101419947171719387646083651987756445659543577235861866123267586089696270414155")).toString(),
            "1.5");
}

TEST(RealFunctionsTests, acotTest) {
  EXPECT_EQ(acot(Real("1")).toString(),
            "0.78539816339744830961566084581987572104929234984377645524373614807695410157155225");
  EXPECT_EQ(acot(Real("999.9996666666444444423280421164020950243150821349686957930420507767438195464464")).toString(),
            "0.001");

  EXPECT_THROW(acot(Real(0)), UndefinedFunctionException);
}

TEST(RealFunctionsTests, sinhTest) {
  EXPECT_EQ(sinh(Real("0")).toString(), "0");
  EXPECT_EQ(sinh(Real("-1")).toString(),
            "-1.1752011936438014568823818505956008151557179813340958702295654130133075673043239");
  EXPECT_EQ(sinh(Real("360")).toString(),
            "1.1091326487692776999948329517793349595727082777083535707260458682053441771196906*10^156");
}

TEST(RealFunctionsTests, coshTest) {
  EXPECT_EQ(cosh(Real("0")).toString(), "1");
  EXPECT_EQ(cosh(Real("1")).toString(),
            "1.5430806348152437784779056207570616826015291123658637047374022147107690630492237");
  EXPECT_EQ(cosh(Real("125")).toString(),
            "967788021017861284360312245263743609428141503861911628.64033144120749560890919683");
}

TEST(RealFunctionsTests, tanhTest) {
  EXPECT_EQ(tanh(Real("0")).toString(), "0");
  EXPECT_EQ(tanh(Real("-10")).toString(),
            "-0.99999999587769276361959283713827574105081461849501996226140069543680188089876683");
  EXPECT_EQ(tanh(Real("1.5")).toString(),
            "0.90514825364486643824230369645649559722764113515878179856422398245110257699457953");
}

TEST(RealFunctionsTests, cothTest) {
  EXPECT_EQ(coth(Real("1")).toString(),
            "1.3130352854993313036361612469308478329120139412404526555431529675670842704618744");
  EXPECT_EQ(coth(Real("200")).toString(), "1");
  EXPECT_EQ(coth(Real("0.001")).toString(),
            "1000.0003333333111111132275130158730372508128641887448236432439795543114729807153");

  EXPECT_THROW(coth(Real("0")), UndefinedFunctionException);
}

TEST(RealFunctionsTests, asinhTest) {
  EXPECT_EQ(asinh(Real("0")).toString(), "0");
  EXPECT_EQ(asinh(Real("10")).toString(),
            "2.9982229502979697388465955375964534766070580548773036557344592627530896573521661");
  EXPECT_EQ(asinh(Real("-10")).toString(),
            "-2.9982229502979697388465955375964534766070580548773036557344592627530896573521661");
}

TEST(RealFunctionsTests, acoshTest) {
  EXPECT_EQ(acosh(Real("1")).toString(), "0");
  EXPECT_EQ(acosh(Real("10")).toString(),
            "2.9932228461263808979126677137741829130836604511809806426851456009774992267097399");

  EXPECT_THROW(acosh(Real("-1")), UndefinedFunctionException);
  EXPECT_THROW(acosh(Real("0")), UndefinedFunctionException);
}

TEST(RealFunctionsTests, atanhTest) {
  EXPECT_EQ(atanh(Real("0")).toString(), "0");
  EXPECT_EQ(atanh(Real("0.5")).toString(),
            "0.54930614433405484569762261846126285232374527891137472586734716681874714660930448");

  EXPECT_THROW(atanh(Real("-1")), UndefinedFunctionException);
  EXPECT_THROW(atanh(Real("1")), UndefinedFunctionException);
}

TEST(RealFunctionsTests, acothTest) {
  EXPECT_EQ(acoth(Real("10")).toString(),
            "0.10033534773107558063572655206003894526336286914595913587458952092779251873800939");
  EXPECT_EQ(acoth(Real("-10")).toString(),
            "-0.10033534773107558063572655206003894526336286914595913587458952092779251873800939");

  EXPECT_THROW(acoth(Real("-1")), UndefinedFunctionException);
  EXPECT_THROW(acoth(Real("0")), UndefinedFunctionException);
  EXPECT_THROW(acoth(Real("1")), UndefinedFunctionException);
}

TEST(RealFunctionsTests, getETest) {
  EXPECT_EQ(getE().toString(), "2.7182818284590452353602874713526624977572470936999595749669676277240766303535476");
}

TEST(RealFunctionsTests, getEPiTest) {
  EXPECT_EQ(getPi().toString(), "3.141592653589793238462643383279502884197169399375105820974944592307816406286209");
}
