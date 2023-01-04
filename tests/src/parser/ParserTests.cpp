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
#include "fintamath/functions/calculus/Derivate.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/functions/comparison/Less.hpp"
#include "fintamath/functions/comparison/LessEqv.hpp"
#include "fintamath/functions/comparison/More.hpp"
#include "fintamath/functions/comparison/MoreEqv.hpp"
#include "fintamath/functions/comparison/Neqv.hpp"
#include "fintamath/functions/factorials/DoubleFactorial.hpp"
#include "fintamath/functions/factorials/Factorial.hpp"
#include "fintamath/functions/logarithms/Lb.hpp"
#include "fintamath/functions/logarithms/Lg.hpp"
#include "fintamath/functions/logarithms/Ln.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"
#include "fintamath/functions/other/Abs.hpp"
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
  EXPECT_TRUE(INumber::parse("1231412736218731623872183")->is<Integer>());

  EXPECT_EQ(INumber::parse("-1231412736218731623872183")->toString(), "-1231412736218731623872183");
  EXPECT_TRUE(INumber::parse("-1231412736218731623872183")->is<Integer>());

  EXPECT_EQ(INumber::parse("0")->toString(), "0");
  EXPECT_TRUE(INumber::parse("0")->is<Integer>());

  EXPECT_EQ(INumber::parse("0.1")->toString(), "1/10");
  EXPECT_TRUE(INumber::parse("0.1")->is<Rational>());

  EXPECT_EQ(INumber::parse(".1")->toString(), "1/10");
  EXPECT_TRUE(INumber::parse(".1")->is<Rational>());

  EXPECT_EQ(INumber::parse("1.")->toString(), "1");
  EXPECT_TRUE(INumber::parse("1.")->is<Rational>());

  EXPECT_EQ(INumber::parse("12323231498721983.12323432432")->toString(), "77020196867012394520214527/6250000000");
  EXPECT_TRUE(INumber::parse("12323231498721983.12323432432")->is<Rational>());

  EXPECT_EQ(INumber::parse("-12323231498721983.12323432432")->toString(), "-77020196867012394520214527/6250000000");
  EXPECT_TRUE(INumber::parse("-12323231498721983.12323432432")->is<Rational>());

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
  EXPECT_TRUE(IConstant::parse("e")->is<E>());
  EXPECT_TRUE(IConstant::parse("pi")->is<Pi>());

  EXPECT_EQ(IConstant::parse("a"), nullptr);
  EXPECT_EQ(IConstant::parse("z"), nullptr);
  EXPECT_EQ(IConstant::parse("1"), nullptr);
  EXPECT_EQ(IConstant::parse("a_"), nullptr);
  EXPECT_EQ(IConstant::parse("a1"), nullptr);
  EXPECT_EQ(IConstant::parse("aa"), nullptr);
}

TEST(ParserTests, parseLiteralTest) {
  EXPECT_TRUE(ILiteral::parse("e")->is<E>());
  EXPECT_TRUE(ILiteral::parse("pi")->is<Pi>());
  EXPECT_TRUE(ILiteral::parse("a")->is<Variable>());
  EXPECT_TRUE(ILiteral::parse("z")->is<Variable>());
  EXPECT_TRUE(ILiteral::parse("true")->is<True>());
  EXPECT_TRUE(ILiteral::parse("false")->is<False>());

  EXPECT_EQ(ILiteral::parse("1"), nullptr);
  EXPECT_EQ(ILiteral::parse("a_"), nullptr);
  EXPECT_EQ(ILiteral::parse("a1"), nullptr);
  EXPECT_EQ(ILiteral::parse("aa"), nullptr);
}

