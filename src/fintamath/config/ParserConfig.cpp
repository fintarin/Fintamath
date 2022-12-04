#include "fintamath/config/ParserConfig.hpp"

#include "fintamath/core/Defines.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/AddExpression.hpp"
#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/functions/comparison/Less.hpp"
#include "fintamath/functions/comparison/LessEqv.hpp"
#include "fintamath/functions/comparison/More.hpp"
#include "fintamath/functions/comparison/MoreEqv.hpp"
#include "fintamath/functions/factorials/DoubleFactorial.hpp"
#include "fintamath/functions/factorials/Factorial.hpp"
#include "fintamath/functions/logarithms/Lb.hpp"
#include "fintamath/functions/logarithms/Lg.hpp"
#include "fintamath/functions/logarithms/Ln.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"
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
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {
  helpers::ParserVector<NumberPtr, std::string> INumber::parserVector;
  helpers::ParserVector<LiteralPtr, std::string> ILiteral::parserVector;

  helpers::ParserVector<ExpressionPtr, TokenVector> IExpression::parserMap;

  helpers::ParserMap<ConstantPtr> IConstant::parserMap;
  helpers::ParserMap<FunctionPtr> IFunction::parserMap;
  helpers::ParserMap<OperatorPtr> IOperator::parserMap;
}

namespace fintamath::config {
  ParserConfig::ParserConfig() {
    // numbers
    INumber::addParser<Integer>();
    INumber::addParser<Rational>();

    // constants
    IConstant::addParser<E>();
    IConstant::addParser<Pi>();

    // literals
    ILiteral::addParser(&IConstant::parse);
    ILiteral::addParser<Variable>();
    ILiteral::addParser<Boolean>();

    // operators
    IOperator::addParser<Add>();
    IOperator::addParser<Sub>();
    IOperator::addParser<Mul>();
    IOperator::addParser<Div>();
    IOperator::addParser<Neg>();
    IOperator::addParser<UnaryPlus>();
    IOperator::addParser<Factorial>();
    IOperator::addParser<DoubleFactorial>();
    IOperator::addParser<Percent>();
    IOperator::addParser<Pow>();
    IOperator::addParser<Eqv>();
    IOperator::addParser<Less>();
    IOperator::addParser<More>();
    IOperator::addParser<LessEqv>();
    IOperator::addParser<MoreEqv>();

    // functions
    IFunction::addParser<Abs>();
    IFunction::addParser<Log>();
    IFunction::addParser<Ln>();
    IFunction::addParser<Lb>();
    IFunction::addParser<Lg>();
    IFunction::addParser<Exp>();
    IFunction::addParser<Sqrt>();
    IFunction::addParser<Sin>();
    IFunction::addParser<Cos>();
    IFunction::addParser<Tan>();
    IFunction::addParser<Cot>();
    IFunction::addParser<Asin>();
    IFunction::addParser<Acos>();
    IFunction::addParser<Atan>();
    IFunction::addParser<Acot>();

    //expressions
    IExpression::addParser<AddExpression>();
    IExpression::addParser<MulExpression>();
    IExpression::addParser<Expression>();

  }

  static const ParserConfig config;
}
