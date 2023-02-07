#include <gtest/gtest.h>

#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/parser/Tokenizer.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/arithmetic/Abs.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sign.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/functions/comparison/Less.hpp"
#include "fintamath/functions/comparison/LessEqv.hpp"
#include "fintamath/functions/comparison/More.hpp"
#include "fintamath/functions/comparison/MoreEqv.hpp"
#include "fintamath/functions/comparison/Neqv.hpp"
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
#include "fintamath/functions/other/Degrees.hpp"
#include "fintamath/functions/other/Factorial.hpp"
#include "fintamath/functions/other/Index.hpp"
#include "fintamath/functions/other/Percent.hpp"
#include "fintamath/functions/powers/Exp.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/functions/trigonometry/Acos.hpp"
#include "fintamath/functions/trigonometry/Acosh.hpp"
#include "fintamath/functions/trigonometry/Acot.hpp"
#include "fintamath/functions/trigonometry/Acoth.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"
#include "fintamath/functions/trigonometry/Asinh.hpp"
#include "fintamath/functions/trigonometry/Atan.hpp"
#include "fintamath/functions/trigonometry/Atanh.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/trigonometry/Cosh.hpp"
#include "fintamath/functions/trigonometry/Cot.hpp"
#include "fintamath/functions/trigonometry/Coth.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/functions/trigonometry/Sinh.hpp"
#include "fintamath/functions/trigonometry/Tan.hpp"
#include "fintamath/functions/trigonometry/Tanh.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/False.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/literals/constants/True.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/parser/Parser.hpp"

using namespace fintamath;

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

TEST(ParseTests, parseConstantTest) {
  EXPECT_TRUE(is<E>(IConstant::parse("E")));
  EXPECT_TRUE(is<Pi>(IConstant::parse("Pi")));

  EXPECT_EQ(IConstant::parse("a"), nullptr);
  EXPECT_EQ(IConstant::parse("z"), nullptr);
  EXPECT_EQ(IConstant::parse("1"), nullptr);
  EXPECT_EQ(IConstant::parse("a_"), nullptr);
  EXPECT_EQ(IConstant::parse("a1"), nullptr);
  EXPECT_EQ(IConstant::parse("aa"), nullptr);
}

TEST(ParserTests, parseLiteralTest) {
  EXPECT_TRUE(is<E>(ILiteral::parse("E")));
  EXPECT_TRUE(is<Pi>(ILiteral::parse("Pi")));
  EXPECT_TRUE(is<Variable>(ILiteral::parse("a")));
  EXPECT_TRUE(is<Variable>(ILiteral::parse("z")));
  EXPECT_TRUE(is<True>(ILiteral::parse("True")));
  EXPECT_TRUE(is<False>(ILiteral::parse("False")));

  EXPECT_EQ(ILiteral::parse("1"), nullptr);
  EXPECT_EQ(ILiteral::parse("a_"), nullptr);
  EXPECT_EQ(ILiteral::parse("a1"), nullptr);
  EXPECT_EQ(ILiteral::parse("aa"), nullptr);
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
  EXPECT_TRUE(is<Derivative>(IOperator::parse("'")));
  EXPECT_TRUE(is<Not>(IOperator::parse("~", IOperator::Priority::PrefixUnary)));
  EXPECT_TRUE(is<And>(IOperator::parse("&")));
  EXPECT_TRUE(is<Or>(IOperator::parse("|")));
  EXPECT_TRUE(is<Impl>(IOperator::parse("->")));
  EXPECT_TRUE(is<Equiv>(IOperator::parse("<->")));
  EXPECT_TRUE(is<Nequiv>(IOperator::parse("!<->")));
  EXPECT_TRUE(is<Index>(IOperator::parse("_")));

  EXPECT_EQ(IOperator::parse("asdgewfe"), nullptr);
  EXPECT_EQ(IOperator::parse("1224"), nullptr);
}

