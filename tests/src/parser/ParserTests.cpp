#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Abs.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Frac.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sign.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
#include "fintamath/functions/calculus/Integral.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/functions/comparison/Less.hpp"
#include "fintamath/functions/comparison/LessEqv.hpp"
#include "fintamath/functions/comparison/More.hpp"
#include "fintamath/functions/comparison/MoreEqv.hpp"
#include "fintamath/functions/comparison/Neqv.hpp"
#include "fintamath/functions/hyperbolic/Acosh.hpp"
#include "fintamath/functions/hyperbolic/Acoth.hpp"
#include "fintamath/functions/hyperbolic/Acsch.hpp"
#include "fintamath/functions/hyperbolic/Asech.hpp"
#include "fintamath/functions/hyperbolic/Asinh.hpp"
#include "fintamath/functions/hyperbolic/Atanh.hpp"
#include "fintamath/functions/hyperbolic/Cosh.hpp"
#include "fintamath/functions/hyperbolic/Coth.hpp"
#include "fintamath/functions/hyperbolic/Csch.hpp"
#include "fintamath/functions/hyperbolic/Sech.hpp"
#include "fintamath/functions/hyperbolic/Sinh.hpp"
#include "fintamath/functions/hyperbolic/Tanh.hpp"
#include "fintamath/functions/logarithms/Lb.hpp"
#include "fintamath/functions/logarithms/Lg.hpp"
#include "fintamath/functions/logarithms/Ln.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/Equiv.hpp"
#include "fintamath/functions/logic/Impl.hpp"
#include "fintamath/functions/logic/Nequiv.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"
#include "fintamath/functions/other/Deg.hpp"
#include "fintamath/functions/other/Factorial.hpp"
#include "fintamath/functions/other/Index.hpp"
#include "fintamath/functions/other/Percent.hpp"
#include "fintamath/functions/powers/Exp.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/powers/PowF.hpp"
#include "fintamath/functions/powers/Root.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/functions/trigonometry/Acos.hpp"
#include "fintamath/functions/trigonometry/Acot.hpp"
#include "fintamath/functions/trigonometry/Acsc.hpp"
#include "fintamath/functions/trigonometry/Asec.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"
#include "fintamath/functions/trigonometry/Atan.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/trigonometry/Cot.hpp"
#include "fintamath/functions/trigonometry/Csc.hpp"
#include "fintamath/functions/trigonometry/Sec.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/functions/trigonometry/Tan.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/False.hpp"
#include "fintamath/literals/constants/I.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/literals/constants/True.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/parser/Parser.hpp"

using namespace fintamath;

TEST(ParserTests, parseMathObjectTest) {
  EXPECT_TRUE(is<IArithmetic>(IMathObject::parse("a+1")));
  EXPECT_TRUE(is<ILiteral>(IMathObject::parse("a")));
  EXPECT_TRUE(is<IFunction>(IMathObject::parse("sin")));
  EXPECT_TRUE(is<IExpression>(IMathObject::parse("a+1")));

  EXPECT_FALSE(is<IArithmetic>(IMathObject::parse("a")));
  EXPECT_FALSE(is<ILiteral>(IMathObject::parse("sin")));
  EXPECT_FALSE(is<IFunction>(IMathObject::parse("123")));
  EXPECT_FALSE(is<IExpression>(IMathObject::parse("sin")));

  EXPECT_EQ(IMathObject::parse("x+"), nullptr);
}

TEST(ParserTests, parseArithmeticTest) {
  EXPECT_TRUE(is<IComparable>(IArithmetic::parse("1231412736.218731623872183")));
  EXPECT_TRUE(is<IInteger>(IArithmetic::parse("1231412736218731623872183")));
  EXPECT_TRUE(is<IInteger>(IArithmetic::parse("1231412736218731623872183")));
  EXPECT_TRUE(is<Expression>(IArithmetic::parse("a")));

  EXPECT_FALSE(is<IComparable>(IArithmetic::parse("True")));
  EXPECT_FALSE(is<IInteger>(IArithmetic::parse("E")));
  EXPECT_FALSE(is<IInteger>(IArithmetic::parse("12314127362187.31623872183")));
  EXPECT_FALSE(is<INumber>(IArithmetic::parse("a")));
  EXPECT_FALSE(is<Expression>(IArithmetic::parse("123")));

  EXPECT_EQ(IArithmetic::parse("x+"), nullptr);
}

