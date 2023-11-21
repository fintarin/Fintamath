#include <gtest/gtest.h>

#include "fintamath/numbers/RealFunctions.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"

using namespace fintamath;

TEST(RealFunctionsTests, floorTest) {
  EXPECT_EQ(floor(Real("-1000.8")).toString(), "-1001");
  EXPECT_EQ(floor(Real("-1000.1")).toString(), "-1001");
  EXPECT_EQ(floor(Real("-1000")).toString(), "-1000");
  EXPECT_EQ(floor(Real("-1.9")).toString(), "-2");
  EXPECT_EQ(floor(Real("-1.5")).toString(), "-2");
  EXPECT_EQ(floor(Real("-1.3")).toString(), "-2");
  EXPECT_EQ(floor(Real("-1")).toString(), "-1");
  EXPECT_EQ(floor(Real("-0.9")).toString(), "-1");
  EXPECT_EQ(floor(Real("-0.3")).toString(), "-1");
  EXPECT_EQ(floor(Real("0")).toString(), "0");
  EXPECT_EQ(floor(Real("0.3")).toString(), "0");
  EXPECT_EQ(floor(Real("0.9")).toString(), "0");
  EXPECT_EQ(floor(Real("1")).toString(), "1");
  EXPECT_EQ(floor(Real("1.9")).toString(), "1");
  EXPECT_EQ(floor(Real("1.5")).toString(), "1");
  EXPECT_EQ(floor(Real("1.3")).toString(), "1");
  EXPECT_EQ(floor(Real("1000")).toString(), "1000");
  EXPECT_EQ(floor(Real("1000.1")).toString(), "1000");
  EXPECT_EQ(floor(Real("1000.8")).toString(), "1000");
}

TEST(RealFunctionsTests, ceilTest) {
  EXPECT_EQ(ceil(Real("-1000.8")).toString(), "-1000");
  EXPECT_EQ(ceil(Real("-1000.1")).toString(), "-1000");
  EXPECT_EQ(ceil(Real("-1000")).toString(), "-1000");
  EXPECT_EQ(ceil(Real("-1.9")).toString(), "-1");
  EXPECT_EQ(ceil(Real("-1.5")).toString(), "-1");
  EXPECT_EQ(ceil(Real("-1.3")).toString(), "-1");
  EXPECT_EQ(ceil(Real("-1")).toString(), "-1");
  EXPECT_EQ(ceil(Real("-0.9")).toString(), "0");
  EXPECT_EQ(ceil(Real("-0.3")).toString(), "0");
  EXPECT_EQ(ceil(Real("0")).toString(), "0");
  EXPECT_EQ(ceil(Real("0.3")).toString(), "1");
  EXPECT_EQ(ceil(Real("0.9")).toString(), "1");
  EXPECT_EQ(ceil(Real("1")).toString(), "1");
  EXPECT_EQ(ceil(Real("1.9")).toString(), "2");
  EXPECT_EQ(ceil(Real("1.5")).toString(), "2");
  EXPECT_EQ(ceil(Real("1.3")).toString(), "2");
  EXPECT_EQ(ceil(Real("1000")).toString(), "1000");
  EXPECT_EQ(ceil(Real("1000.1")).toString(), "1001");
  EXPECT_EQ(ceil(Real("1000.8")).toString(), "1001");
}

TEST(RealFunctionsTests, absTest) {
  EXPECT_EQ(abs(Real("8465132.321651651")).toString(), "8465132.321651651");
  EXPECT_EQ(abs(Real("-98465136846516354684651.351")).toString(), "98465136846516354684651.351");
  EXPECT_EQ(abs(Real("0")).toString(), "0.0");
}