TEST(ParserTests, parseFunctionTest) {
  EXPECT_TRUE(is<Add>(IFunction::parse("+", IFunction::Type::Binary)));
  EXPECT_TRUE(is<UnaryPlus>(IFunction::parse("+", IFunction::Type::Unary)));
  EXPECT_TRUE(is<Sub>(IFunction::parse("-", IFunction::Type::Binary)));
  EXPECT_TRUE(is<Neg>(IFunction::parse("-", IFunction::Type::Unary)));
  EXPECT_TRUE(is<Mul>(IFunction::parse("*")));
  EXPECT_TRUE(is<Div>(IFunction::parse("/")));
  EXPECT_TRUE(is<Pow>(IFunction::parse("^")));
  EXPECT_TRUE(is<Percent>(IFunction::parse("%")));
  EXPECT_TRUE(is<Factorial>(IFunction::parse("!")));
  EXPECT_TRUE(is<Eqv>(IFunction::parse("=")));
  EXPECT_TRUE(is<Neqv>(IFunction::parse("!=")));
  EXPECT_TRUE(is<Less>(IFunction::parse("<")));
  EXPECT_TRUE(is<More>(IFunction::parse(">")));
  EXPECT_TRUE(is<LessEqv>(IFunction::parse("<=")));
  EXPECT_TRUE(is<MoreEqv>(IFunction::parse(">=")));
  EXPECT_TRUE(is<Derivative>(IFunction::parse("'")));
  EXPECT_TRUE(is<Sqrt>(IFunction::parse("sqrt")));
  EXPECT_TRUE(is<Exp>(IFunction::parse("exp")));
  EXPECT_TRUE(is<Log>(IFunction::parse("log")));
  EXPECT_TRUE(is<Ln>(IFunction::parse("ln")));
  EXPECT_TRUE(is<Lb>(IFunction::parse("lb")));
  EXPECT_TRUE(is<Lg>(IFunction::parse("lg")));
  EXPECT_TRUE(is<Sin>(IFunction::parse("sin")));
  EXPECT_TRUE(is<Cos>(IFunction::parse("cos")));
  EXPECT_TRUE(is<Tan>(IFunction::parse("tan")));
  EXPECT_TRUE(is<Cot>(IFunction::parse("cot")));
  EXPECT_TRUE(is<Asin>(IFunction::parse("asin")));
  EXPECT_TRUE(is<Acos>(IFunction::parse("acos")));
  EXPECT_TRUE(is<Atan>(IFunction::parse("atan")));
  EXPECT_TRUE(is<Acot>(IFunction::parse("acot")));
  EXPECT_TRUE(is<Abs>(IFunction::parse("abs")));
  EXPECT_TRUE(is<Not>(IFunction::parse("~")));
  EXPECT_TRUE(is<And>(IFunction::parse("&")));
  EXPECT_TRUE(is<Or>(IFunction::parse("|")));
  EXPECT_TRUE(is<Impl>(IFunction::parse("->")));
  EXPECT_TRUE(is<Equiv>(IFunction::parse("<->")));
  EXPECT_TRUE(is<Nequiv>(IFunction::parse("!<->")));
  EXPECT_TRUE(is<Degrees>(IFunction::parse("degrees")));
  EXPECT_TRUE(is<Index>(IFunction::parse("_")));
  EXPECT_TRUE(is<Sign>(IFunction::parse("sign")));
  EXPECT_TRUE(is<Sinh>(IFunction::parse("sinh")));
  EXPECT_TRUE(is<Cosh>(IFunction::parse("cosh")));
  EXPECT_TRUE(is<Tanh>(IFunction::parse("tanh")));
  EXPECT_TRUE(is<Coth>(IFunction::parse("coth")));
  EXPECT_TRUE(is<Asinh>(IFunction::parse("asinh")));
  EXPECT_TRUE(is<Acosh>(IFunction::parse("acosh")));
  EXPECT_TRUE(is<Atanh>(IFunction::parse("atanh")));
  EXPECT_TRUE(is<Acoth>(IFunction::parse("acoth")));

  EXPECT_EQ(IFunction::parse("asdgewfe"), nullptr);
  EXPECT_EQ(IFunction::parse("1224"), nullptr);
}
