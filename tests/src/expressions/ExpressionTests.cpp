#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"

#include <fstream>

using namespace fintamath;

TEST(ExpressionTests, constructorTest) {
  EXPECT_EQ(Expression().toString(), "0");
}

TEST(ExpressionTests, moveTest) {
  auto a = Expression("1+2");
  EXPECT_EQ(a.toString(), "3");
  auto b = std::move(a);
  EXPECT_TRUE(b.toString() == "3" && a.toString() == "0");
  a = std::move(b);
  EXPECT_TRUE(a.toString() == "3" && b.toString() == "0");
}

TEST(ExpressionTests, copyTest) {
  auto a = Expression("1+2");
  auto b = a;
  EXPECT_TRUE(a == b && &a != &b);
}

TEST(ExpressionTests, stingConstructorAndToStringTest) {
  EXPECT_EQ(Expression("2").toString(), "2");
  EXPECT_EQ(Expression("2 + 2").toString(), "4");
  EXPECT_EQ(Expression("-2 + 3").toString(), "1");
  EXPECT_EQ(Expression("2 * 2").toString(), "4");
  EXPECT_EQ(Expression("1 / 3").toString(), "1/3");
  EXPECT_EQ(Expression("0 / 3").toString(), "0");
  EXPECT_EQ(Expression("2 ^ 2").toString(), "4");
  EXPECT_EQ(Expression("0^1").toString(), "0");
  EXPECT_EQ(Expression("2^0").toString(), "1");
  EXPECT_EQ(Expression("(-7)^10").toString(), "282475249");
  EXPECT_EQ(Expression("2^0").toString(), "1");
  EXPECT_EQ(Expression("0.001-0.002").toString(), "-1/1000");
  EXPECT_EQ(Expression("(0.004)/(0.002+0.002)").toString(), "1");
  EXPECT_EQ(Expression("2 + 2 * 2").toString(), "6");
  EXPECT_EQ(Expression("2^2^2^2").toString(), "65536");
  EXPECT_EQ(Expression("(2 + 2) * 2").toString(), "8");
  EXPECT_EQ(Expression("(2-2)").toString(), "0");
  EXPECT_EQ(Expression("(2 + 2) / (2 ^ 2 - 2) * 2").toString(), "4");
  EXPECT_EQ(Expression("((((2))))").toString(), "2");
  EXPECT_EQ(Expression("(((((2 + 2) + 2) + 2) + 2) + 2)").toString(), "12");
  EXPECT_EQ(Expression("(((2 ^ 2)^2))").toString(), "16");
  EXPECT_EQ(Expression("-5").toString(), "-5");
  EXPECT_EQ(Expression("--5").toString(), "5");
  EXPECT_EQ(Expression("---5").toString(), "-5");
  EXPECT_EQ(Expression("+5").toString(), "5");
  EXPECT_EQ(Expression("5*-3").toString(), "-15");
  EXPECT_EQ(Expression("5!").toString(), "120");
  EXPECT_EQ(Expression("-1!").toString(), "-1");
  EXPECT_EQ(Expression("-100!").toString(),
            "-933262154439441526816992388562667004907159682643816214685929638952175999932299156089414639761565182862536"
            "97920827223758251185210916864000000000000000000000000");
  EXPECT_EQ(Expression("5!!").toString(),
            "6689502913449127057588118054090372586752746333138029810295671352301633557244962989366874165271984981308157"
            "637893214090552534408589408121859898481114389650005964960521256960000000000000000000000000000");
  EXPECT_EQ(Expression("(2)!").toString(), "2");
  EXPECT_EQ(Expression("sqrt144").toString(), "12");
  EXPECT_EQ(Expression("sqrt0").toString(), "0");
  EXPECT_EQ(Expression("e^101-e^101").toString(), "0");
  EXPECT_EQ(Expression("ln(e^e) / ln(e^e) - 1").toString(), "0");
  EXPECT_EQ(Expression("sqrt4!").toString(), "2");
  EXPECT_EQ(Expression("(sqrt4)!").toString(), "2");
  EXPECT_EQ(Expression("sqrt4*2!").toString(), "4");
  EXPECT_EQ(Expression("abs(-5)").toString(), "5");
  EXPECT_EQ(Expression("abs((-5))").toString(), "5");
  EXPECT_EQ(Expression("log(2, 256)").toString(), "8");
  EXPECT_EQ(Expression("1/10^-100").toString(),
            "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
  EXPECT_EQ(Expression("1/10^---100").toString(),
            "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
  EXPECT_EQ(
      Expression("10^-1000").toString(),
      "1/"
      "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
      "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
      "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
      "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
      "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
      "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
      "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
      "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
      "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
  EXPECT_EQ(Expression("e").toString(), "e");
  EXPECT_EQ(Expression("pi").toString(), "pi");
  EXPECT_EQ(Expression("exp100").toString(), "exp(100)");
  EXPECT_EQ(Expression("e^101").toString(), "e^101");
  EXPECT_EQ(Expression("e^(-101)").toString(), "e^-101");
  EXPECT_EQ(Expression("log(e,e)").toString(), "log(e,e)");
  EXPECT_EQ(Expression("log(pi, pi^10)").toString(), "log(pi,pi^10)");
  EXPECT_EQ(Expression("log(e,e^3)").toString(), "log(e,e^3)");
  EXPECT_EQ(Expression("ln3").toString(), "ln(3)");
  EXPECT_EQ(Expression("ln2").toString(), "ln(2)");
  EXPECT_EQ(Expression("ln100").toString(), "ln(100)");
  EXPECT_EQ(Expression("ln(e)").toString(), "ln(e)");
  EXPECT_EQ(Expression("lg99").toString(), "lg(99)");
  EXPECT_EQ(Expression("lg100").toString(), "2");
  EXPECT_EQ(Expression("lb100").toString(), "lb(100)");
  EXPECT_EQ(Expression("lb4").toString(), "2");
  EXPECT_EQ(Expression("sin10").toString(), "sin(10)");
  EXPECT_EQ(Expression("cos10").toString(), "cos(10)");
  EXPECT_EQ(Expression("tan10").toString(), "tan(10)");
  EXPECT_EQ(Expression("cot10").toString(), "cot(10)");
  EXPECT_EQ(Expression("asin0.9").toString(), "asin(9/10)");
  EXPECT_EQ(Expression("acos0.9").toString(), "acos(9/10)");
  EXPECT_EQ(Expression("atan10").toString(), "atan(10)");
  EXPECT_EQ(Expression("acot10").toString(), "acot(10)");
  EXPECT_EQ(Expression("((2))*sqrt2").toString(), "2*sqrt(2)");
  EXPECT_EQ(Expression("sqrt2*((2))").toString(), "2*sqrt(2)");
  EXPECT_EQ(Expression("sin(1)^2").toString(), "sin(1)^2");
  EXPECT_EQ(Expression("sin(-1)^2").toString(), "sin(-1)^2");
  EXPECT_EQ(Expression("sin1^2").toString(), "sin(1)^2");
  EXPECT_EQ(Expression("sin(10^30)").toString(), "sin(1000000000000000000000000000000)");
  EXPECT_EQ(Expression("sin(1)^2+cos(1)^2").toString(), "cos(1)^2+sin(1)^2");
  EXPECT_EQ(Expression("sin(pi/3)").toString(), "sin(1/3*pi)");
  EXPECT_EQ(Expression("cos(pi/3)").toString(), "cos(1/3*pi)");
  EXPECT_EQ(Expression("2!*e").toString(), "2*e");
  EXPECT_EQ(Expression("e*2!").toString(), "2*e");
  EXPECT_EQ(Expression("sqrt((1-cos(2*(pi/3)))/2)").toString(), "sqrt(-1/2*cos(2/3*pi)+1/2)");
  EXPECT_EQ(Expression("2*sqrt((1-cos(2*(pi/3)))/2)*cos(pi/3)").toString(), "2*cos(1/3*pi)*sqrt(-1/2*cos(2/3*pi)+1/2)");
  EXPECT_EQ(Expression("ln(ln(ln(ln(e))))").toString(), "ln(ln(ln(ln(e))))");
  EXPECT_EQ(Expression("ln(ln(ln(ln(ln(e)))))").toString(), "ln(ln(ln(ln(ln(e)))))");
  EXPECT_EQ(Expression("-sin(x)").toString(), "-sin(x)");
  EXPECT_EQ(Expression("-sin(2)").toString(), "-sin(2)");
  EXPECT_EQ(Expression("-(-(-(-(-(-(-(-a)))))))").toString(), "a");
  EXPECT_EQ(Expression("a+a").toString(), "2*a");
  EXPECT_EQ(Expression("a-a").toString(), "0");
  EXPECT_EQ(Expression("(a+b)-b").toString(), "a");
  EXPECT_EQ(Expression("(a+b)*(a+b)+a*b*c-c*a*b+b*a").toString(), "a^2+b^2+3*a*b");
  EXPECT_EQ(Expression("+a").toString(), "a");
  EXPECT_EQ(Expression("(a+b)^2").toString(), "a^2+b^2+2*a*b");
  EXPECT_EQ(Expression("(a+b)^3").toString(), "a^3+b^3+3*a^2*b+3*b^2*a");
  EXPECT_EQ(Expression("1*(a+b)^3").toString(), "a^3+b^3+3*a^2*b+3*b^2*a");
  EXPECT_EQ(Expression("(a+b)^4").toString(), "a^4+b^4+4*a^3*b+4*b^3*a+6*a^2*b^2");
  EXPECT_EQ(Expression("(a+3)/(b+2)").toString(), "(a+3)/(b+2)");
  EXPECT_EQ(Expression("b/a*(a+3)/(b+2)").toString(), "(3*b+a*b)/(2*a+a*b)");
  EXPECT_EQ(Expression("(5+b)/a*(a+3)/(b+2)").toString(), "(3*b+5*a+a*b+15)/(2*a+a*b)");
  EXPECT_EQ(Expression("(a+b)*(a+b)/(a+b)").toString(), "a+b");
  EXPECT_EQ(Expression("lne").toString(), "ln(e)");
  EXPECT_EQ(Expression("lncossine").toString(), "ln(cos(sin(e)))");
  EXPECT_EQ(Expression("ln cos sin a").toString(), "n^2*s^2*a*c*i*l*o"); // TODO: ln(cos(sin(a)))
  EXPECT_EQ(Expression("a=a").toString(), "true");
  EXPECT_EQ(Expression("a+a=2*a").toString(), "true");
  EXPECT_EQ(Expression("a=b").toString(), "a-b=0");
  EXPECT_EQ(Expression("a!=a").toString(), "false");
  EXPECT_EQ(Expression("a+a!=2*a").toString(), "false");
  EXPECT_EQ(Expression("a!=b").toString(), "a-b!=0");
  EXPECT_EQ(Expression("x<6").toString(), "x-6<0");
  EXPECT_EQ(Expression("x<=6").toString(), "x-6<=0");
  EXPECT_EQ(Expression("x>6").toString(), "x-6>0");
  EXPECT_EQ(Expression("x>=6").toString(), "x-6>=0");
  EXPECT_EQ(Expression("(5+5)=(2*5)").toString(), "true");
  EXPECT_EQ(Expression("((((5+5)=(2*5))))").toString(), "true");
  EXPECT_EQ(Expression("((1*1))(5+5)=((2*5)/(1/1))").toString(), "true");
  EXPECT_EQ(Expression("1-(sin(x)+1)").toString(), "-sin(x)");
  EXPECT_EQ(Expression("1/(sin(x)+1)").toString(), "1/(sin(x)+1)");
  EXPECT_EQ(Expression("(x+1)^3").toString(), "x^3+3*x+3*x^2+1");
  EXPECT_EQ(Expression("(x+1)^(-3)").toString(), "1/(x^3+3*x+3*x^2+1)");
  EXPECT_EQ(Expression("(sin(x)+1)^3").toString(), "sin(x)^3+3*sin(x)+3*sin(x)^2+1");
  EXPECT_EQ(Expression("(sin(x)+1)^(-3)").toString(), "1/(sin(x)^3+3*sin(x)+3*sin(x)^2+1)");
  EXPECT_EQ(Expression("1^-1").toString(), "1");
  EXPECT_EQ(Expression("1.").toString(), "1");
  EXPECT_EQ(Expression(".1").toString(), "1/10");
  EXPECT_EQ(Expression("2+.1+.1+1.+1.").toString(), "21/5");
  EXPECT_EQ(Expression("2.a").toString(), "2*a");
  EXPECT_EQ(Expression("a'").toString(), "1");
  EXPECT_EQ(Expression("(a+a)'").toString(), "(2*a)'");
  EXPECT_EQ(Expression("b'+a'").toString(), "2");
  EXPECT_EQ(Expression("5'").toString(), "0");
  EXPECT_EQ(Expression("!true").toString(), "false");
  EXPECT_EQ(Expression("!false").toString(), "true");
  EXPECT_EQ(Expression("true&&false").toString(), "false");
  EXPECT_EQ(Expression("!!!true&&!!!!false||!!!!!!false||false").toString(), "false");
  EXPECT_EQ(Expression("true||false").toString(), "true");
  EXPECT_EQ(Expression("true&&false||true&&false").toString(), "false");
  EXPECT_EQ(Expression("false&&true||true&&false").toString(), "false");
  EXPECT_EQ(Expression("false&&true||true&&true||false").toString(), "true");
  EXPECT_EQ(Expression("false||!false&&true").toString(), "true");
  EXPECT_EQ(Expression("(false||false&&!true)||(true&&!(false||true))").toString(), "false");
  EXPECT_EQ(Expression("!(1=1)").toString(), "false");
  EXPECT_EQ(Expression("!(1=2)").toString(), "true");
  EXPECT_EQ(Expression("(1=1)&&(1=2)").toString(), "false");
  EXPECT_EQ(Expression("(1=1)||(1=2)").toString(), "true");
  EXPECT_EQ(Expression("(1=2)||!(1=2)&&(1=1)").toString(), "true");
  EXPECT_EQ(Expression("((1=2)||(1=2)&&!(1=1))||((1=1)&&!((1=2)||(1=1)))").toString(), "false");
  EXPECT_EQ(Expression("----5+++5").toString(), "10");
  EXPECT_EQ(Expression("5----4").toString(), "9");
  EXPECT_EQ(Expression("5+-+-4").toString(), "9");
  EXPECT_EQ(Expression("5*+++---4").toString(), "-20");
  EXPECT_EQ(Expression("!!!!!!!!!!a").toString(), "!!!!!!!!!!a");
  EXPECT_EQ(Expression("a!!!!!!!!!!").toString(), "a!!!!!!!!!!");
}

TEST(ExpressionTests, stringConstructorNegativeTest) {
  EXPECT_THROW(Expression(""), InvalidInputException);
  EXPECT_THROW(Expression("1+"), InvalidInputException);
  EXPECT_THROW(Expression("1-"), InvalidInputException);
  EXPECT_THROW(Expression("1*"), InvalidInputException);
  EXPECT_THROW(Expression("1/"), InvalidInputException);
  EXPECT_THROW(Expression(" +   "), InvalidInputException);
  EXPECT_THROW(Expression("(1+2))"), InvalidInputException);
  EXPECT_THROW(Expression("5-*3"), InvalidInputException);
  EXPECT_THROW(Expression("((()()))"), InvalidInputException);
  EXPECT_THROW(Expression("2.2.2"), InvalidInputException);
  EXPECT_THROW(Expression("--"), InvalidInputException);
  EXPECT_THROW(Expression("."), InvalidInputException);
  EXPECT_THROW(Expression(","), InvalidInputException);
  EXPECT_THROW(Expression("/"), InvalidInputException);
  EXPECT_THROW(Expression(";"), InvalidInputException);
  EXPECT_THROW(Expression("\'"), InvalidInputException);
  EXPECT_THROW(Expression("["), InvalidInputException);
  EXPECT_THROW(Expression("]"), InvalidInputException);
  EXPECT_THROW(Expression("!"), InvalidInputException);
  EXPECT_THROW(Expression("@"), InvalidInputException);
  EXPECT_THROW(Expression("\""), InvalidInputException);
  EXPECT_THROW(Expression("#"), InvalidInputException);
  EXPECT_THROW(Expression("№"), InvalidInputException);
  EXPECT_THROW(Expression("%"), InvalidInputException);
  EXPECT_THROW(Expression(":"), InvalidInputException);
  EXPECT_THROW(Expression("?"), InvalidInputException);
  EXPECT_THROW(Expression("*"), InvalidInputException);
  EXPECT_THROW(Expression("("), InvalidInputException);
  EXPECT_THROW(Expression(")"), InvalidInputException);
  EXPECT_THROW(Expression("-"), InvalidInputException);
  EXPECT_THROW(Expression("+"), InvalidInputException);
  EXPECT_THROW(Expression("$"), InvalidInputException);
  EXPECT_THROW(Expression("^"), InvalidInputException);
  EXPECT_THROW(Expression("&"), InvalidInputException);
  EXPECT_THROW(Expression("_"), InvalidInputException);
  EXPECT_THROW(Expression("[1+1]"), InvalidInputException);
  EXPECT_THROW(Expression("{1}"), InvalidInputException);
  EXPECT_THROW(Expression("(1"), InvalidInputException);
  EXPECT_THROW(Expression("(((2)"), InvalidInputException);
  EXPECT_THROW(Expression("(((2))"), InvalidInputException);
  EXPECT_THROW(Expression("((2)))"), InvalidInputException);
  EXPECT_THROW(Expression("(2)))"), InvalidInputException);
  EXPECT_THROW(Expression("(2"), InvalidInputException);
  EXPECT_THROW(Expression("((2)"), InvalidInputException);
  EXPECT_THROW(Expression("((2"), InvalidInputException);
  EXPECT_THROW(Expression("(()())"), InvalidInputException);
  EXPECT_THROW(Expression("((((()))))"), InvalidInputException);
  EXPECT_THROW(Expression("((((2)((2))))"), InvalidInputException);
  EXPECT_THROW(Expression("!2"), InvalidInputException);
  EXPECT_THROW(Expression("!!2"), InvalidInputException);
  EXPECT_THROW(Expression("!2!!"), InvalidInputException);
  EXPECT_THROW(Expression("!(2"), InvalidInputException);
  EXPECT_THROW(Expression("!(2)"), InvalidInputException);
  EXPECT_THROW(Expression("2)!"), InvalidInputException);
  EXPECT_THROW(Expression("sin(2))!"), InvalidInputException);
  EXPECT_THROW(Expression("esin()"), InvalidInputException);
  EXPECT_THROW(Expression("(a+b)*()"), InvalidInputException);
  EXPECT_THROW(Expression("sin(2,3)"), InvalidInputException);
  EXPECT_THROW(Expression("sin()"), InvalidInputException);
  EXPECT_THROW(Expression("log(1)"), InvalidInputException);
  EXPECT_THROW(Expression("log()"), InvalidInputException);
  EXPECT_THROW(Expression("(1 = 1) / 2"), InvalidInputException);
  EXPECT_THROW(Expression("2 + (1 = 2)"), InvalidInputException);
  EXPECT_THROW(Expression("sin(1 = 1)"), InvalidInputException);
  EXPECT_THROW(Expression("true/true"), InvalidInputException);
  EXPECT_THROW(Expression("((1 == 1)) + ((1 == 2))"), InvalidInputException);
  EXPECT_THROW(Expression("((1 == 1)) - ((1 == 1))"), InvalidInputException);
  EXPECT_THROW(Expression("((1 == 1)) / ((1 == 1))"), InvalidInputException);
  EXPECT_THROW(Expression("(5+5)=(2=5)"), InvalidInputException);
  EXPECT_THROW(Expression("1+(sin(x)<2)"), InvalidInputException);
  EXPECT_THROW(Expression("1/(sin(x)<2)"), InvalidInputException);

  EXPECT_THROW(Expression("1/0"), UndefinedException);
  EXPECT_THROW(Expression("0^0"), UndefinedException);
  EXPECT_THROW(Expression("(-1)!"), UndefinedException);
  EXPECT_THROW(Expression("(2/3)!"), UndefinedException);
  EXPECT_THROW(Expression("(-1)!!"), UndefinedException);
  EXPECT_THROW(Expression("(2/3)!!"), UndefinedException);
  EXPECT_THROW(Expression("sqrt(-1)"), UndefinedException);
  EXPECT_THROW(Expression("ln(0)"), UndefinedException);
  EXPECT_THROW(Expression("ln(-1)"), UndefinedException);
  EXPECT_THROW(Expression("log(-1, 1)"), UndefinedException);
  EXPECT_THROW(Expression("log(0, 1)"), UndefinedException);
  EXPECT_THROW(Expression("log(1, 0)"), UndefinedException);
  EXPECT_THROW(Expression("lb(-1)"), UndefinedException);
  EXPECT_THROW(Expression("lg(-1)"), UndefinedException);
  EXPECT_THROW(Expression("(-1)^(2/3)"), UndefinedException);
  // TODO constants
  // EXPECT_THROW(Expression("e!"), UndefinedException);
  // EXPECT_THROW(Expression("tan(pi/2)"), UndefinedException);
  // EXPECT_THROW(Expression("cot(0)"), UndefinedException);
  // EXPECT_THROW(Expression("asin(2)"), UndefinedException);
  // EXPECT_THROW(Expression("acos(2)"), UndefinedException);
  // EXPECT_THROW(Expression("tan(3/2*pi)"), UndefinedException);
  // EXPECT_THROW(Expression("cot(2*pi)"), UndefinedException);
}

TEST(ExpressionTests, simplifyInpreciseTest) {
  EXPECT_EQ(Expression("150!").simplify(false)->toString(),
            "5713383956445854590478932865261054003189553578601126418254837583317982912484539839312657448867531114537710"
            "7878746854204162666250198684504466355949195922066574942592095735778929325357290444962472405416790722118445"
            "437122269675520000000000000000000000000000000000000");
  EXPECT_EQ(Expression("e").simplify(false)->toString(),
            "2.7182818284590452353602874713526624977572470936999595749669676277240766303535476");
  EXPECT_EQ(Expression("pi").simplify(false)->toString(),
            "3.141592653589793238462643383279502884197169399375105820974944592307816406286209");
  EXPECT_EQ(Expression("exp100").simplify(false)->toString(),
            "26881171418161354484126255515800135873611118.773741922415191608615280287034909565");
  EXPECT_EQ(Expression("e^101").simplify(false)->toString(),
            "73070599793680672726476826340615135890078390.083960707616445859670987728609198428");
  EXPECT_EQ(Expression("e^(-101)").simplify(false)->toString(),
            "1.3685394711738530002470557302322944177986775531612023009807438134142551921153897*10^-44");
  EXPECT_EQ(Expression("log(e,e)").simplify(false)->toString(), "1");
  EXPECT_EQ(Expression("log(2, 256)").simplify(false)->toString(), "8");
  EXPECT_EQ(Expression("log(pi, pi^10)").simplify(false)->toString(), "10");
  EXPECT_EQ(Expression("log(e,e^3)").simplify(false)->toString(), "3");
  EXPECT_EQ(Expression("ln3").simplify(false)->toString(),
            "1.098612288668109691395245236922525704647490557822749451734694333637494293218609");
  EXPECT_EQ(Expression("ln2").simplify(false)->toString(),
            "0.69314718055994530941723212145817656807550013436025525412068000949339362196969472");
  EXPECT_EQ(Expression("ln100").simplify(false)->toString(),
            "4.605170185988091368035982909368728415202202977257545952066655801935145219354705");
  EXPECT_EQ(Expression("ln(e)").simplify(false)->toString(), "1");
  EXPECT_EQ(Expression("lg99").simplify(false)->toString(),
            "1.9956351945975499153402557777532548601069599188478448242562702992902113378005716");
  EXPECT_EQ(Expression("lg100").simplify(false)->toString(), "2");
  EXPECT_EQ(Expression("lb100").simplify(false)->toString(),
            "6.6438561897747246957406388589787803517296627860491612241095127916318695532172504");
  EXPECT_EQ(Expression("lb4").simplify(false)->toString(), "2");
  EXPECT_EQ(Expression("sin10").simplify(false)->toString(),
            "-0.54402111088936981340474766185137728168364301291622389157418401261675720964049343");
  EXPECT_EQ(Expression("cos10").simplify(false)->toString(),
            "-0.83907152907645245225886394782406483451993016513316854683595373104879258686627077");
  EXPECT_EQ(Expression("tan10").simplify(false)->toString(),
            "0.6483608274590866712591249330098086768168743429837249756336279673958556003746239");
  EXPECT_EQ(Expression("cot10").simplify(false)->toString(),
            "1.5423510453569200482774693556824293113206672064019624909194716061981945043136768");
  EXPECT_EQ(Expression("asin0.9").simplify(false)->toString(),
            "1.1197695149986341866866770558453996158951621864033028823756818639144375371065333");
  EXPECT_EQ(Expression("acos0.9").simplify(false)->toString(),
            "0.45102681179626243254464463579435182620342251328425002811179043223947066603657116");
  EXPECT_EQ(Expression("atan10").simplify(false)->toString(),
            "1.4711276743037345918528755717617308518553063771832382624719635193438804556955538");
  EXPECT_EQ(Expression("acot10").simplify(false)->toString(),
            "0.099668652491162027378446119878020590243278322504314648015508776810027747447550654");
  EXPECT_EQ(Expression("((2))*sqrt2").simplify(false)->toString(),
            "2.8284271247461900976033774484193961571393437507538961463533594759814649569242141");
  EXPECT_EQ(Expression("sqrt2*((2))").simplify(false)->toString(),
            "2.8284271247461900976033774484193961571393437507538961463533594759814649569242141");
  EXPECT_EQ(Expression("sin(1)^2").simplify(false)->toString(),
            "0.70807341827357119349878411475038109488300038553777244537757498689098246806203958");
  EXPECT_EQ(Expression("sin(-1)^2").simplify(false)->toString(),
            "0.70807341827357119349878411475038109488300038553777244537757498689098246806203958");
  EXPECT_EQ(Expression("sin1^2").simplify(false)->toString(),
            "0.70807341827357119349878411475038109488300038553777244537757498689098246806203958");
  EXPECT_EQ(Expression("sin(10^30)").simplify(false)->toString(),
            "-0.090116901912138058030386428952987330274396332993043449885460666579773983476795775");
  EXPECT_EQ(Expression("sin(1)^2+cos(1)^2").simplify(false)->toString(), "1");
  EXPECT_EQ(Expression("sin(pi/3)").simplify(false)->toString(),
            "0.86602540378443864676372317075293618347140262690519031402790348972596650845440002");
  EXPECT_EQ(Expression("cos(pi/3)").simplify(false)->toString(), "0.5");
  EXPECT_EQ(Expression("2!*e").simplify(false)->toString(),
            "5.4365636569180904707205749427053249955144941873999191499339352554481532607070952");
  EXPECT_EQ(Expression("e*2!").simplify(false)->toString(),
            "5.4365636569180904707205749427053249955144941873999191499339352554481532607070952");
  EXPECT_EQ(Expression("sqrt((1-cos(2*(pi/3)))/2)").simplify(false)->toString(),
            "0.86602540378443864676372317075293618347140262690519031402790348972596650845440002");
  EXPECT_EQ(Expression("2*sqrt((1-cos(2*(pi/3)))/2)*cos(pi/3)").simplify(false)->toString(),
            "0.86602540378443864676372317075293618347140262690519031402790348972596650845440002");
  EXPECT_EQ(Expression("sin(e)=sin(e)").simplify(false)->toString(), "true");
  EXPECT_EQ(Expression("sin(e)>sin(e)").simplify(false)->toString(), "false");
  EXPECT_EQ(Expression("sin(e)>=sin(e)").simplify(false)->toString(), "true");
  EXPECT_EQ(Expression("sin(e)<sin(e)").simplify(false)->toString(), "false");
  EXPECT_EQ(Expression("sin(e)<=sin(e)").simplify(false)->toString(), "true");
  EXPECT_EQ(Expression("1/(sin(5))").simplify(false)->toString(),
            "-1.0428352127714058197831198559077598439723517523645461744044708582222288573346961");
  EXPECT_EQ(Expression("log(e,5)=ln(5)").simplify(false)->toString(), "true");
  EXPECT_EQ(Expression("log(e,5)<ln(5)").simplify(false)->toString(), "false");
  EXPECT_EQ(Expression("log(e,5)>ln(5)").simplify(false)->toString(), "false");
  EXPECT_EQ(Expression("log(e,5)<=ln(5)").simplify(false)->toString(), "true");
  EXPECT_EQ(Expression("log(e,5)>=ln(5)").simplify(false)->toString(), "true");
  EXPECT_EQ(Expression("(sqrt((1-cos(2*(pi/3)))/2))'").simplify(false)->toString(), "0");

  // TODO logarithms
  // EXPECT_EQ(Expression("ln(ln(ln(ln(e))))").simplify(false)->toString(), "0");
  // EXPECT_EQ(Expression("ln(ln(ln(ln(ln(e)))))").simplify(false)->toString(), "1");
}

TEST(ExpressionTests, simplifyInpreciseNegativeTest) {
  EXPECT_THROW(Expression("ln(ln(ln(ln(e))))").simplify(false), UndefinedException);
  EXPECT_THROW(Expression("ln(ln(ln(ln(ln(e)))))").simplify(false), UndefinedException);
  EXPECT_THROW(Expression("e!").simplify(false), UndefinedException);
  EXPECT_THROW(Expression("sqrt(-1)").simplify(false), UndefinedException);
  EXPECT_THROW(Expression("ln(0)").simplify(false), UndefinedException);
  EXPECT_THROW(Expression("ln(-1)").simplify(false), UndefinedException);
  EXPECT_THROW(Expression("log(-1, 1)").simplify(false), UndefinedException);
  EXPECT_THROW(Expression("log(0, 1)").simplify(false), UndefinedException);
  EXPECT_THROW(Expression("log(1, 0)").simplify(false), UndefinedException);
  EXPECT_THROW(Expression("lb(-1)").simplify(false), UndefinedException);
  EXPECT_THROW(Expression("lg(-1)").simplify(false), UndefinedException);
  EXPECT_THROW(Expression("(-1)^(2/3)").simplify(false), UndefinedException);
  EXPECT_THROW(Expression("tan(pi/2)").simplify(false), UndefinedException);
  EXPECT_THROW(Expression("cot(0)").simplify(false), UndefinedException);
  EXPECT_THROW(Expression("asin(2)").simplify(false), UndefinedException);
  EXPECT_THROW(Expression("acos(2)").simplify(false), UndefinedException);
  EXPECT_THROW(Expression("tan(3/2*pi)").simplify(false), UndefinedException);
  EXPECT_THROW(Expression("cot(2*pi)").simplify(false), UndefinedException);

  // TODD: do no perform operation, when the result is too big
  EXPECT_THROW(Expression("ln(ln(ln(ln(ln(e^e^e^e^e)))))").simplify(false), UndefinedException);
}

TEST(ExpressionTests, solveTest) {
  EXPECT_EQ(Expression("x-10=0").solve(), "x in {10}");
  EXPECT_EQ(Expression("x<-10").solve(), "x+10<0");
  EXPECT_EQ(Expression("-10-x=0").solve(), "x in {-10}");
  EXPECT_EQ(Expression("x^2-10=39").solve(), "x in {-7,7}");
  EXPECT_EQ(Expression("x^2=0").solve(), "x in {0}");
  EXPECT_EQ(Expression("x^2=1").solve(), "x in {-1,1}");
  EXPECT_EQ(Expression("x^2=-1").solve(), "x^2+1=0"); // TODO complex numbers
  EXPECT_EQ(Expression("x^2-2x-3=0").solve(), "x in {-1,3}");
  EXPECT_EQ(Expression("15-2x-x^2=0").solve(), "x in {-5,3}");
  EXPECT_EQ(Expression("x^2+12x+36=0").solve(), "x in {-6}");
  EXPECT_EQ(Expression("15x^2+sin(25)x-10%=ey").solve(5), "15*x^2-2.7183*y-0.13235*x-0.1=0");
}

TEST(ExpressionTests, toStringPrecision) {
  EXPECT_EQ(Expression("10^10000").toString(8), "1*10^10000");
  EXPECT_EQ(Expression("x+e").toString(8), "x+2.7182818");
  EXPECT_EQ(Expression("9^10000").toString(8), "2.6613034*10^9542");
  EXPECT_EQ(Expression("sin(e)").toString(16), "0.4107812905029087");
  EXPECT_EQ(Expression("sin(sin(e))").toString(30), "0.39932574404189139297067052142");
}