TEST(RealFunctionsTests, sqrtTest) {
  EXPECT_EQ(sqrt(Real(1)).toString(), "1.0");
  EXPECT_EQ(sqrt(Real(4)).toString(), "2.0");
  EXPECT_EQ(sqrt(Real(144)).toString(), "12.0");
  EXPECT_EQ(sqrt(Real("1000000000000000000")).toString(), "1000000000.0");

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
  EXPECT_EQ(pow(Real("10"), Real("0")).toString(), "1.0");
  EXPECT_EQ(pow(Real("-10"), Real("3")).toString(), "-1000.0");
  EXPECT_EQ(pow(Real("1"), Real("25")).toString(), "1.0");
  EXPECT_EQ(pow(Real("2.2"), Real("5")).toString(), "51.53632");
  EXPECT_EQ(pow(Real("1.61051"), Real("0.2")).toString(), "1.1");
  EXPECT_EQ(pow(Real("10"), Real("10000")).toString(), "1.0*10^10000");
  EXPECT_EQ(pow(Real("20"), Real("10000")).toString(),
            "1.9950631168807583848837421626835850838234968318861924548520089498529438830221947*10^13010");
  EXPECT_EQ(pow(Real("10"), Real("-10000")).toString(), "1.0*10^-10000");
  EXPECT_EQ(pow(Real("-10"), Real("-3")).toString(), "-0.001");
  EXPECT_EQ(pow(Real("-1"), Real("-25")).toString(), "-1.0");
  EXPECT_EQ(pow(Real("-2.2"), Real("-5")).toString(),
            "-0.019403791345598599201495178545926445660070412478034908196782385703907457886011264");
  EXPECT_EQ(pow(Real("-10"), Real("-10000")).toString(), "1.0*10^-10000");
  EXPECT_EQ(pow(Real("-20"), Real("-10000")).toString(),
            "5.012372749206452009297555933742977749321567781338425839421429042279239530950784*10^-13011");

  EXPECT_THROW(pow(Real("0"), Real("0")), UndefinedBinaryOperatorException);
  EXPECT_THROW(pow(Real("0"), Real("-10")), UndefinedBinaryOperatorException);
  EXPECT_THROW(pow(Real("-10"), Real("-1.5")), UndefinedBinaryOperatorException);
  EXPECT_THROW(pow(Real("10"), Real("100000000000000000000")), UndefinedBinaryOperatorException);
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
  EXPECT_EQ(log(Real("2"), Real("32")).toString(), "5.0");
  EXPECT_EQ(log(Real("6.6"), Real("1897.4736")).toString(), "4.0");
  EXPECT_EQ(log(Real("25625423589"), Real("1")).toString(), "0.0");

  EXPECT_THROW(log(Real("1"), Real("66")), UndefinedFunctionException);
  EXPECT_THROW(log(Real("-10"), Real("10")), UndefinedFunctionException);
  EXPECT_THROW(log(Real("1"), Real("-10")), UndefinedFunctionException);
  EXPECT_THROW(log(Real("0"), Real("0")), UndefinedFunctionException);
}

TEST(RealFunctionsTests, lnTest) {
  EXPECT_EQ(ln(Real("1")).toString(), "0.0");
  EXPECT_EQ(ln(Real("66")).toString(),
            "4.1896547420264255448744209363458315725446975461204218810739420522614615391015404");

  EXPECT_THROW(ln(Real("0")), UndefinedFunctionException);
  EXPECT_THROW(ln(Real("-33")), UndefinedFunctionException);
}

TEST(RealFunctionsTests, lbTest) {
  EXPECT_EQ(lb(Real("2")).toString(), "1.0");
  EXPECT_EQ(lb(Real("1024")).toString(), "10.0");

  EXPECT_THROW(lb(Real("-1")), UndefinedFunctionException);
}

TEST(RealFunctionsTests, lgTest) {
  EXPECT_EQ(lg(Real("0.001")).toString(), "-3.0");
  EXPECT_EQ(lg(Real("25")).toString(),
            "1.397940008672037609572522210551013946463620237075782917379145077745783621451151");

  EXPECT_THROW(lg(Real("0")), UndefinedFunctionException);
}

TEST(RealFunctionsTests, sinTest) {
  EXPECT_EQ(sin(Real("0")).toString(), "0.0");
  EXPECT_EQ(sin(Real("-1")).toString(),
            "-0.84147098480789650665250232163029899962256306079837106567275170999191040439123967");
  EXPECT_EQ(sin(Real("360")).toString(),
            "0.95891572341430650775887594775378440067396475320176419597230510239310187233155217");
  EXPECT_EQ(sin(pow(Real(11), -100)).toString(),
            "7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(sin(-pow(Real(11), -100)).toString(),
            "-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");

  EXPECT_THROW(sin(pow(Real(11), 100)), UndefinedFunctionException);
  EXPECT_THROW(sin(-pow(Real(11), 100)), UndefinedFunctionException);
}

TEST(RealFunctionsTests, cosTest) {
  EXPECT_EQ(cos(Real("0")).toString(), "1.0");
  EXPECT_EQ(cos(Real("1")).toString(),
            "0.54030230586813971740093660744297660373231042061792222767009725538110039477447176");
  EXPECT_EQ(cos(Real("125")).toString(),
            "0.78771451214423447462921467726566085443902399155278651945734350565151508650071467");
  EXPECT_EQ(cos(pow(Real(11), -100)).toString(),
            "1.0");
  EXPECT_EQ(cos(-pow(Real(11), -100)).toString(),
            "1.0");

  EXPECT_THROW(cos(pow(Real(11), 100)), UndefinedFunctionException);
  EXPECT_THROW(cos(-pow(Real(11), 100)), UndefinedFunctionException);
}