TEST(ParserTests, parseComparableTest) {
  EXPECT_TRUE(is<INumber>(IComparable::parse("12314127362.18731623872183")));

  EXPECT_EQ(IComparable::parse("x"), nullptr);
}

TEST(ParserTests, parseIntegerTest) {
  EXPECT_TRUE(is<Integer>(IInteger::parse("1231412736218731623872183")));

  EXPECT_EQ(IInteger::parse("x"), nullptr);
}

TEST(ParserTests, parseModularTest) {
  EXPECT_TRUE(is<Integer>(IInteger::parse("18731623872183")));

  EXPECT_EQ(IInteger::parse("123.123"), nullptr);
}

TEST(ParserTests, parseNumberTest) {
  EXPECT_EQ(INumber::parse("1231412736218731623872183")->toString(), "1231412736218731623872183");
  EXPECT_TRUE(is<Integer>(INumber::parse("1231412736218731623872183")));

  EXPECT_EQ(INumber::parse("-1231412736218731623872183")->toString(), "-1231412736218731623872183");
  EXPECT_TRUE(is<Integer>(INumber::parse("-1231412736218731623872183")));

  EXPECT_EQ(INumber::parse("0")->toString(), "0");
  EXPECT_TRUE(is<Integer>(INumber::parse("0")));

  EXPECT_EQ(INumber::parse("0.1")->toString(), "1/10");
  EXPECT_TRUE(is<Rational>(INumber::parse("0.1")));

  EXPECT_EQ(INumber::parse(".1")->toString(), "1/10");
  EXPECT_TRUE(is<Rational>(INumber::parse(".1")));

  EXPECT_EQ(INumber::parse("1.")->toString(), "1");
  EXPECT_TRUE(is<Rational>(INumber::parse("1.")));

  EXPECT_EQ(INumber::parse("12323231498721983.12323432432")->toString(), "77020196867012394520214527/6250000000");
  EXPECT_TRUE(is<Rational>(INumber::parse("12323231498721983.12323432432")));

  EXPECT_EQ(INumber::parse("-12323231498721983.12323432432")->toString(), "-77020196867012394520214527/6250000000");
  EXPECT_TRUE(is<Rational>(INumber::parse("-12323231498721983.12323432432")));

  EXPECT_EQ(INumber::parse("--10"), nullptr);
  EXPECT_EQ(INumber::parse("test"), nullptr);
  EXPECT_EQ(INumber::parse(""), nullptr);
  EXPECT_EQ(INumber::parse("+"), nullptr);
  EXPECT_EQ(INumber::parse("939849.0-0023"), nullptr);
  EXPECT_EQ(INumber::parse("a"), nullptr);
  EXPECT_EQ(INumber::parse("a.1"), nullptr);
  EXPECT_EQ(INumber::parse("1.a"), nullptr);
  EXPECT_EQ(INumber::parse("1a.1"), nullptr);
  EXPECT_EQ(INumber::parse("1.1a"), nullptr);
  EXPECT_EQ(INumber::parse("--10.-1"), nullptr);
  EXPECT_EQ(INumber::parse("10.-1"), nullptr);
  EXPECT_EQ(INumber::parse("1-0.1"), nullptr);
  EXPECT_EQ(INumber::parse("10-.1"), nullptr);
  EXPECT_EQ(INumber::parse("10.--1"), nullptr);
}

