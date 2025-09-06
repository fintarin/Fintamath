#include "fintamath/config/TypeConfig.hpp"

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/IMathObject.hpp"
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
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath::detail {

TypeConfig::TypeConfig() {
  IMathObject::registerType<IArithmetic>();
  // IMathObject::registerType<IFunction>();
  IMathObject::registerType<ILiteral>();
  // IMathObject::registerType<IExpression>();

  IArithmetic::registerType<IComparable>();

  IComparable::registerType<INumber>();

  INumber::registerType<Integer>();
  INumber::registerType<Rational>();
  INumber::registerType<Real>();
  // INumber::registerType<Complex>();

  ILiteral::registerType<IConstant>();
  ILiteral::registerType<Variable>();
  ILiteral::registerType<Boolean>();

  IConstant::registerType<E>();
  IConstant::registerType<Pi>();
  IConstant::registerType<True>();
  IConstant::registerType<False>();
  // IConstant::registerType<I>();
  IConstant::registerType<Inf>();
  IConstant::registerType<NegInf>();
  IConstant::registerType<ComplexInf>();
  IConstant::registerType<Undefined>();

  // IFunction::registerType<IOperator>();

  // IOperator::registerType<AddOper>();
  // IOperator::registerType<UnaryPlus>();
  // IOperator::registerType<Sub>();
  // IOperator::registerType<Neg>();
  // IOperator::registerType<MulOper>();
  // IOperator::registerType<Div>();
  // IOperator::registerType<Mod>();
  // IOperator::registerType<PowOper>();
  // IOperator::registerType<Factorial>();
  // IOperator::registerType<Percent>();
  // IOperator::registerType<Deg>();
  // IOperator::registerType<Index>();
  // IOperator::registerType<Comma>();
  // IOperator::registerType<Eqv>();
  // IOperator::registerType<Neqv>();
  // IOperator::registerType<Less>();
  // IOperator::registerType<More>();
  // IOperator::registerType<LessEqv>();
  // IOperator::registerType<MoreEqv>();
  // IOperator::registerType<Not>();
  // IOperator::registerType<AndOper>();
  // IOperator::registerType<OrOper>();
  // IOperator::registerType<Impl>();
  // IOperator::registerType<Equiv>();
  // IOperator::registerType<Nequiv>();

  // IFunction::registerType<Pow>();
  // IFunction::registerType<Add>();
  // IFunction::registerType<Mul>();
  // IFunction::registerType<Abs>();
  // IFunction::registerType<Log>();
  // IFunction::registerType<Ln>();
  // IFunction::registerType<Lb>();
  // IFunction::registerType<Lg>();
  // IFunction::registerType<Exp>();
  // IFunction::registerType<Sqr>();
  // IFunction::registerType<Sqrt>();
  // IFunction::registerType<Root>();
  // IFunction::registerType<Sin>();
  // IFunction::registerType<Cos>();
  // IFunction::registerType<Tan>();
  // IFunction::registerType<Cot>();
  // IFunction::registerType<Sec>();
  // IFunction::registerType<Csc>();
  // IFunction::registerType<Asin>();
  // IFunction::registerType<Acos>();
  // IFunction::registerType<Atan>();
  // IFunction::registerType<Acot>();
  // IFunction::registerType<Asec>();
  // IFunction::registerType<Acsc>();
  // IFunction::registerType<Sign>();
  // IFunction::registerType<Sinh>();
  // IFunction::registerType<Cosh>();
  // IFunction::registerType<Tanh>();
  // IFunction::registerType<Coth>();
  // IFunction::registerType<Sech>();
  // IFunction::registerType<Csch>();
  // IFunction::registerType<Asinh>();
  // IFunction::registerType<Acosh>();
  // IFunction::registerType<Atanh>();
  // IFunction::registerType<Acoth>();
  // IFunction::registerType<Asech>();
  // IFunction::registerType<Acsch>();
  // IFunction::registerType<Min>();
  // IFunction::registerType<Max>();
  // IFunction::registerType<Derivative>();
  // IFunction::registerType<Integral>();
  // IFunction::registerType<Frac>();
  // IFunction::registerType<FracMixed>();
  // IFunction::registerType<Floor>();
  // IFunction::registerType<Ceil>();
  // IFunction::registerType<And>();
  // IFunction::registerType<Or>();

  // IExpression::registerType<IPolynomExpression>();
  // IExpression::registerType<IBinaryExpression>();
  // IExpression::registerType<IUnaryExpression>();
  // IExpression::registerType<FunctionExpression>();
  // IExpression::registerType<Expression>();

  // IPolynomExpression::registerType<AddExpr>();
  // IPolynomExpression::registerType<MulExpr>();
  // IPolynomExpression::registerType<MinMaxExpr>();
  // IPolynomExpression::registerType<AndExpr>();
  // IPolynomExpression::registerType<OrExpr>();

  // IBinaryExpression::registerType<DivExpr>();
  // IBinaryExpression::registerType<PowExpr>();
  // IBinaryExpression::registerType<LogExpr>();
  // IBinaryExpression::registerType<DerivativeExpr>();
  // IBinaryExpression::registerType<IntegralExpr>();
  // IBinaryExpression::registerType<CompExpr>();

  // IUnaryExpression::registerType<AbsExpr>();
  // IUnaryExpression::registerType<SignExpr>();
  // IUnaryExpression::registerType<FloorCeilExpr>();
  // IUnaryExpression::registerType<TrigExpr>();
  // IUnaryExpression::registerType<InvTrigExpr>();
  // IUnaryExpression::registerType<HyperbExpr>();
  // IUnaryExpression::registerType<InvHyperbExpr>();
  // IUnaryExpression::registerType<NotExpr>();
}

}