TEST(RealFunctionsTests, tanTest) {
  EXPECT_EQ(tan(Real("0")).toString(), "0.0");
  EXPECT_EQ(tan(Real("-10")).toString(),
            "-0.6483608274590866712591249330098086768168743429837249756336279673958556003746239");
  EXPECT_EQ(tan(Real("1.5")).toString(),
            "14.101419947171719387646083651987756445659543577235861866123267586089696270414155");
  EXPECT_EQ(tan(Real(getPi() / 2)).toString(),
            "1.8284132705300082902317661058105479684239284072480833124982117000101510968883506*10^120");
  EXPECT_EQ(tan(pow(Real(11), -100)).toString(),
            "7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(tan(-pow(Real(11), -100)).toString(),
            "-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");

  EXPECT_THROW(tan(pow(Real(11), 100)), UndefinedFunctionException);
  EXPECT_THROW(tan(-pow(Real(11), 100)), UndefinedFunctionException);
}

TEST(RealFunctionsTests, cotTest) {
  EXPECT_EQ(cot(Real("1")).toString(),
            "0.64209261593433070300641998659426562023027811391817137910116228042627685683916467");
  EXPECT_EQ(cot(Real("200")).toString(),
            "-0.55787150213477006971046091195634798429557648836442892718891989460860978240822024");
  EXPECT_EQ(cot(Real("0.001")).toString(),
            "999.9996666666444444423280421164020950243150821349686957930420507767438195464464");
  EXPECT_EQ(cot(pow(Real(11), -100)).toString(),
            "1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104");
  EXPECT_EQ(cot(-pow(Real(11), -100)).toString(),
            "-1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104");

  EXPECT_THROW(cot(Real("0")), UndefinedFunctionException);
  EXPECT_THROW(cot(pow(Real(11), 100)), UndefinedFunctionException);
  EXPECT_THROW(cot(-pow(Real(11), 100)), UndefinedFunctionException);
}

TEST(RealFunctionsTests, secTest) {
  EXPECT_EQ(sec(Real("0")).toString(), "1.0");
  EXPECT_EQ(sec(Real("1")).toString(),
            "1.8508157176809256179117532413986501934703966550940092988351582778588154112615967");
  EXPECT_EQ(sec(Real("1.6")).toString(),
            "-34.247135610018689205295461483291306219436082882081545055042205706353264742234617");
  EXPECT_EQ(sec(Real("125")).toString(),
            "1.2694954638805676703376706923632363680417203139865889801435769773818587224340106");
  EXPECT_EQ(sec(pow(Real(11), -100)).toString(),
            "1.0");
  EXPECT_EQ(sec(-pow(Real(11), -100)).toString(),
            "1.0");

  EXPECT_THROW(sec(pow(Real(11), 100)), UndefinedFunctionException);
  EXPECT_THROW(sec(-pow(Real(11), 100)), UndefinedFunctionException);
}

TEST(RealFunctionsTests, cscTest) {
  EXPECT_EQ(csc(Real("1")).toString(),
            "1.1883951057781212162615994523745510035278298340979626252652536663591843673571905");
  EXPECT_EQ(csc(Real("-1")).toString(),
            "-1.1883951057781212162615994523745510035278298340979626252652536663591843673571905");
  EXPECT_EQ(csc(Real("3.2")).toString(),
            "-17.130872356878680929063816308707772644748981698069414677586948372772984323565408");
  EXPECT_EQ(csc(Real("360")).toString(),
            "1.0428445123825993746264366840754767090833603173462451344005105419339646525772189");
  EXPECT_EQ(csc(pow(Real(11), -100)).toString(),
            "1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104");
  EXPECT_EQ(csc(-pow(Real(11), -100)).toString(),
            "-1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104");

  EXPECT_THROW(csc(Real("0")), UndefinedFunctionException);
  EXPECT_THROW(csc(pow(Real(11), 100)), UndefinedFunctionException);
  EXPECT_THROW(csc(-pow(Real(11), 100)), UndefinedFunctionException);
}