TEST(ParserTests, parseOperatorTest) {
  EXPECT_TRUE(IOperator::parse("+", IOperator::Priority::Addition)->is<Add>());
  EXPECT_TRUE(IOperator::parse("+", IOperator::Priority::PrefixUnary)->is<UnaryPlus>());
  EXPECT_TRUE(IOperator::parse("-", IOperator::Priority::Addition)->is<Sub>());
  EXPECT_TRUE(IOperator::parse("-", IOperator::Priority::PrefixUnary)->is<Neg>());
  EXPECT_TRUE(IOperator::parse("*")->is<Mul>());
  EXPECT_TRUE(IOperator::parse("/")->is<Div>());
  EXPECT_TRUE(IOperator::parse("^")->is<Pow>());
  EXPECT_TRUE(IOperator::parse("%")->is<Percent>());
  EXPECT_TRUE(IOperator::parse("!")->is<Factorial>());
  EXPECT_TRUE(IOperator::parse("!!")->is<DoubleFactorial>());
  EXPECT_TRUE(IOperator::parse("=")->is<Eqv>());
  EXPECT_TRUE(IOperator::parse("!=")->is<Neqv>());
  EXPECT_TRUE(IOperator::parse("<")->is<Less>());
  EXPECT_TRUE(IOperator::parse(">")->is<More>());
  EXPECT_TRUE(IOperator::parse("<=")->is<LessEqv>());
  EXPECT_TRUE(IOperator::parse(">=")->is<MoreEqv>());
  EXPECT_TRUE(IOperator::parse("'")->is<Derivate>());
  EXPECT_TRUE(IOperator::parse("!", IOperator::Priority::PrefixUnary)->is<Not>());
  EXPECT_TRUE(IOperator::parse("&&")->is<And>());
  EXPECT_TRUE(IOperator::parse("||")->is<Or>());

  EXPECT_EQ(IOperator::parse("asdgewfe"), nullptr);
  EXPECT_EQ(IOperator::parse("1224"), nullptr);
}

TEST(ParserTests, parseFunctionTest) {
  EXPECT_TRUE(IFunction::parse("+", IFunction::Type::Binary)->is<Add>());
  EXPECT_TRUE(IFunction::parse("+", IFunction::Type::Unary)->is<UnaryPlus>());
  EXPECT_TRUE(IFunction::parse("-", IFunction::Type::Binary)->is<Sub>());
  EXPECT_TRUE(IFunction::parse("-", IFunction::Type::Unary)->is<Neg>());
  EXPECT_TRUE(IFunction::parse("*")->is<Mul>());
  EXPECT_TRUE(IFunction::parse("/")->is<Div>());
  EXPECT_TRUE(IFunction::parse("^")->is<Pow>());
  EXPECT_TRUE(IFunction::parse("%")->is<Percent>());
  EXPECT_TRUE(IFunction::parse("!")->is<Factorial>());
  EXPECT_TRUE(IFunction::parse("!!")->is<DoubleFactorial>());
  EXPECT_TRUE(IFunction::parse("=")->is<Eqv>());
  EXPECT_TRUE(IFunction::parse("!=")->is<Neqv>());
  EXPECT_TRUE(IFunction::parse("<")->is<Less>());
  EXPECT_TRUE(IFunction::parse(">")->is<More>());
  EXPECT_TRUE(IFunction::parse("<=")->is<LessEqv>());
  EXPECT_TRUE(IFunction::parse(">=")->is<MoreEqv>());
  EXPECT_TRUE(IFunction::parse("'")->is<Derivate>());
  EXPECT_TRUE(IFunction::parse("sqrt")->is<Sqrt>());
  EXPECT_TRUE(IFunction::parse("exp")->is<Exp>());
  EXPECT_TRUE(IFunction::parse("log")->is<Log>());
  EXPECT_TRUE(IFunction::parse("ln")->is<Ln>());
  EXPECT_TRUE(IFunction::parse("lb")->is<Lb>());
  EXPECT_TRUE(IFunction::parse("lg")->is<Lg>());
  EXPECT_TRUE(IFunction::parse("sin")->is<Sin>());
  EXPECT_TRUE(IFunction::parse("cos")->is<Cos>());
  EXPECT_TRUE(IFunction::parse("tan")->is<Tan>());
  EXPECT_TRUE(IFunction::parse("cot")->is<Cot>());
  EXPECT_TRUE(IFunction::parse("asin")->is<Asin>());
  EXPECT_TRUE(IFunction::parse("acos")->is<Acos>());
  EXPECT_TRUE(IFunction::parse("atan")->is<Atan>());
  EXPECT_TRUE(IFunction::parse("acot")->is<Acot>());
  EXPECT_TRUE(IFunction::parse("abs")->is<Abs>());
  EXPECT_TRUE(IFunction::parse("&&")->is<And>());
  EXPECT_TRUE(IFunction::parse("||")->is<Or>());

  EXPECT_EQ(IFunction::parse("asdgewfe"), nullptr);
  EXPECT_EQ(IFunction::parse("1224"), nullptr);
}