TEST(ParserTests, parseLiteralTest) {
  EXPECT_TRUE(is<E>(ILiteral::parse("E")));
  EXPECT_TRUE(is<Variable>(ILiteral::parse("a")));
  EXPECT_TRUE(is<Variable>(ILiteral::parse("z")));

  EXPECT_EQ(ILiteral::parse("1"), nullptr);
  EXPECT_EQ(ILiteral::parse("a_"), nullptr);
  EXPECT_EQ(ILiteral::parse("a1"), nullptr);
  EXPECT_EQ(ILiteral::parse("aa"), nullptr);
  EXPECT_EQ(ILiteral::parse("A"), nullptr);
  EXPECT_EQ(ILiteral::parse("Z"), nullptr);
}

TEST(ParseTests, parseConstantTest) {
  EXPECT_TRUE(is<E>(IConstant::parse("E")));
  EXPECT_TRUE(is<Pi>(IConstant::parse("Pi")));
  EXPECT_TRUE(is<True>(IConstant::parse("True")));
  EXPECT_TRUE(is<False>(IConstant::parse("False")));
  EXPECT_TRUE(is<I>(IConstant::parse("I")));
  EXPECT_TRUE(is<Inf>(IConstant::parse("Inf")));
  EXPECT_TRUE(is<NegInf>(IConstant::parse("-Inf")));
  EXPECT_TRUE(is<ComplexInf>(IConstant::parse("ComplexInf")));
  EXPECT_TRUE(is<Undefined>(IConstant::parse("Undefined")));

  EXPECT_EQ(IConstant::parse("a"), nullptr);
  EXPECT_EQ(IConstant::parse("z"), nullptr);
  EXPECT_EQ(IConstant::parse("1"), nullptr);
  EXPECT_EQ(IConstant::parse("a_"), nullptr);
  EXPECT_EQ(IConstant::parse("a1"), nullptr);
  EXPECT_EQ(IConstant::parse("aa"), nullptr);
}

TEST(ParserTests, parseFunctionTest) {
  EXPECT_TRUE(is<Sqrt>(IFunction::parse("sqrt")));
  EXPECT_TRUE(is<Root>(IFunction::parse("root")));
  EXPECT_TRUE(is<Exp>(IFunction::parse("exp")));
  EXPECT_TRUE(is<Log>(IFunction::parse("log")));
  EXPECT_TRUE(is<Ln>(IFunction::parse("ln")));
  EXPECT_TRUE(is<Lb>(IFunction::parse("lb")));
  EXPECT_TRUE(is<Lg>(IFunction::parse("lg")));
  EXPECT_TRUE(is<Sin>(IFunction::parse("sin")));
  EXPECT_TRUE(is<Cos>(IFunction::parse("cos")));
  EXPECT_TRUE(is<Tan>(IFunction::parse("tan")));
  EXPECT_TRUE(is<Cot>(IFunction::parse("cot")));
  EXPECT_TRUE(is<Sec>(IFunction::parse("sec")));
  EXPECT_TRUE(is<Csc>(IFunction::parse("csc")));
  EXPECT_TRUE(is<Asin>(IFunction::parse("asin")));
  EXPECT_TRUE(is<Acos>(IFunction::parse("acos")));
  EXPECT_TRUE(is<Atan>(IFunction::parse("atan")));
  EXPECT_TRUE(is<Acot>(IFunction::parse("acot")));
  EXPECT_TRUE(is<Asec>(IFunction::parse("asec")));
  EXPECT_TRUE(is<Acsc>(IFunction::parse("acsc")));
  EXPECT_TRUE(is<Abs>(IFunction::parse("abs")));
  EXPECT_TRUE(is<Sign>(IFunction::parse("sign")));
  EXPECT_TRUE(is<Sinh>(IFunction::parse("sinh")));
  EXPECT_TRUE(is<Cosh>(IFunction::parse("cosh")));
  EXPECT_TRUE(is<Tanh>(IFunction::parse("tanh")));
  EXPECT_TRUE(is<Coth>(IFunction::parse("coth")));
  EXPECT_TRUE(is<Sech>(IFunction::parse("sech")));
  EXPECT_TRUE(is<Csch>(IFunction::parse("csch")));
  EXPECT_TRUE(is<Asinh>(IFunction::parse("asinh")));
  EXPECT_TRUE(is<Acosh>(IFunction::parse("acosh")));
  EXPECT_TRUE(is<Atanh>(IFunction::parse("atanh")));
  EXPECT_TRUE(is<Acoth>(IFunction::parse("acoth")));
  EXPECT_TRUE(is<Asech>(IFunction::parse("asech")));
  EXPECT_TRUE(is<Acsch>(IFunction::parse("acsch")));
  EXPECT_TRUE(is<Derivative>(IFunction::parse("derivative")));
  EXPECT_TRUE(is<Integral>(IFunction::parse("integral")));
  EXPECT_TRUE(is<Frac>(IFunction::parse("frac")));
  EXPECT_TRUE(is<PowF>(IFunction::parse("pow")));

  EXPECT_TRUE(is<Add>(IFunction::parse("+", IFunction::Type::Binary)));
  EXPECT_TRUE(is<UnaryPlus>(IFunction::parse("+", IFunction::Type::Unary)));
  EXPECT_TRUE(is<Sub>(IFunction::parse("-", IFunction::Type::Binary)));
  EXPECT_TRUE(is<Neg>(IFunction::parse("-", IFunction::Type::Unary)));

  EXPECT_EQ(IFunction::parse("asdgewfe"), nullptr);
  EXPECT_EQ(IFunction::parse("1224"), nullptr);
}

