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
#include "fintamath/functions/arithmetic/Frac.hpp"
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
#include "fintamath/functions/ntheory/Ceil.hpp"
#include "fintamath/functions/ntheory/Floor.hpp"
#include "fintamath/functions/ntheory/Mod.hpp"
#include "fintamath/functions/other/Comma.hpp"
#include "fintamath/functions/other/Deg.hpp"
#include "fintamath/functions/other/Factorial.hpp"
#include "fintamath/functions/other/Index.hpp"
#include "fintamath/functions/other/Percent.hpp"
#include "fintamath/functions/powers/Exp.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/powers/PowFunction.hpp"
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
#include "fintamath/numbers/IInteger.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/parser/Parser.hpp"
#include "fintamath/parser/Tokenizer.hpp"

namespace fintamath {

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

    INumber::registerType<IInteger>(&IInteger::parse);
    INumber::registerType<Rational>();

    IInteger::registerType<Integer>();

    ILiteral::registerType<IConstant>(&IConstant::parse);
    ILiteral::registerType<Variable>();
    ILiteral::registerType<Boolean>();

    IConstant::registerType<E>();
    IConstant::registerType<Pi>();
    IConstant::registerType<True>();
    IConstant::registerType<False>();
    IConstant::registerType<I>();
    IConstant::registerType<Inf>();
    IConstant::registerType<NegInf>();
    IConstant::registerType<ComplexInf>();
    IConstant::registerType<Undefined>();

    IFunction::registerType<Abs>();
    IFunction::registerType<Log>();
    IFunction::registerType<Ln>();
    IFunction::registerType<Lb>();
    IFunction::registerType<Lg>();
    IFunction::registerType<Exp>();
    IFunction::registerType<Sqrt>();
    IFunction::registerType<Root>();
    IFunction::registerType<Sin>();
    IFunction::registerType<Cos>();
    IFunction::registerType<Tan>();
    IFunction::registerType<Cot>();
    IFunction::registerType<Sec>();
    IFunction::registerType<Csc>();
    IFunction::registerType<Asin>();
    IFunction::registerType<Acos>();
    IFunction::registerType<Atan>();
    IFunction::registerType<Acot>();
    IFunction::registerType<Asec>();
    IFunction::registerType<Acsc>();
    IFunction::registerType<Sign>();
    IFunction::registerType<Sinh>();
    IFunction::registerType<Cosh>();
    IFunction::registerType<Tanh>();
    IFunction::registerType<Coth>();
    IFunction::registerType<Sech>();
    IFunction::registerType<Csch>();
    IFunction::registerType<Asinh>();
    IFunction::registerType<Acosh>();
    IFunction::registerType<Atanh>();
    IFunction::registerType<Acoth>();
    IFunction::registerType<Asech>();
    IFunction::registerType<Acsch>();
    IFunction::registerType<Min>();
    IFunction::registerType<Max>();
    IFunction::registerType<Derivative>();
    IFunction::registerType<Integral>();
    IFunction::registerType<Frac>();
    IFunction::registerType<PowFunction>();
    IFunction::registerType<Floor>();
    IFunction::registerType<Ceil>();

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
    IOperator::registerType<Deg>();
    IOperator::registerType<Comma>();
    IOperator::registerType<Mod>();

    IExpression::registerType<Expression>();
  }
};

const ParserConfig config;

}
