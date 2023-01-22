#include <gtest/gtest.h>

#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
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
  EXPECT_TRUE(INumber::parse("1231412736218731623872183")->instanceof<Integer>());

  EXPECT_EQ(INumber::parse("-1231412736218731623872183")->toString(), "-1231412736218731623872183");
  EXPECT_TRUE(INumber::parse("-1231412736218731623872183")->instanceof<Integer>());

  EXPECT_EQ(INumber::parse("0")->toString(), "0");
  EXPECT_TRUE(INumber::parse("0")->instanceof<Integer>());

  EXPECT_EQ(INumber::parse("0.1")->toString(), "1/10");
  EXPECT_TRUE(INumber::parse("0.1")->instanceof<Rational>());

  EXPECT_EQ(INumber::parse(".1")->toString(), "1/10");
  EXPECT_TRUE(INumber::parse(".1")->instanceof<Rational>());

  EXPECT_EQ(INumber::parse("1.")->toString(), "1");
  EXPECT_TRUE(INumber::parse("1.")->instanceof<Rational>());

  EXPECT_EQ(INumber::parse("12323231498721983.12323432432")->toString(), "77020196867012394520214527/6250000000");
  EXPECT_TRUE(INumber::parse("12323231498721983.12323432432")->instanceof<Rational>());

  EXPECT_EQ(INumber::parse("-12323231498721983.12323432432")->toString(), "-77020196867012394520214527/6250000000");
  EXPECT_TRUE(INumber::parse("-12323231498721983.12323432432")->instanceof<Rational>());

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
  EXPECT_TRUE(IConstant::parse("e")->instanceof<E>());
  EXPECT_TRUE(IConstant::parse("pi")->instanceof<Pi>());

  EXPECT_EQ(IConstant::parse("a"), nullptr);
  EXPECT_EQ(IConstant::parse("z"), nullptr);
  EXPECT_EQ(IConstant::parse("1"), nullptr);
  EXPECT_EQ(IConstant::parse("a_"), nullptr);
  EXPECT_EQ(IConstant::parse("a1"), nullptr);
  EXPECT_EQ(IConstant::parse("aa"), nullptr);
}

TEST(ParserTests, parseLiteralTest) {
  EXPECT_TRUE(ILiteral::parse("e")->instanceof<E>());
  EXPECT_TRUE(ILiteral::parse("pi")->instanceof<Pi>());
  EXPECT_TRUE(ILiteral::parse("a")->instanceof<Variable>());
  EXPECT_TRUE(ILiteral::parse("z")->instanceof<Variable>());
  EXPECT_TRUE(ILiteral::parse("true")->instanceof<True>());
  EXPECT_TRUE(ILiteral::parse("false")->instanceof<False>());

  EXPECT_EQ(ILiteral::parse("1"), nullptr);
  EXPECT_EQ(ILiteral::parse("a_"), nullptr);
  EXPECT_EQ(ILiteral::parse("a1"), nullptr);
  EXPECT_EQ(ILiteral::parse("aa"), nullptr);
}

TEST(ParserTests, parseOperatorTest) {
  EXPECT_TRUE(IOperator::parse("+", IOperator::Priority::Addition)->instanceof<Add>());
  EXPECT_TRUE(IOperator::parse("+", IOperator::Priority::PrefixUnary)->instanceof<UnaryPlus>());
  EXPECT_TRUE(IOperator::parse("-", IOperator::Priority::Addition)->instanceof<Sub>());
  EXPECT_TRUE(IOperator::parse("-", IOperator::Priority::PrefixUnary)->instanceof<Neg>());
  EXPECT_TRUE(IOperator::parse("*")->instanceof<Mul>());
  EXPECT_TRUE(IOperator::parse("/")->instanceof<Div>());
  EXPECT_TRUE(IOperator::parse("^")->instanceof<Pow>());
  EXPECT_TRUE(IOperator::parse("%")->instanceof<Percent>());
  EXPECT_TRUE(IOperator::parse("!")->instanceof<Factorial>());
  EXPECT_TRUE(IOperator::parse("=")->instanceof<Eqv>());
  EXPECT_TRUE(IOperator::parse("!=")->instanceof<Neqv>());
  EXPECT_TRUE(IOperator::parse("<")->instanceof<Less>());
  EXPECT_TRUE(IOperator::parse(">")->instanceof<More>());
  EXPECT_TRUE(IOperator::parse("<=")->instanceof<LessEqv>());
  EXPECT_TRUE(IOperator::parse(">=")->instanceof<MoreEqv>());
  EXPECT_TRUE(IOperator::parse("'")->instanceof<Derivative>());
  EXPECT_TRUE(IOperator::parse("!", IOperator::Priority::PrefixUnary)->instanceof<Not>());
  EXPECT_TRUE(IOperator::parse("&&")->instanceof<And>());
  EXPECT_TRUE(IOperator::parse("||")->instanceof<Or>());

  EXPECT_EQ(IOperator::parse("asdgewfe"), nullptr);
  EXPECT_EQ(IOperator::parse("1224"), nullptr);
}