TEST(RealFunctionsTests, asinTest) {
  EXPECT_EQ(asin(Real("0")).toString(), "0.0");
  EXPECT_EQ(asin(Real("-0.84")).toString(),
            "-0.99728322237179986604941509532521395934714998516818417157450478882243040040739065");
  EXPECT_EQ(asin(-1 + pow(Real(11), -100)).toString(),
            "-1.5707963267948966192313216916397514420985846996875527900169647837490308108646706");
  EXPECT_EQ(asin(1 - pow(Real(11), -100)).toString(),
            "1.5707963267948966192313216916397514420985846996875527900169647837490308108646706");
  EXPECT_EQ(asin(pow(Real(11), -100)).toString(),
            "7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(asin(-pow(Real(11), -100)).toString(),
            "-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");

  EXPECT_THROW(asin(Real("10")), UndefinedFunctionException);
  EXPECT_THROW(asin(Real("-10")), UndefinedFunctionException);
  EXPECT_THROW(asin(-1 - pow(Real(11), -100)).toString(), UndefinedFunctionException);
  EXPECT_THROW(asin(1 + pow(Real(11), -100)).toString(), UndefinedFunctionException);
  EXPECT_THROW(asin(pow(Real(11), 100)), UndefinedFunctionException);
  EXPECT_THROW(asin(-pow(Real(11), 100)), UndefinedFunctionException);
}

TEST(RealFunctionsTests, acosTest) {
  EXPECT_EQ(acos(Real("0")).toString(),
            "1.5707963267948966192313216916397514420985846996875529104874722961539082031431045");
  EXPECT_EQ(acos(Real("0.54")).toString(),
            "1.0003592173949747118791376298435469512885913377969497906049204887187423921567895");
  EXPECT_EQ(acos(Real("-1")).toString(),
            "3.141592653589793238462643383279502884197169399375105820974944592307816406286209");
  EXPECT_EQ(acos(-1 + pow(Real(11), -100)).toString(),
            "3.1415926535897932384626433832795028841971693993751057005044370799029390140077751");
  EXPECT_EQ(acos(1 - pow(Real(11), -100)).toString(),
            "1.2047050751240487739227843386018166895553773908567102047465696750792188150593125*10^-52");
  EXPECT_EQ(acos(pow(Real(11), -100)).toString(),
            "1.5707963267948966192313216916397514420985846996875529104874722961539082031431045");
  EXPECT_EQ(acos(-pow(Real(11), -100)).toString(),
            "1.5707963267948966192313216916397514420985846996875529104874722961539082031431045");

  EXPECT_THROW(acos(Real("10")), UndefinedFunctionException);
  EXPECT_THROW(acos(Real("-10")), UndefinedFunctionException);
  EXPECT_THROW(acos(-1 - pow(Real(11), -100)).toString(), UndefinedFunctionException);
  EXPECT_THROW(acos(1 + pow(Real(11), -100)).toString(), UndefinedFunctionException);
  EXPECT_THROW(acos(pow(Real(11), 100)), UndefinedFunctionException);
  EXPECT_THROW(acos(-pow(Real(11), 100)), UndefinedFunctionException);
}

TEST(RealFunctionsTests, atanTest) {
  EXPECT_EQ(atan(Real("0")).toString(), "0.0");
  EXPECT_EQ(atan(Real("14.101419947171719387646083651987756445659543577235861866123267586089696270414155")).toString(),
            "1.5");
  EXPECT_EQ(atan(pow(Real(11), -100)).toString(),
            "7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(atan(-pow(Real(11), -100)).toString(),
            "-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(atan(pow(Real(11), 100)).toString(),
            "1.5707963267948966192313216916397514420985846996875529104874722961539082031431045");
  EXPECT_EQ(atan(-pow(Real(11), 100)).toString(),
            "-1.5707963267948966192313216916397514420985846996875529104874722961539082031431045");
}

TEST(RealFunctionsTests, acotTest) {
  EXPECT_EQ(acot(Real("1")).toString(),
            "0.78539816339744830961566084581987572104929234984377645524373614807695410157155225");
  EXPECT_EQ(acot(Real("999.9996666666444444423280421164020950243150821349686957930420507767438195464464")).toString(),
            "0.001");
  EXPECT_EQ(acot(pow(Real(11), -100)).toString(),
            "1.5707963267948966192313216916397514420985846996875529104874722961539082031431045");
  EXPECT_EQ(acot(-pow(Real(11), -100)).toString(),
            "-1.5707963267948966192313216916397514420985846996875529104874722961539082031431045");
  EXPECT_EQ(acot(pow(Real(11), 100)).toString(),
            "7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(acot(-pow(Real(11), 100)).toString(),
            "-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");

  EXPECT_THROW(acot(Real("0")), UndefinedFunctionException);
}

