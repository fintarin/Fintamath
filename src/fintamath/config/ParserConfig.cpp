#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"

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
#include "fintamath/functions/hyperbolic/Acosh.hpp"
#include "fintamath/functions/trigonometry/Acot.hpp"
#include "fintamath/functions/hyperbolic/Acoth.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"
#include "fintamath/functions/hyperbolic/Asinh.hpp"
#include "fintamath/functions/trigonometry/Atan.hpp"
#include "fintamath/functions/hyperbolic/Atanh.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/hyperbolic/Cosh.hpp"
#include "fintamath/functions/trigonometry/Cot.hpp"
#include "fintamath/functions/hyperbolic/Coth.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/functions/hyperbolic/Sinh.hpp"
#include "fintamath/functions/trigonometry/Tan.hpp"
#include "fintamath/functions/hyperbolic/Tanh.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/False.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/literals/constants/True.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

TokenVector Tokenizer::registeredTokens;
Parser::ParserVector<NumberPtr, std::string> INumber::parserVector;
Parser::ParserVector<LiteralPtr, std::string> ILiteral::parserVector;
Parser::ParserMap<ConstantPtr> IConstant::parserMap;
Parser::ParserMap<FunctionPtr> IFunction::parserMap;
Parser::ParserMap<OperatorPtr> IOperator::parserMap;

}

using namespace fintamath;

namespace {

struct ParserConfig {
  ParserConfig() {
    // numbers
    INumber::registerParser<Integer>();
    INumber::registerParser<Rational>();

    // constants
    IConstant::registerParser<E>();
    IConstant::registerParser<Pi>();
    IConstant::registerParser<True>();
    IConstant::registerParser<False>();

    // literals
    ILiteral::registerParser(&IConstant::parse);
    ILiteral::registerParser<Variable>();

    // operators
    IOperator::registerParser<Add>();
    IOperator::registerParser<Sub>();
    IOperator::registerParser<Mul>();
    IOperator::registerParser<Div>();
    IOperator::registerParser<Neg>();
    IOperator::registerParser<UnaryPlus>();
    IOperator::registerParser<Factorial>();
    IOperator::registerParser<Percent>();
    IOperator::registerParser<Pow>();
    IOperator::registerParser<Eqv>();
    IOperator::registerParser<Neqv>();
    IOperator::registerParser<Less>();
    IOperator::registerParser<More>();
    IOperator::registerParser<LessEqv>();
    IOperator::registerParser<MoreEqv>();
    IOperator::registerParser<Derivative>();
    IOperator::registerParser<Not>();
    IOperator::registerParser<And>();
    IOperator::registerParser<Or>();
    IOperator::registerParser<Impl>();
    IOperator::registerParser<Equiv>();
    IOperator::registerParser<Nequiv>();
    IOperator::registerParser<Index>();

    // functions
    IFunction::registerParser<Abs>();
    IFunction::registerParser<Log>();
    IFunction::registerParser<Ln>();
    IFunction::registerParser<Lb>();
    IFunction::registerParser<Lg>();
    IFunction::registerParser<Exp>();
    IFunction::registerParser<Sqrt>();
    IFunction::registerParser<Sin>();
    IFunction::registerParser<Cos>();
    IFunction::registerParser<Tan>();
    IFunction::registerParser<Cot>();
    IFunction::registerParser<Asin>();
    IFunction::registerParser<Acos>();
    IFunction::registerParser<Atan>();
    IFunction::registerParser<Acot>();
    IFunction::registerParser<Degrees>();
    IFunction::registerParser<Sign>();
    IFunction::registerParser<Sinh>();
    IFunction::registerParser<Cosh>();
    IFunction::registerParser<Tanh>();
    IFunction::registerParser<Coth>();
    IFunction::registerParser<Asinh>();
    IFunction::registerParser<Acosh>();
    IFunction::registerParser<Atanh>();
    IFunction::registerParser<Acoth>();
  }
};

const ParserConfig config;

}
