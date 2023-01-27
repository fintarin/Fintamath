#include <gtest/gtest.h>

#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/logic/Equiv.hpp"
#include "fintamath/functions/logic/Impl.hpp"
#include "fintamath/functions/logic/Nequiv.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/parser/Tokenizer.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
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
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"
#include "fintamath/functions/other/Abs.hpp"
#include "fintamath/functions/other/Factorial.hpp"
#include "fintamath/functions/other/Percent.hpp"
#include "fintamath/functions/powers/Exp.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/functions/trigonometry/Acos.hpp"
#include "fintamath/functions/trigonometry/Acot.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"
#include "fintamath/functions/trigonometry/Atan.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/trigonometry/Cot.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/functions/trigonometry/Tan.hpp"
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
  EXPECT_TRUE(cast<Integer>(INumber::parse("1231412736218731623872183")));

  EXPECT_EQ(INumber::parse("-1231412736218731623872183")->toString(), "-1231412736218731623872183");
  EXPECT_TRUE(cast<Integer>(INumber::parse("-1231412736218731623872183")));

  EXPECT_EQ(INumber::parse("0")->toString(), "0");
  EXPECT_TRUE(cast<Integer>(INumber::parse("0")));

  EXPECT_EQ(INumber::parse("0.1")->toString(), "1/10");
  EXPECT_TRUE(cast<Rational>(INumber::parse("0.1")));

  EXPECT_EQ(INumber::parse(".1")->toString(), "1/10");
  EXPECT_TRUE(cast<Rational>(INumber::parse(".1")));

  EXPECT_EQ(INumber::parse("1.")->toString(), "1");
  EXPECT_TRUE(cast<Rational>(INumber::parse("1.")));

  EXPECT_EQ(INumber::parse("12323231498721983.12323432432")->toString(), "77020196867012394520214527/6250000000");
  EXPECT_TRUE(cast<Rational>(INumber::parse("12323231498721983.12323432432")));

  EXPECT_EQ(INumber::parse("-12323231498721983.12323432432")->toString(), "-77020196867012394520214527/6250000000");
  EXPECT_TRUE(cast<Rational>(INumber::parse("-12323231498721983.12323432432")));

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
  EXPECT_TRUE(cast<E>(IConstant::parse("E")));
  EXPECT_TRUE(cast<Pi>(IConstant::parse("Pi")));

  EXPECT_EQ(IConstant::parse("a"), nullptr);
  EXPECT_EQ(IConstant::parse("z"), nullptr);
  EXPECT_EQ(IConstant::parse("1"), nullptr);
  EXPECT_EQ(IConstant::parse("a_"), nullptr);
  EXPECT_EQ(IConstant::parse("a1"), nullptr);
  EXPECT_EQ(IConstant::parse("aa"), nullptr);
}

TEST(ParserTests, parseLiteralTest) {
  EXPECT_TRUE(cast<E>(ILiteral::parse("E")));
  EXPECT_TRUE(cast<Pi>(ILiteral::parse("Pi")));
  EXPECT_TRUE(cast<Variable>(ILiteral::parse("a")));
  EXPECT_TRUE(cast<Variable>(ILiteral::parse("z")));
  EXPECT_TRUE(cast<True>(ILiteral::parse("True")));
  EXPECT_TRUE(cast<False>(ILiteral::parse("False")));

  EXPECT_EQ(ILiteral::parse("1"), nullptr);
  EXPECT_EQ(ILiteral::parse("a_"), nullptr);
  EXPECT_EQ(ILiteral::parse("a1"), nullptr);
  EXPECT_EQ(ILiteral::parse("aa"), nullptr);
}