TEST(RealFunctionsTests, asecTest) {
  EXPECT_EQ(asec(Real("-1")).toString(),
            "3.141592653589793238462643383279502884197169399375105820974944592307816406286209");
  EXPECT_EQ(asec(Real("10")).toString(),
            "1.4706289056333368228857985121870581235299087274579233690964484411175055294922419");
  EXPECT_EQ(asec(Real("-10")).toString(),
            "1.6709637479564564155768448710924447606672606719171824518784961511903108767939671");
  EXPECT_EQ(asec(-1 - pow(Real(11), -100)).toString(),
            "3.1415926535897932384626433832795028841971693993751057005044370799029473147945872");
  EXPECT_EQ(asec(1 + pow(Real(11), -100)).toString(),
            "1.2047050751240486909149162180969045816186910730220273684418427142357810517189649*10^-52");
  EXPECT_EQ(asec(pow(Real(11), 100)).toString(),
            "1.5707963267948966192313216916397514420985846996875529104874722961539082031431045");
  EXPECT_EQ(asec(-pow(Real(11), 100)).toString(),
            "1.5707963267948966192313216916397514420985846996875529104874722961539082031431045");

  EXPECT_THROW(asec(Real("0")).toString(), UndefinedFunctionException);
  EXPECT_THROW(asec(Real("0.54")).toString(), UndefinedFunctionException);
  EXPECT_THROW(asec(-1 + pow(Real(11), -100)).toString(), UndefinedFunctionException);
  EXPECT_THROW(asec(1 - pow(Real(11), -100)).toString(), UndefinedFunctionException);
  EXPECT_THROW(asec(pow(Real(11), -100)).toString(), UndefinedFunctionException);
  EXPECT_THROW(asec(-pow(Real(11), -100)).toString(), UndefinedFunctionException);
}

TEST(RealFunctionsTests, acscTest) {
  EXPECT_EQ(acsc(Real("2")).toString(),
            "0.52359877559829887307710723054658381403286156656251763682915743205130273438103483");
  EXPECT_EQ(acsc(Real("10")).toString(),
            "0.10016742116155979634552317945269331856867597222962954139102385503640267365086255");
  EXPECT_EQ(acsc(Real("-10")).toString(),
            "-0.10016742116155979634552317945269331856867597222962954139102385503640267365086255");
  EXPECT_EQ(acsc(-1 - pow(Real(11), -100)).toString(),
            "-1.5707963267948966192313216916397514420985846996875527900169647837490391116514827");
  EXPECT_EQ(acsc(1 + pow(Real(11), -100)).toString(),
            "1.5707963267948966192313216916397514420985846996875527900169647837490391116514827");
  EXPECT_EQ(acsc(pow(Real(11), 100)).toString(),
            "7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(acsc(-pow(Real(11), 100)).toString(),
            "-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");

  EXPECT_THROW(acsc(Real("0")), UndefinedFunctionException);
  EXPECT_THROW(acsc(Real("0.54")).toString(), UndefinedFunctionException);
  EXPECT_THROW(acsc(-1 + pow(Real(11), -100)).toString(), UndefinedFunctionException);
  EXPECT_THROW(acsc(1 - pow(Real(11), -100)).toString(), UndefinedFunctionException);
  EXPECT_THROW(acsc(pow(Real(11), -100)).toString(), UndefinedFunctionException);
  EXPECT_THROW(acsc(-pow(Real(11), -100)).toString(), UndefinedFunctionException);
}

TEST(RealFunctionsTests, sinhTest) {
  EXPECT_EQ(sinh(Real("0")).toString(), "0.0");
  EXPECT_EQ(sinh(Real("-1")).toString(),
            "-1.1752011936438014568823818505956008151557179813340958702295654130133075673043239");
  EXPECT_EQ(sinh(Real("360")).toString(),
            "1.1091326487692776999948329517793349595727082777083535707260458682053441771196906*10^156");
  EXPECT_EQ(sinh(pow(Real(11), -100)).toString(),
            "7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(sinh(-pow(Real(11), -100)).toString(),
            "-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");

  EXPECT_THROW(sinh(pow(Real(11), 100)), UndefinedFunctionException);
  EXPECT_THROW(sinh(-pow(Real(11), 100)), UndefinedFunctionException);
}

TEST(RealFunctionsTests, coshTest) {
  EXPECT_EQ(cosh(Real("0")).toString(), "1.0");
  EXPECT_EQ(cosh(Real("1")).toString(),
            "1.5430806348152437784779056207570616826015291123658637047374022147107690630492237");
  EXPECT_EQ(cosh(Real("125")).toString(),
            "967788021017861284360312245263743609428141503861911628.64033144120749560890919683");
  EXPECT_EQ(cosh(pow(Real(11), -100)).toString(),
            "1.0");
  EXPECT_EQ(cosh(-pow(Real(11), -100)).toString(),
            "1.0");

  EXPECT_THROW(cosh(pow(Real(11), 100)), UndefinedFunctionException);
  EXPECT_THROW(cosh(-pow(Real(11), 100)), UndefinedFunctionException);
}

