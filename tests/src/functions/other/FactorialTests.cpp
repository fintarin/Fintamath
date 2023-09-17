#include "gtest/gtest.h"

#include "fintamath/functions/other/Factorial.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Factorial f;
const Factorial f2(2);
const Factorial f3(3);

TEST(FactorialTests, toStringTest) {
  EXPECT_EQ(f.toString(), "!");
}

TEST(FactorialTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(FactorialTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::PostfixUnary);
}

TEST(FactorialTests, isAssociativeTest) {
  EXPECT_FALSE(f.isAssociative());
}

TEST(FactorialTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "1");
  EXPECT_EQ(f(Integer(1))->toString(), "1");
  EXPECT_EQ(f(Integer(2))->toString(), "2");
  EXPECT_EQ(f(Integer(3))->toString(), "6");
  EXPECT_EQ(f(Integer(4))->toString(), "24");
  EXPECT_EQ(f(Integer(5))->toString(), "120");
  EXPECT_EQ(f(Integer(10))->toString(), "3628800");
  EXPECT_EQ(f(Integer(500))->toString(),
            "1220136825991110068701238785423046926253574342803192842192413588385845373153881997605496447502203281863013"
            "6164771482035841633787220781772004807852051593292854779075719393306037729608590862704291745478824249127263"
            "4430567017327076946106280231045264421887878946575477714986349436778103764427403382736539747138647787849543"
            "8489595537537990423241061271326984327745715546309977202781014561081188373709531016356324432987029563896628"
            "9116589747695720879269288712817800702651745077684107196243903943225364226052349458501299185715012487069615"
            "6814162535905669342381300885624924689156412677565448188650659384795177536089400574523894033579847636394490"
            "5313062323749066445048824665075946735862074637925184200459369692981022263971952597190945217823331756934581"
            "5085523328207628200234026269078983424517120062077146409794561161276291459512372299133401695523638509428855"
            "9201872743379517301458635757082835578015873543276888868012039988238470215146760544540766353598417443048012"
            "8938313896881639487469658817504506926365338175055478128640000000000000000000000000000000000000000000000000"
            "000000000000000000000000000000000000000000000000000000000000000000000000000");

  EXPECT_EQ(f(Rational(10, 1))->toString(), "3628800");
  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "0.9513507698668731836292487177265402192550578626088377343050000770434265383322821");
  EXPECT_EQ(f(Rational(-1, 10))->toString(),
            "1.0686287021193193548973053356944807781698387850609731790493706839815721770254476");

  EXPECT_EQ(f(Real("0.1"))->toString(),
            "0.9513507698668731836292487177265402192550578626088377343050000770434265383322821");
  EXPECT_EQ(f(Real("10"))->toString(), "3628800.0");
  EXPECT_EQ(f(Real(-10))->toString(), "(-10.0)!");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "(1 + I)!");

  EXPECT_EQ(f(Integer(-10))->toString(), "ComplexInf");
  EXPECT_EQ(f(Rational(-10))->toString(), "ComplexInf");

  EXPECT_EQ(f(Variable("a"))->toString(), "a!");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(FactorialTests, call2Test) {
  EXPECT_EQ(f2(Integer(0))->toString(), "1");
  EXPECT_EQ(f2(Integer(1))->toString(), "1");
  EXPECT_EQ(f2(Integer(2))->toString(), "2");
  EXPECT_EQ(f2(Integer(3))->toString(), "3");
  EXPECT_EQ(f2(Integer(4))->toString(), "8");
  EXPECT_EQ(f2(Integer(5))->toString(), "15");
  EXPECT_EQ(f2(Integer(10))->toString(), "3840");
  EXPECT_EQ(f2(Integer(500))->toString(),
            "5849049697728183931901573966636399185893290101863305204136019757220414567257738129869679070426230366367652"
            "4519801978580022635614498055517710209011137393136263367055635637057883605036300944034886758546681615347607"
            "8819542001527937762172951762079266894496398139148992667153937293848100117303111705276322149142028172766173"
            "1208544954134335107331812412321791962113178938189516786683915122565052376248782141535507632768973188905459"
            "5155322981745629479849064902575529423867748242615886790540487176747609630034624512000000000000000000000000"
            "00000000000000000000000000000000000000");

  EXPECT_EQ(f2(Rational(10, 1))->toString(), "3840");
  EXPECT_EQ(f2(Rational(1, 10))->toString(), "(1/10)!!");
  EXPECT_EQ(f2(Rational(-1, 10))->toString(), "(-1/10)!!");

  EXPECT_EQ(f2(Real("0.1"))->toString(), "0.1!!");
  EXPECT_EQ(f2(Real("10"))->toString(), "10.0!!");

  EXPECT_EQ(f2(Integer(-10))->toString(), "(-10)!!");
  EXPECT_EQ(f2(Rational(-10))->toString(), "(-10)!!");
  EXPECT_EQ(f2(Real(-10))->toString(), "(-10.0)!!");

  EXPECT_EQ(f2(Variable("a"))->toString(), "a!!");

  EXPECT_THROW(f2(), InvalidInputFunctionException);
  EXPECT_THROW(f2(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(FactorialTests, call3Test) {
  EXPECT_EQ(f3(Integer(0))->toString(), "1");
  EXPECT_EQ(f3(Integer(1))->toString(), "1");
  EXPECT_EQ(f3(Integer(2))->toString(), "2");
  EXPECT_EQ(f3(Integer(3))->toString(), "3");
  EXPECT_EQ(f3(Integer(4))->toString(), "4");
  EXPECT_EQ(f3(Integer(5))->toString(), "10");
  EXPECT_EQ(f3(Integer(10))->toString(), "280");
  EXPECT_EQ(f3(Integer(500))->toString(),
            "9627993490692047015610121660806242061041980962334724315971467112857597905672427525550231392342889276669093"
            "4746446102067564365301803305987158213375383608919071597887358308001635489486833441141250874436302859378574"
            "6697670525318423753154497673666758945906833918816145199178864638598033799687449468589488107994117034844310"
            "8099519138035138560000000000000000000000000000000000000000000");

  EXPECT_EQ(f3(Rational(10, 1))->toString(), "280");
  EXPECT_EQ(f3(Rational(1, 10))->toString(), "(1/10)!!!");
  EXPECT_EQ(f3(Rational(-1, 10))->toString(), "(-1/10)!!!");

  EXPECT_EQ(f3(Real("0.1"))->toString(), "0.1!!!");
  EXPECT_EQ(f3(Real("10"))->toString(), "10.0!!!");

  EXPECT_EQ(f3(Integer(-10))->toString(), "(-10)!!!");
  EXPECT_EQ(f3(Rational(-10))->toString(), "(-10)!!!");
  EXPECT_EQ(f3(Real(-10))->toString(), "(-10.0)!!!");

  EXPECT_EQ(f3(Variable("a"))->toString(), "a!!!");

  EXPECT_THROW(f3(), InvalidInputFunctionException);
  EXPECT_THROW(f3(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(FactorialTests, getSetOrderTest) {
  Factorial fnth;
  EXPECT_EQ(fnth.getOrder(), 1);

  fnth.setOrder(123);
  EXPECT_EQ(fnth.getOrder(), 123);
}

TEST(FactorialTests, exprTest) {
  EXPECT_EQ(factorialExpr(Integer(10))->toString(), "10!");
}

TEST(FactorialTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(FactorialTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Factorial());
  EXPECT_EQ(Factorial(), f);
  EXPECT_EQ(f, cast<IMathObject>(Factorial()));
  EXPECT_EQ(cast<IMathObject>(Factorial()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(FactorialTests, getTypeIdTest) {
  EXPECT_EQ(Factorial::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Factorial));
  EXPECT_EQ(Factorial().getTypeId(), MathObjectTypeId(MathObjectType::Factorial));
}