TEST(ParserTests, parseOperatorTest) {
  EXPECT_TRUE(cast<Add>(IOperator::parse("+", IOperator::Priority::Addition)));
  EXPECT_TRUE(cast<UnaryPlus>(IOperator::parse("+", IOperator::Priority::PrefixUnary)));
  EXPECT_TRUE(cast<Sub>(IOperator::parse("-", IOperator::Priority::Addition)));
  EXPECT_TRUE(cast<Neg>(IOperator::parse("-", IOperator::Priority::PrefixUnary)));
  EXPECT_TRUE(cast<Mul>(IOperator::parse("*")));
  EXPECT_TRUE(cast<Div>(IOperator::parse("/")));
  EXPECT_TRUE(cast<Pow>(IOperator::parse("^")));
  EXPECT_TRUE(cast<Percent>(IOperator::parse("%")));
  EXPECT_TRUE(cast<Factorial>(IOperator::parse("!")));
  EXPECT_TRUE(cast<Eqv>(IOperator::parse("=")));
  EXPECT_TRUE(cast<Neqv>(IOperator::parse("!=")));
  EXPECT_TRUE(cast<Less>(IOperator::parse("<")));
  EXPECT_TRUE(cast<More>(IOperator::parse(">")));
  EXPECT_TRUE(cast<LessEqv>(IOperator::parse("<=")));
  EXPECT_TRUE(cast<MoreEqv>(IOperator::parse(">=")));
  EXPECT_TRUE(cast<Derivative>(IOperator::parse("'")));
  EXPECT_TRUE(cast<Not>(IOperator::parse("!", IOperator::Priority::PrefixUnary)));
  EXPECT_TRUE(cast<And>(IOperator::parse("&&")));
  EXPECT_TRUE(cast<Or>(IOperator::parse("||")));
  EXPECT_TRUE(cast<Impl>(IOperator::parse("->")));
  EXPECT_TRUE(cast<Equiv>(IOperator::parse("<->")));
  EXPECT_TRUE(cast<Nequiv>(IOperator::parse("!<->")));

  EXPECT_EQ(IOperator::parse("asdgewfe"), nullptr);
  EXPECT_EQ(IOperator::parse("1224"), nullptr);
}

TEST(ParserTests, parseFunctionTest) {
  EXPECT_TRUE(cast<Add>(IFunction::parse("+", IFunction::Type::Binary)));
  EXPECT_TRUE(cast<UnaryPlus>(IFunction::parse("+", IFunction::Type::Unary)));
  EXPECT_TRUE(cast<Sub>(IFunction::parse("-", IFunction::Type::Binary)));
  EXPECT_TRUE(cast<Neg>(IFunction::parse("-", IFunction::Type::Unary)));
  EXPECT_TRUE(cast<Mul>(IFunction::parse("*")));
  EXPECT_TRUE(cast<Div>(IFunction::parse("/")));
  EXPECT_TRUE(cast<Pow>(IFunction::parse("^")));
  EXPECT_TRUE(cast<Percent>(IFunction::parse("%")));
  EXPECT_TRUE(cast<Factorial>(IFunction::parse("!")));
  EXPECT_TRUE(cast<Eqv>(IFunction::parse("=")));
  EXPECT_TRUE(cast<Neqv>(IFunction::parse("!=")));
  EXPECT_TRUE(cast<Less>(IFunction::parse("<")));
  EXPECT_TRUE(cast<More>(IFunction::parse(">")));
  EXPECT_TRUE(cast<LessEqv>(IFunction::parse("<=")));
  EXPECT_TRUE(cast<MoreEqv>(IFunction::parse(">=")));
  EXPECT_TRUE(cast<Derivative>(IFunction::parse("'")));
  EXPECT_TRUE(cast<Sqrt>(IFunction::parse("sqrt")));
  EXPECT_TRUE(cast<Exp>(IFunction::parse("exp")));
  EXPECT_TRUE(cast<Log>(IFunction::parse("log")));
  EXPECT_TRUE(cast<Ln>(IFunction::parse("ln")));
  EXPECT_TRUE(cast<Lb>(IFunction::parse("lb")));
  EXPECT_TRUE(cast<Lg>(IFunction::parse("lg")));
  EXPECT_TRUE(cast<Sin>(IFunction::parse("sin")));
  EXPECT_TRUE(cast<Cos>(IFunction::parse("cos")));
  EXPECT_TRUE(cast<Tan>(IFunction::parse("tan")));
  EXPECT_TRUE(cast<Cot>(IFunction::parse("cot")));
  EXPECT_TRUE(cast<Asin>(IFunction::parse("asin")));
  EXPECT_TRUE(cast<Acos>(IFunction::parse("acos")));
  EXPECT_TRUE(cast<Atan>(IFunction::parse("atan")));
  EXPECT_TRUE(cast<Acot>(IFunction::parse("acot")));
  EXPECT_TRUE(cast<Abs>(IFunction::parse("abs")));
  EXPECT_TRUE(cast<And>(IFunction::parse("&&")));
  EXPECT_TRUE(cast<Or>(IFunction::parse("||")));
  EXPECT_TRUE(cast<Impl>(IFunction::parse("->")));
  EXPECT_TRUE(cast<Equiv>(IFunction::parse("<->")));
  EXPECT_TRUE(cast<Nequiv>(IFunction::parse("!<->")));

  EXPECT_EQ(IFunction::parse("asdgewfe"), nullptr);
  EXPECT_EQ(IFunction::parse("1224"), nullptr);
}
