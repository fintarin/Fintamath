#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Abs.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sign.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
#include "fintamath/functions/calculus/Integral.hpp"
#include "fintamath/functions/calculus/Max.hpp"
#include "fintamath/functions/calculus/Min.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/functions/comparison/Less.hpp"
#include "fintamath/functions/comparison/LessEqv.hpp"
#include "fintamath/functions/comparison/More.hpp"
#include "fintamath/functions/comparison/MoreEqv.hpp"
#include "fintamath/functions/comparison/Neqv.hpp"
#include "fintamath/functions/hyperbolic/Acosh.hpp"
#include "fintamath/functions/hyperbolic/Acoth.hpp"
#include "fintamath/functions/hyperbolic/Asinh.hpp"
#include "fintamath/functions/hyperbolic/Atanh.hpp"
#include "fintamath/functions/hyperbolic/Cosh.hpp"
#include "fintamath/functions/hyperbolic/Coth.hpp"
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
#include "fintamath/functions/other/Angle.hpp"
#include "fintamath/functions/other/Degrees.hpp"
#include "fintamath/functions/other/Factorial.hpp"
#include "fintamath/functions/other/Index.hpp"
#include "fintamath/functions/other/Percent.hpp"
#include "fintamath/functions/other/Rad.hpp"
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
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/False.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/literals/constants/True.hpp"
#include "fintamath/meta/InheritanceTable.hpp"
#include "fintamath/numbers/IInteger.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/parser/Parser.hpp"
#include "fintamath/parser/Tokenizer.hpp"

namespace fintamath {

std::multimap<TypeInfo, TypeInfo> &InheritanceTable::getTable() {
  static std::multimap<TypeInfo, TypeInfo> table;
  return table;
}

TokenVector &Tokenizer::getRegisteredTokens() {
  static TokenVector registeredTokens;
  return registeredTokens;
}

Parser::Vector<std::unique_ptr<IMathObject>, const std::string &> &IMathObject::getParser() {
  static Parser::Vector<std::unique_ptr<IMathObject>, const std::string &> parser;
  return parser;
}

Parser::Vector<std::unique_ptr<IArithmetic>, const std::string &> &IArithmetic::getParser() {
  static Parser::Vector<std::unique_ptr<IArithmetic>, const std::string &> parser;
  return parser;
}

Parser::Vector<std::unique_ptr<IComparable>, const std::string &> &IComparable::getParser() {
  static Parser::Vector<std::unique_ptr<IComparable>, const std::string &> parser;
  return parser;
}

Parser::Vector<std::unique_ptr<INumber>, const std::string &> &INumber::getParser() {
  static Parser::Vector<std::unique_ptr<INumber>, const std::string &> parser;
  return parser;
}

Parser::Vector<std::unique_ptr<IInteger>, const std::string &> &IInteger::getParser() {
  static Parser::Vector<std::unique_ptr<IInteger>, const std::string &> parser;
  return parser;
}

Parser::Vector<std::unique_ptr<ILiteral>, const std::string &> &ILiteral::getParser() {
  static Parser::Vector<std::unique_ptr<ILiteral>, const std::string &> parser;
  return parser;
}

Parser::Map<std::unique_ptr<IConstant>> &IConstant::getParser() {
  static Parser::Map<std::unique_ptr<IConstant>> parser;
  return parser;
}

Parser::Map<std::unique_ptr<IFunction>> &IFunction::getParser() {
  static Parser::Map<std::unique_ptr<IFunction>> parser;
  return parser;
}

Parser::Map<std::unique_ptr<IOperator>> &IOperator::getParser() {
  static Parser::Map<std::unique_ptr<IOperator>> parser;
  return parser;
}

Parser::Vector<std::unique_ptr<IExpression>, const std::string &> &IExpression::getParser() {
  static Parser::Vector<std::unique_ptr<IExpression>, const std::string &> parser;
  return parser;
}

}

using namespace fintamath;

namespace {

struct ParserConfig {
  ParserConfig() {
    IMathObject::registerType<ILiteral>(&ILiteral::parse);
    IMathObject::registerType<IFunction>([](const std::string &str) {
      return IFunction::parse(str);
    });
    IMathObject::registerType<IArithmetic>(&IArithmetic::parse);

    IArithmetic::registerType<IComparable>(&IComparable::parse);
    IArithmetic::registerType<Expression>();

    IComparable::registerType<INumber>(&INumber::parse);

    IInteger::registerType<Integer>();

    INumber::registerType<IInteger>(&IInteger::parse);
    INumber::registerType<Rational>();
    INumber::registerType<Real>();

    IInteger::registerType<Integer>();

    ILiteral::registerType<IConstant>(&IConstant::parse);
    ILiteral::registerType<Variable>();
    ILiteral::registerType<Boolean>();

    IConstant::registerType<E>();
    IConstant::registerType<Pi>();
    IConstant::registerType<True>();
    IConstant::registerType<False>();

    IFunction::registerType<Abs>();
    IFunction::registerType<Log>();
    IFunction::registerType<Ln>();
    IFunction::registerType<Lb>();
    IFunction::registerType<Lg>();
    IFunction::registerType<Exp>();
    IFunction::registerType<Sqrt>();
    IFunction::registerType<Sin>();
    IFunction::registerType<Cos>();
    IFunction::registerType<Tan>();
    IFunction::registerType<Cot>();
    IFunction::registerType<Asin>();
    IFunction::registerType<Acos>();
    IFunction::registerType<Atan>();
    IFunction::registerType<Acot>();
    IFunction::registerType<Degrees>();
    IFunction::registerType<Rad>();
    IFunction::registerType<Sign>();
    IFunction::registerType<Sinh>();
    IFunction::registerType<Cosh>();
    IFunction::registerType<Tanh>();
    IFunction::registerType<Coth>();
    IFunction::registerType<Asinh>();
    IFunction::registerType<Acosh>();
    IFunction::registerType<Atanh>();
    IFunction::registerType<Acoth>();
    IFunction::registerType<Min>();
    IFunction::registerType<Max>();
    IFunction::registerType<Derivative>();
    IFunction::registerType<Integral>();

    IOperator::registerType<Add>();
    IOperator::registerType<Sub>();
    IOperator::registerType<Mul>();
    IOperator::registerType<Div>();
    IOperator::registerType<Neg>();
    IOperator::registerType<UnaryPlus>();
    IOperator::registerType<Factorial>();
    IOperator::registerType<Percent>();
    IOperator::registerType<Pow>();
    IOperator::registerType<Eqv>();
    IOperator::registerType<Neqv>();
    IOperator::registerType<Less>();
    IOperator::registerType<More>();
    IOperator::registerType<LessEqv>();
    IOperator::registerType<MoreEqv>();
    IOperator::registerType<Not>();
    IOperator::registerType<And>();
    IOperator::registerType<Or>();
    IOperator::registerType<Impl>();
    IOperator::registerType<Equiv>();
    IOperator::registerType<Nequiv>();
    IOperator::registerType<Index>();
    IOperator::registerType<Angle>();

    IExpression::registerType<Expression>();
  }
};

const ParserConfig config;

}