TEST(RealFunctionsTests, tanhTest) {
  EXPECT_EQ(tanh(Real("0")).toString(), "0.0");
  EXPECT_EQ(tanh(Real("-10")).toString(),
            "-0.99999999587769276361959283713827574105081461849501996226140069543680188089876683");
  EXPECT_EQ(tanh(Real("1.5")).toString(),
            "0.90514825364486643824230369645649559722764113515878179856422398245110257699457953");
  EXPECT_EQ(tanh(pow(Real(11), -100)).toString(),
            "7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(tanh(-pow(Real(11), -100)).toString(),
            "-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(tanh(pow(Real(11), 100)).toString(),
            "1.0");
  EXPECT_EQ(tanh(-pow(Real(11), 100)).toString(),
            "-1.0");
}

TEST(RealFunctionsTests, cothTest) {
  EXPECT_EQ(coth(Real("1")).toString(),
            "1.3130352854993313036361612469308478329120139412404526555431529675670842704618744");
  EXPECT_EQ(coth(Real("200")).toString(), "1.0");
  EXPECT_EQ(coth(Real("0.001")).toString(),
            "1000.0003333333111111132275130158730372508128641887448236432439795543114729807153");
  EXPECT_EQ(coth(pow(Real(11), -100)).toString(),
            "1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104");
  EXPECT_EQ(coth(-pow(Real(11), -100)).toString(),
            "-1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104");
  EXPECT_EQ(coth(pow(Real(11), 100)).toString(),
            "1.0");
  EXPECT_EQ(coth(-pow(Real(11), 100)).toString(),
            "-1.0");

  EXPECT_THROW(coth(Real("0")), UndefinedFunctionException);
}

TEST(RealFunctionsTests, sechTest) {
  EXPECT_EQ(sech(Real("0")).toString(), "1.0");
  EXPECT_EQ(sech(Real("-1")).toString(),
            "0.64805427366388539957497735322615032310848931207194202303786533731871759564671283");
  EXPECT_EQ(sech(Real("360")).toString(),
            "9.0160541312134836868594093056048781135886063264031045543166320171424640100585883*10^-157");
  EXPECT_EQ(sech(pow(Real(11), -100)).toString(),
            "1.0");
  EXPECT_EQ(sech(-pow(Real(11), -100)).toString(),
            "1.0");

  EXPECT_THROW(sech(pow(Real(11), 100)), UndefinedFunctionException);
  EXPECT_THROW(sech(-pow(Real(11), 100)), UndefinedFunctionException);
}

TEST(RealFunctionsTests, cschTest) {
  EXPECT_EQ(csch(Real("-1")).toString(),
            "-0.8509181282393215451338427632871752841817246609103396169904211517290033643214651");
  EXPECT_EQ(csch(Real("1")).toString(),
            "0.8509181282393215451338427632871752841817246609103396169904211517290033643214651");
  EXPECT_EQ(csch(Real("125")).toString(),
            "1.0332841265675721960505437214715115728551601889626861910405726604708228332416093*10^-54");
  EXPECT_EQ(csch(pow(Real(11), -100)).toString(),
            "1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104");
  EXPECT_EQ(csch(-pow(Real(11), -100)).toString(),
            "-1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104");

  EXPECT_THROW(csch(Real("0")).toString(), UndefinedFunctionException);
  EXPECT_THROW(csch(pow(Real(11), 100)), UndefinedFunctionException);
  EXPECT_THROW(csch(-pow(Real(11), 100)), UndefinedFunctionException);
}

TEST(RealFunctionsTests, asinhTest) {
  EXPECT_EQ(asinh(Real("0")).toString(), "0.0");
  EXPECT_EQ(asinh(Real("10")).toString(),
            "2.9982229502979697388465955375964534766070580548773036557344592627530896573521661");
  EXPECT_EQ(asinh(Real("-10")).toString(),
            "-2.9982229502979697388465955375964534766070580548773036557344592627530896573521661");
  EXPECT_EQ(asinh(pow(Real(11), -100)).toString(),
            "7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(asinh(-pow(Real(11), -100)).toString(),
            "-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(asinh(pow(Real(11), 100)).toString(),
            "240.48267446039699971561158991797110655024618552810197277597745092255075601329337");
  EXPECT_EQ(asinh(-pow(Real(11), 100)).toString(),
            "-240.48267446039699971561158991797110655024618552810197277597745092255075601329337");
}

