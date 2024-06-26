#include "fintamath/config/TypeConfig.hpp"

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/FunctionExpression.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/binary/CompExpr.hpp"
#include "fintamath/expressions/binary/DerivativeExpr.hpp"
#include "fintamath/expressions/binary/DivExpr.hpp"
#include "fintamath/expressions/binary/IntegralExpr.hpp"
#include "fintamath/expressions/binary/LogExpr.hpp"
#include "fintamath/expressions/binary/PowExpr.hpp"
#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/expressions/polynomial/AddExpr.hpp"
#include "fintamath/expressions/polynomial/AndExpr.hpp"
#include "fintamath/expressions/polynomial/MinMaxExpr.hpp"
#include "fintamath/expressions/polynomial/MulExpr.hpp"
#include "fintamath/expressions/polynomial/OrExpr.hpp"
#include "fintamath/expressions/unary/AbsExpr.hpp"
#include "fintamath/expressions/unary/FloorCeilExpr.hpp"
#include "fintamath/expressions/unary/HyperbExpr.hpp"
#include "fintamath/expressions/unary/InvHyperbExpr.hpp"
#include "fintamath/expressions/unary/InvTrigExpr.hpp"
#include "fintamath/expressions/unary/NotExpr.hpp"
#include "fintamath/expressions/unary/SignExpr.hpp"
#include "fintamath/expressions/unary/TrigExpr.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Abs.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/AddOper.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Frac.hpp"
#include "fintamath/functions/arithmetic/FracMixed.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/MulOper.hpp"
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
#include "fintamath/functions/logic/AndOper.hpp"
#include "fintamath/functions/logic/Equiv.hpp"
#include "fintamath/functions/logic/Impl.hpp"
#include "fintamath/functions/logic/Nequiv.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"
#include "fintamath/functions/logic/OrOper.hpp"
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
#include "fintamath/functions/powers/PowOper.hpp"
#include "fintamath/functions/powers/Root.hpp"
#include "fintamath/functions/powers/Sqr.hpp"
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
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath::detail {

TypeConfig::TypeConfig() {
  IMathObject::registerType<IArithmetic>();
  IMathObject::registerType<IFunction>();
  IMathObject::registerType<ILiteral>();
  IMathObject::registerType<IExpression>();

  IArithmetic::registerType<IComparable>();

  IComparable::registerType<INumber>();

  INumber::registerType<Integer>();
  INumber::registerType<Rational>();
  INumber::registerType<Real>();
  INumber::registerType<Complex>();

  ILiteral::registerType<IConstant>();
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

  IFunction::registerType<IOperator>();

  IOperator::registerType<AddOper>();
  IOperator::registerType<UnaryPlus>();
  IOperator::registerType<Sub>();
  IOperator::registerType<Neg>();
  IOperator::registerType<MulOper>();
  IOperator::registerType<Div>();
  IOperator::registerType<Mod>();
  IOperator::registerType<PowOper>();
  IOperator::registerType<Factorial>();
  IOperator::registerType<Percent>();
  IOperator::registerType<Deg>();
  IOperator::registerType<Index>();
  IOperator::registerType<Comma>();
  IOperator::registerType<Eqv>();
  IOperator::registerType<Neqv>();
  IOperator::registerType<Less>();
  IOperator::registerType<More>();
  IOperator::registerType<LessEqv>();
  IOperator::registerType<MoreEqv>();
  IOperator::registerType<Not>();
  IOperator::registerType<AndOper>();
  IOperator::registerType<OrOper>();
  IOperator::registerType<Impl>();
  IOperator::registerType<Equiv>();
  IOperator::registerType<Nequiv>();

  IFunction::registerType<Pow>();
  IFunction::registerType<Add>();
  IFunction::registerType<Mul>();
  IFunction::registerType<Abs>();
  IFunction::registerType<Log>();
  IFunction::registerType<Ln>();
  IFunction::registerType<Lb>();
  IFunction::registerType<Lg>();
  IFunction::registerType<Exp>();
  IFunction::registerType<Sqr>();
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
  IFunction::registerType<FracMixed>();
  IFunction::registerType<Floor>();
  IFunction::registerType<Ceil>();
  IFunction::registerType<And>();
  IFunction::registerType<Or>();

  IExpression::registerType<IPolynomExpression>();
  IExpression::registerType<IBinaryExpression>();
  IExpression::registerType<IUnaryExpression>();
  IExpression::registerType<FunctionExpression>();
  IExpression::registerType<Expression>();

  IPolynomExpression::registerType<AddExpr>();
  IPolynomExpression::registerType<MulExpr>();
  IPolynomExpression::registerType<MinMaxExpr>();
  IPolynomExpression::registerType<AndExpr>();
  IPolynomExpression::registerType<OrExpr>();

  IBinaryExpression::registerType<DivExpr>();
  IBinaryExpression::registerType<PowExpr>();
  IBinaryExpression::registerType<LogExpr>();
  IBinaryExpression::registerType<DerivativeExpr>();
  IBinaryExpression::registerType<IntegralExpr>();
  IBinaryExpression::registerType<CompExpr>();

  IUnaryExpression::registerType<AbsExpr>();
  IUnaryExpression::registerType<SignExpr>();
  IUnaryExpression::registerType<FloorCeilExpr>();
  IUnaryExpression::registerType<TrigExpr>();
  IUnaryExpression::registerType<InvTrigExpr>();
  IUnaryExpression::registerType<HyperbExpr>();
  IUnaryExpression::registerType<InvHyperbExpr>();
  IUnaryExpression::registerType<NotExpr>();
}

}
