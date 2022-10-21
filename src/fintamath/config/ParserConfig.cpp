#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/functions/factorials/DoubleFactorial.hpp"
#include "fintamath/functions/factorials/Factorial.hpp"
#include "fintamath/functions/logarithms/Lb.hpp"
#include "fintamath/functions/logarithms/Lg.hpp"
#include "fintamath/functions/logarithms/Ln.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/logic/Eq.hpp"
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
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {
  helpers::ParserVector<NumberPtr> INumber::parserMap;
  helpers::ParserVector<LiteralPtr> ILiteral::parserMap;
  helpers::ParserMap<ConstantPtr> IConstant::parserMap;
  helpers::ParserMap<FunctionPtr> IFunction::parserMap;
  helpers::ParserMap<OperatorPtr> IOperator::parserMap;
}

namespace {
  using namespace fintamath;

  // numbers
  bool integer = INumber::addParser<Integer>();
  bool rational = INumber::addParser<Rational>();

  // constants
  bool e = IConstant::addParser<E>();
  bool pi = IConstant::addParser<Pi>();

  // literals
  bool constant = ILiteral::addParser(&IConstant::parse);
  bool variable = ILiteral::addParser<Variable>();

  // operators
  bool add = IOperator::addParser<Add>();
  bool sub = IOperator::addParser<Sub>();
  bool mul = IOperator::addParser<Mul>();
  bool div = IOperator::addParser<Div>();
  bool neg = IOperator::addParser<Neg>();
  bool unaryPlus = IOperator::addParser<UnaryPlus>();
  bool factorial = IOperator::addParser<Factorial>();
  bool doubleFactorial = IOperator::addParser<DoubleFactorial>();
  bool percent = IOperator::addParser<Percent>();
  bool pow = IOperator::addParser<Pow>();
  bool eq = IOperator::addParser<Eq>();

  // functions
  bool abs = IFunction::addParser<Abs>();
  bool log = IFunction::addParser<Log>();
  bool ln = IFunction::addParser<Ln>();
  bool lb = IFunction::addParser<Lb>();
  bool lg = IFunction::addParser<Lg>();
  bool exp = IFunction::addParser<Exp>();
  bool sqrt = IFunction::addParser<Sqrt>();
  bool sin = IFunction::addParser<Sin>();
  bool cos = IFunction::addParser<Cos>();
  bool tan = IFunction::addParser<Tan>();
  bool cot = IFunction::addParser<Cot>();
  bool asin = IFunction::addParser<Asin>();
  bool acos = IFunction::addParser<Acos>();
  bool atan = IFunction::addParser<Atan>();
  bool acot = IFunction::addParser<Acot>();
}