TEST(RealFunctionsTests, acoshTest) {
  EXPECT_EQ(acosh(Real("1")).toString(), "0.0");
  EXPECT_EQ(acosh(Real("10")).toString(),
            "2.9932228461263808979126677137741829130836604511809806426851456009774992267097399");
  EXPECT_EQ(acosh(1 + pow(Real(11), -100)).toString(),
            "1.2047050751240487739227843386018166895553773908567102047465696750792188150593125*10^-52");
  EXPECT_EQ(acosh(pow(Real(11), 100)).toString(),
            "240.48267446039699971561158991797110655024618552810197277597745092255075601329337");

  EXPECT_THROW(acosh(Real("-1")), UndefinedFunctionException);
  EXPECT_THROW(acosh(Real("0")), UndefinedFunctionException);
  EXPECT_THROW(acosh(-1 + pow(Real(11), -100)), UndefinedFunctionException);
  EXPECT_THROW(acosh(-1 - pow(Real(11), -100)).toString(), UndefinedFunctionException);
  EXPECT_THROW(acosh(1 - pow(Real(11), -100)), UndefinedFunctionException);
  EXPECT_THROW(acosh(-pow(Real(11), 100)), UndefinedFunctionException);
  EXPECT_THROW(acosh(pow(Real(11), -100)), UndefinedFunctionException);
  EXPECT_THROW(acosh(-pow(Real(11), -100)), UndefinedFunctionException);
}

TEST(RealFunctionsTests, atanhTest) {
  EXPECT_EQ(atanh(Real("0")).toString(), "0.0");
  EXPECT_EQ(atanh(Real("0.5")).toString(),
            "0.54930614433405484569762261846126285232374527891137472586734716681874714660930448");
  EXPECT_EQ(atanh(pow(Real(11), -100)).toString(),
            "7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(atanh(-pow(Real(11), -100)).toString(),
            "-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");

  EXPECT_THROW(atanh(Real("-1")), UndefinedFunctionException);
  EXPECT_THROW(atanh(Real("1")), UndefinedFunctionException);
  EXPECT_THROW(atanh(-1 + pow(Real(11), -100)), UndefinedFunctionException);
  EXPECT_THROW(atanh(-1 - pow(Real(11), -100)).toString(), UndefinedFunctionException);
  EXPECT_THROW(atanh(1 + pow(Real(11), -100)).toString(), UndefinedFunctionException);
  EXPECT_THROW(atanh(1 - pow(Real(11), -100)), UndefinedFunctionException);
  EXPECT_THROW(atanh(pow(Real(11), 100)).toString(), UndefinedFunctionException);
  EXPECT_THROW(atanh(-pow(Real(11), 100)).toString(), UndefinedFunctionException);
}

TEST(RealFunctionsTests, acothTest) {
  EXPECT_EQ(acoth(Real("10")).toString(),
            "0.10033534773107558063572655206003894526336286914595913587458952092779251873800939");
  EXPECT_EQ(acoth(Real("-10")).toString(),
            "-0.10033534773107558063572655206003894526336286914595913587458952092779251873800939");
  EXPECT_EQ(acoth(pow(Real(11), 100)).toString(),
            "7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(acoth(-pow(Real(11), 100)).toString(),
            "-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");

  EXPECT_THROW(acoth(Real("-1")), UndefinedFunctionException);
  EXPECT_THROW(acoth(Real("0")), UndefinedFunctionException);
  EXPECT_THROW(acoth(Real("1")), UndefinedFunctionException);
  EXPECT_THROW(acoth(-1 + pow(Real(11), -100)), UndefinedFunctionException);
  EXPECT_THROW(acoth(-1 - pow(Real(11), -100)).toString(), UndefinedFunctionException);
  EXPECT_THROW(acoth(1 + pow(Real(11), -100)).toString(), UndefinedFunctionException);
  EXPECT_THROW(acoth(1 - pow(Real(11), -100)), UndefinedFunctionException);
  EXPECT_THROW(acoth(pow(Real(11), -100)).toString(), UndefinedFunctionException);
  EXPECT_THROW(acoth(-pow(Real(11), -100)).toString(), UndefinedFunctionException);
}

TEST(RealFunctionsTests, asechTest) {
  EXPECT_EQ(asech(Real("1")).toString(), "0.0");
  EXPECT_EQ(asech(Real("0.3")).toString(),
            "1.8738202425274144249769979852084091960595966794746295241858217517040005820158279");
  EXPECT_EQ(asech(Real("0.5")).toString(),
            "1.316957896924816708625046347307968444026981971467516479768472256920460185416444");
  EXPECT_EQ(asech(1 - pow(Real(11), -100)).toString(),
            "1.2047050676410388537815742365190888195060803599521175782305679940978031876598796*10^-52");

  EXPECT_THROW(asech(Real("-1")), UndefinedFunctionException);
  EXPECT_THROW(asech(Real("0")), UndefinedFunctionException);
  EXPECT_THROW(asech(-1 + pow(Real(11), -100)), UndefinedFunctionException);
  EXPECT_THROW(asech(-1 - pow(Real(11), -100)).toString(), UndefinedFunctionException);
  EXPECT_THROW(asech(1 + pow(Real(11), -100)).toString(), UndefinedFunctionException);
}