TEST(ParserTests, parseOperatorTest) {
  EXPECT_TRUE(is<Add>(IOperator::parse("+", IOperator::Priority::Addition)));
  EXPECT_TRUE(is<UnaryPlus>(IOperator::parse("+", IOperator::Priority::PrefixUnary)));
  EXPECT_TRUE(is<Sub>(IOperator::parse("-", IOperator::Priority::Addition)));
  EXPECT_TRUE(is<Neg>(IOperator::parse("-", IOperator::Priority::PrefixUnary)));
  EXPECT_TRUE(is<Mul>(IOperator::parse("*")));
  EXPECT_TRUE(is<Div>(IOperator::parse("/")));
  EXPECT_TRUE(is<Pow>(IOperator::parse("^")));
  EXPECT_TRUE(is<Percent>(IOperator::parse("%")));
  EXPECT_TRUE(is<Factorial>(IOperator::parse("!")));
  EXPECT_TRUE(is<Eqv>(IOperator::parse("=")));
  EXPECT_TRUE(is<Neqv>(IOperator::parse("!=")));
  EXPECT_TRUE(is<Less>(IOperator::parse("<")));
  EXPECT_TRUE(is<More>(IOperator::parse(">")));
  EXPECT_TRUE(is<LessEqv>(IOperator::parse("<=")));
  EXPECT_TRUE(is<MoreEqv>(IOperator::parse(">=")));
  EXPECT_TRUE(is<Not>(IOperator::parse("~", IOperator::Priority::PrefixUnary)));
  EXPECT_TRUE(is<And>(IOperator::parse("&")));
  EXPECT_TRUE(is<Or>(IOperator::parse("|")));
  EXPECT_TRUE(is<Impl>(IOperator::parse("->")));
  EXPECT_TRUE(is<Equiv>(IOperator::parse("<->")));
  EXPECT_TRUE(is<Nequiv>(IOperator::parse("!<->")));
  EXPECT_TRUE(is<Index>(IOperator::parse("_")));
  EXPECT_TRUE(is<Deg>(IOperator::parse("deg")));

  EXPECT_EQ(IOperator::parse("asdgewfe"), nullptr);
  EXPECT_EQ(IOperator::parse("1224"), nullptr);
}

TEST(ParserTests, parseExpressionTest) {
  EXPECT_TRUE(is<Expression>(IExpression::parse("x+1")));
  EXPECT_TRUE(is<Expression>(IExpression::parse("x*1")));

  EXPECT_EQ(IExpression::parse("x+"), nullptr);
  EXPECT_EQ(IExpression::parse("^x"), nullptr);
}
