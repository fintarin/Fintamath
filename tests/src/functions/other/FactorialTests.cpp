#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/other/Factorial.hpp"

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

TEST(FactorialTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(FactorialTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(FactorialTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(FactorialTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(FactorialTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::PostfixUnary);
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
  EXPECT_EQ(f(Integer(500))->toString(), "1220136825991110068701238785423046926253574342803192842192413588385845373153881997605496447502203281863013616477148203584163378722078177200480785205159329285477907571939330603772960859086270429174547882424912726344305670173270769461062802310452644218878789465754777149863494367781037644274033827365397471386477878495438489595537537990423241061271326984327745715546309977202781014561081188373709531016356324432987029563896628911658974769572087926928871281780070265174507768410719624390394322536422605234945850129918571501248706961568141625359056693423813008856249246891564126775654481886506593847951775360894005745238940335798476363944905313062323749066445048824665075946735862074637925184200459369692981022263971952597190945217823331756934581508552332820762820023402626907898342451712006207714640979456116127629145951237229913340169552363850942885592018727433795173014586357570828355780158735432768888680120399882384702151467605445407663535984174430480128938313896881639487469658817504506926365338175055478128640000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

  EXPECT_EQ(f(Rational(10, 1))->toString(), "3628800");
  EXPECT_EQ(f(Rational(1, 10))->toString(), "0.95135076986687318363");
  EXPECT_EQ(f(Rational(-1, 10))->toString(), "1.0686287021193193549");

  EXPECT_EQ(f(Real("0.1"))->toString(), "0.95135076986687318363");
  EXPECT_EQ(f(Real("10"))->toString(), "3628800.0");
  EXPECT_EQ(f(Real(-10))->toString(), "(-10.0)!");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "(1 + I)!");

  EXPECT_EQ(f(Integer(-10))->toString(), "ComplexInf");
  EXPECT_EQ(f(Rational(-10))->toString(), "ComplexInf");

  EXPECT_EQ(f(Variable("a"))->toString(), "a!");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(FactorialTests, callDoubleFactorialTest) {
  EXPECT_EQ(f2(Integer(0))->toString(), "1");
  EXPECT_EQ(f2(Integer(1))->toString(), "1");
  EXPECT_EQ(f2(Integer(2))->toString(), "2");
  EXPECT_EQ(f2(Integer(3))->toString(), "3");
  EXPECT_EQ(f2(Integer(4))->toString(), "8");
  EXPECT_EQ(f2(Integer(5))->toString(), "15");
  EXPECT_EQ(f2(Integer(10))->toString(), "3840");
  EXPECT_EQ(f2(Integer(500))->toString(), "5849049697728183931901573966636399185893290101863305204136019757220414567257738129869679070426230366367652451980197858002263561449805551771020901113739313626336705563563705788360503630094403488675854668161534760788195420015279377621729517620792668944963981391489926671539372938481001173031117052763221491420281727661731208544954134335107331812412321791962113178938189516786683915122565052376248782141535507632768973188905459515532298174562947984906490257552942386774824261588679054048717674760963003462451200000000000000000000000000000000000000000000000000000000000000");

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

TEST(FactorialTests, callTripleFactorialTest) {
  EXPECT_EQ(f3(Integer(0))->toString(), "1");
  EXPECT_EQ(f3(Integer(1))->toString(), "1");
  EXPECT_EQ(f3(Integer(2))->toString(), "2");
  EXPECT_EQ(f3(Integer(3))->toString(), "3");
  EXPECT_EQ(f3(Integer(4))->toString(), "4");
  EXPECT_EQ(f3(Integer(5))->toString(), "10");
  EXPECT_EQ(f3(Integer(10))->toString(), "280");
  EXPECT_EQ(f3(Integer(500))->toString(), "9627993490692047015610121660806242061041980962334724315971467112857597905672427525550231392342889276669093474644610206756436530180330598715821337538360891907159788735830800163548948683344114125087443630285937857466976705253184237531544976736667589459068339188161451991788646385980337996874494685894881079941170348443108099519138035138560000000000000000000000000000000000000000000");

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

TEST(FactorialTests, getClassTest) {
  EXPECT_EQ(f.getClass(), MathObjectClass("Factorial"));
  EXPECT_EQ(f.getClass().getParent(), IOperator::getClassStatic());
}