TEST(RealFunctionsTests, acschTest) {
  EXPECT_EQ(acsch(Real("1")).toString(),
            "0.88137358701954302523260932497979230902816032826163541075329560865337718422202609");
  EXPECT_EQ(acsch(Real("10")).toString(),
            "0.099834078899207563327303124704769443267712911708825010742382695651591768393613465");
  EXPECT_EQ(acsch(Real("-10")).toString(),
            "-0.099834078899207563327303124704769443267712911708825010742382695651591768393613465");
  EXPECT_EQ(acsch(pow(Real(11), -100)).toString(),
            "240.48267446039699971561158991797110655024618552810197277597745092255075601329337");
  EXPECT_EQ(acsch(-pow(Real(11), -100)).toString(),
            "-240.48267446039699971561158991797110655024618552810197277597745092255075601329337");
  EXPECT_EQ(acsch(pow(Real(11), 100)).toString(),
            "7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(acsch(-pow(Real(11), 100)).toString(),
            "-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");

  EXPECT_THROW(acsch(Real("0")), UndefinedFunctionException);
}

TEST(RealFunctionsTests, getETest) {
  EXPECT_EQ(getE().toString(), "2.7182818284590452353602874713526624977572470936999595749669676277240766303535476");
}

TEST(RealFunctionsTests, getEPiTest) {
  EXPECT_EQ(getPi().toString(), "3.141592653589793238462643383279502884197169399375105820974944592307816406286209");
}

TEST(RealFunctionsTests, tgammaTest) {
  EXPECT_EQ(tgamma(Real("1")).toString(), "1.0");
  EXPECT_EQ(tgamma(Real("2")).toString(), "1.0");
  EXPECT_EQ(tgamma(Real("3")).toString(), "2.0");
  EXPECT_EQ(tgamma(Real("4")).toString(), "6.0");
  EXPECT_EQ(tgamma(Real("5")).toString(), "24.0");
  EXPECT_EQ(tgamma(Real("10")).toString(), "362880.0");
  EXPECT_EQ(tgamma(Real("1000000")).toString(),
            "8.2639316883312400623766461031726662911353479789638730451677758855633796110356451*10^5565702");

  EXPECT_EQ(tgamma(Real("0.5")).toString(),
            "1.7724538509055160272981674833411451827975494561223871282138077898529112845910322");
  EXPECT_EQ(tgamma(Real("1.5")).toString(),
            "0.88622692545275801364908374167057259139877472806119356410690389492645564229551609");
  EXPECT_EQ(tgamma(Real("1.23345")).toString(),
            "0.90997105032312305741807535506003700168381988861711231924267338164564458593112273");
  EXPECT_EQ(tgamma(Real("10.888")).toString(),
            "2790176.1744474603546712580801633763601209060179121811338563253860175273379208134");
  EXPECT_EQ(tgamma(Real("-0.5")).toString(),
            "-3.5449077018110320545963349666822903655950989122447742564276155797058225691820644");
  EXPECT_EQ(tgamma(Real("-1.5")).toString(),
            "2.3632718012073547030642233111215269103967326081631828376184103864705483794547096");
  EXPECT_EQ(tgamma(Real("-1.23345")).toString(),
            "4.1813173753338157686838484929306398465161945343856820450249490692138002199035393");
  EXPECT_EQ(tgamma(Real("-10.888")).toString(),
            "-3.0005493180448293721869822512345553711440749496581172835311328514510130843563454*10^-7");

  EXPECT_THROW(tgamma(Real("0")), UndefinedFunctionException);
  EXPECT_THROW(tgamma(Real("-1")), UndefinedFunctionException);
  EXPECT_THROW(tgamma(Real("-2")), UndefinedFunctionException);
  EXPECT_THROW(tgamma(Real("-3")), UndefinedFunctionException);
  EXPECT_THROW(tgamma(Real("-32352")), UndefinedFunctionException);

  EXPECT_THROW(tgamma(Real("1000000000")), UndefinedFunctionException);
  EXPECT_THROW(tgamma(Real("-1000000000")), UndefinedFunctionException);
}