TEST(ParserTests, parseFunctionTest) {
  EXPECT_TRUE(IFunction::parse("+", IFunction::Type::Binary)->instanceof<Add>());
  EXPECT_TRUE(IFunction::parse("+", IFunction::Type::Unary)->instanceof<UnaryPlus>());
  EXPECT_TRUE(IFunction::parse("-", IFunction::Type::Binary)->instanceof<Sub>());
  EXPECT_TRUE(IFunction::parse("-", IFunction::Type::Unary)->instanceof<Neg>());
  EXPECT_TRUE(IFunction::parse("*")->instanceof<Mul>());
  EXPECT_TRUE(IFunction::parse("/")->instanceof<Div>());
  EXPECT_TRUE(IFunction::parse("^")->instanceof<Pow>());
  EXPECT_TRUE(IFunction::parse("%")->instanceof<Percent>());
  EXPECT_TRUE(IFunction::parse("!")->instanceof<Factorial>());
  EXPECT_TRUE(IFunction::parse("=")->instanceof<Eqv>());
  EXPECT_TRUE(IFunction::parse("!=")->instanceof<Neqv>());
  EXPECT_TRUE(IFunction::parse("<")->instanceof<Less>());
  EXPECT_TRUE(IFunction::parse(">")->instanceof<More>());
  EXPECT_TRUE(IFunction::parse("<=")->instanceof<LessEqv>());
  EXPECT_TRUE(IFunction::parse(">=")->instanceof<MoreEqv>());
  EXPECT_TRUE(IFunction::parse("'")->instanceof<Derivative>());
  EXPECT_TRUE(IFunction::parse("sqrt")->instanceof<Sqrt>());
  EXPECT_TRUE(IFunction::parse("exp")->instanceof<Exp>());
  EXPECT_TRUE(IFunction::parse("log")->instanceof<Log>());
  EXPECT_TRUE(IFunction::parse("ln")->instanceof<Ln>());
  EXPECT_TRUE(IFunction::parse("lb")->instanceof<Lb>());
  EXPECT_TRUE(IFunction::parse("lg")->instanceof<Lg>());
  EXPECT_TRUE(IFunction::parse("sin")->instanceof<Sin>());
  EXPECT_TRUE(IFunction::parse("cos")->instanceof<Cos>());
  EXPECT_TRUE(IFunction::parse("tan")->instanceof<Tan>());
  EXPECT_TRUE(IFunction::parse("cot")->instanceof<Cot>());
  EXPECT_TRUE(IFunction::parse("asin")->instanceof<Asin>());
  EXPECT_TRUE(IFunction::parse("acos")->instanceof<Acos>());
  EXPECT_TRUE(IFunction::parse("atan")->instanceof<Atan>());
  EXPECT_TRUE(IFunction::parse("acot")->instanceof<Acot>());
  EXPECT_TRUE(IFunction::parse("abs")->instanceof<Abs>());
  EXPECT_TRUE(IFunction::parse("&&")->instanceof<And>());
  EXPECT_TRUE(IFunction::parse("||")->instanceof<Or>());

  EXPECT_EQ(IFunction::parse("asdgewfe"), nullptr);
  EXPECT_EQ(IFunction::parse("1224"), nullptr);
}
