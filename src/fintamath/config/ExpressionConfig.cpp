#include "fintamath/config/ExpressionConfig.hpp"

#include <memory>
#include <utility>

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/binary/CompExpr.hpp"
#include "fintamath/expressions/binary/DerivativeExpr.hpp"
#include "fintamath/expressions/binary/DivExpr.hpp"
#include "fintamath/expressions/binary/IntegralExpr.hpp"
#include "fintamath/expressions/binary/LogExpr.hpp"
#include "fintamath/expressions/binary/PowExpr.hpp"
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
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
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
#include "fintamath/functions/other/Deg.hpp"
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
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/constants/E.hpp"

namespace fintamath::detail {

ExpressionConfig::ExpressionConfig() {
  Expression::registerExpressionConstructor<Add>([](ArgumentPtrVector &&args) {
    return AddExpr(std::move(args)).clone();
  });

  Expression::registerExpressionConstructor<AddOper>([](ArgumentPtrVector &&args) {
    return addExpr(std::move(args));
  });

  Expression::registerExpressionConstructor<Sub>([](ArgumentPtrVector args) {
    ArgumentPtr lhs = std::move(args.front());
    ArgumentPtr rhs = std::move(args.back());

    ArgumentPtr negRhs = negExpr(std::move(rhs));

    return addExpr(std::move(lhs), std::move(negRhs));
  });

  Expression::registerExpressionConstructor<Mul>([](ArgumentPtrVector &&args) {
    return MulExpr(std::move(args)).clone();
  });

  Expression::registerExpressionConstructor<MulOper>([](ArgumentPtrVector &&args) {
    return mulExpr(std::move(args));
  });

  Expression::registerExpressionConstructor<Div>([](ArgumentPtrVector args) {
    return DivExpr(std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerExpressionConstructor<Frac>([](ArgumentPtrVector &&args) {
    return divExpr(std::move(args));
  });

  Expression::registerExpressionConstructor<FracMixed>([](ArgumentPtrVector args) {
    ArgumentPtr integ = std::move(args[0]);
    ArgumentPtr numer = std::move(args[1]);
    ArgumentPtr denom = std::move(args[2]);

    return addExpr(std::move(integ), divExpr(std::move(numer), std::move(denom)));
  });

  Expression::registerExpressionConstructor<And>([](ArgumentPtrVector &&args) {
    return AndExpr(std::move(args)).clone();
  });

  Expression::registerExpressionConstructor<AndOper>([](ArgumentPtrVector &&args) {
    return andExpr(std::move(args));
  });

  Expression::registerExpressionConstructor<Or>([](ArgumentPtrVector &&args) {
    return OrExpr(std::move(args)).clone();
  });

  Expression::registerExpressionConstructor<OrOper>([](ArgumentPtrVector &&args) {
    return orExpr(std::move(args));
  });

  Expression::registerExpressionConstructor<Pow>([](ArgumentPtrVector args) {
    return PowExpr(std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerExpressionConstructor<PowOper>([](ArgumentPtrVector &&args) {
    return powExpr(std::move(args));
  });

  Expression::registerExpressionConstructor<Eqv>([](ArgumentPtrVector args) {
    return CompExpr(Eqv{}, std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerExpressionConstructor<Neqv>([](ArgumentPtrVector args) {
    return CompExpr(Neqv{}, std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerExpressionConstructor<Less>([](ArgumentPtrVector args) {
    return CompExpr(Less{}, std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerExpressionConstructor<More>([](ArgumentPtrVector args) {
    return CompExpr(More{}, std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerExpressionConstructor<LessEqv>([](ArgumentPtrVector args) {
    return CompExpr(LessEqv{}, std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerExpressionConstructor<MoreEqv>([](ArgumentPtrVector args) {
    return CompExpr(MoreEqv{}, std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerExpressionConstructor<Index>([](const ArgumentPtrVector &args) {
    static const Index indexFunc;

    const ArgumentPtr &lhs = args.front();
    const ArgumentPtr &rhs = args.back();

    if (!indexFunc.doArgsMatch({*lhs, *rhs})) {
      throw InvalidInputBinaryOperatorException(indexFunc.toString(), lhs->toString(), rhs->toString());
    }

    return Expression(indexFunc(*lhs, *rhs)).clone(); // TODO: looks weird
  });

  Expression::registerExpressionConstructor<Impl>([](ArgumentPtrVector args) {
    ArgumentPtr lhs = std::move(args.front());
    ArgumentPtr rhs = std::move(args.back());

    ArgumentPtr notLhs = notExpr(std::move(lhs));

    return orExpr(std::move(notLhs), std::move(rhs));
  });

  Expression::registerExpressionConstructor<Equiv>([](ArgumentPtrVector args) {
    ArgumentPtr lhs = std::move(args.front());
    ArgumentPtr rhs = std::move(args.back());

    ArgumentPtr notLhs = notExpr(lhs);
    ArgumentPtr notRhs = notExpr(rhs);

    ArgumentPtr lhsAndRhs = andExpr(std::move(lhs), std::move(rhs));
    ArgumentPtr notLhsAndNotRhs = andExpr(std::move(notLhs), std::move(notRhs));

    return orExpr(std::move(lhsAndRhs), std::move(notLhsAndNotRhs));
  });

  Expression::registerExpressionConstructor<Nequiv>([](ArgumentPtrVector args) {
    ArgumentPtr lhs = std::move(args.front());
    ArgumentPtr rhs = std::move(args.back());

    ArgumentPtr notLhs = notExpr(lhs);
    ArgumentPtr notRhs = notExpr(rhs);

    ArgumentPtr notLhsAndRhs = andExpr(std::move(notLhs), std::move(rhs));
    ArgumentPtr lhsAndNotRhs = andExpr(std::move(lhs), std::move(notRhs));

    return orExpr(std::move(notLhsAndRhs), std::move(lhsAndNotRhs));
  });

  Expression::registerExpressionConstructor<Neg>([](ArgumentPtrVector args) {
    static const ArgumentPtr negOne = Integer(-1).clone();
    return mulExpr(negOne, std::move(args.front()));
  });

  Expression::registerExpressionConstructor<UnaryPlus>([](ArgumentPtrVector args) {
    return std::move(args.front())->clone();
  });

  Expression::registerExpressionConstructor<Not>([](ArgumentPtrVector args) {
    return NotExpr(std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Derivative>([](ArgumentPtrVector args) {
    return DerivativeExpr(std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerExpressionConstructor<Integral>([](ArgumentPtrVector args) {
    return IntegralExpr(std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerExpressionConstructor<Log>([](ArgumentPtrVector args) {
    return LogExpr(std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerExpressionConstructor<Ln>([](ArgumentPtrVector args) {
    static const ArgumentPtr logBase = E{}.clone();
    return logExpr(logBase, std::move(args.front()));
  });

  Expression::registerExpressionConstructor<Lb>([](ArgumentPtrVector args) {
    static const ArgumentPtr logBase = Integer(2).clone();
    return logExpr(logBase, std::move(args.front()));
  });

  Expression::registerExpressionConstructor<Lg>([](ArgumentPtrVector args) {
    static const ArgumentPtr logBase = Integer(10).clone();
    return logExpr(logBase, std::move(args.front()));
  });

  Expression::registerExpressionConstructor<Exp>([](ArgumentPtrVector args) {
    static const ArgumentPtr powBase = E{}.clone();
    return powExpr(powBase, std::move(args.front()));
  });

  Expression::registerExpressionConstructor<Percent>([](ArgumentPtrVector args) {
    static const ArgumentPtr percentValue = Integer(100).clone();
    return divExpr(std::move(args.front()), percentValue);
  });

  Expression::registerExpressionConstructor<Min>([](ArgumentPtrVector &&args) {
    return MinMaxExpr(Min{}, std::move(args)).clone();
  });

  Expression::registerExpressionConstructor<Max>([](ArgumentPtrVector &&args) {
    return MinMaxExpr(Max{}, std::move(args)).clone();
  });

  Expression::registerExpressionConstructor<Sqr>([](ArgumentPtrVector args) {
    static const ArgumentPtr powRate = Integer(2).clone();
    return powExpr(std::move(args.front()), powRate);
  });

  Expression::registerExpressionConstructor<Sqrt>([](ArgumentPtrVector args) {
    static const ArgumentPtr powRate = Rational(1, 2).clone();
    return powExpr(std::move(args.front()), powRate);
  });

  Expression::registerExpressionConstructor<Root>([](ArgumentPtrVector args) {
    ArgumentPtr lhs = std::move(args.front());
    ArgumentPtr rhs = std::move(args.back());

    if (const auto rhsNum = cast<INumber>(rhs); rhsNum && *rhsNum != Integer(0)) {
      return powExpr(std::move(lhs), Rational(1) / (*rhsNum));
    }

    static const ArgumentPtr one = Integer(1).clone();
    ArgumentPtr invRhs = divExpr(one, std::move(rhs));

    return powExpr(std::move(lhs), std::move(invRhs));
  });

  Expression::registerExpressionConstructor<Sin>([](ArgumentPtrVector args) {
    return TrigExpr(Sin{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Cos>([](ArgumentPtrVector args) {
    return TrigExpr(Cos{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Tan>([](ArgumentPtrVector args) {
    return TrigExpr(Tan{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Cot>([](ArgumentPtrVector args) {
    return TrigExpr(Cot{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Sec>([](ArgumentPtrVector args) {
    return TrigExpr(Sec{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Csc>([](ArgumentPtrVector args) {
    return TrigExpr(Csc{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Asin>([](ArgumentPtrVector args) {
    return InvTrigExpr(Asin{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Acos>([](ArgumentPtrVector args) {
    return InvTrigExpr(Acos{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Atan>([](ArgumentPtrVector args) {
    return InvTrigExpr(Atan{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Acot>([](ArgumentPtrVector args) {
    return InvTrigExpr(Acot{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Asec>([](ArgumentPtrVector args) {
    return InvTrigExpr(Asec{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Acsc>([](ArgumentPtrVector args) {
    return InvTrigExpr(Acsc{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Sinh>([](ArgumentPtrVector args) {
    return HyperbExpr(Sinh{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Cosh>([](ArgumentPtrVector args) {
    return HyperbExpr(Cosh{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Tanh>([](ArgumentPtrVector args) {
    return HyperbExpr(Tanh{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Coth>([](ArgumentPtrVector args) {
    return HyperbExpr(Coth{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Sech>([](ArgumentPtrVector args) {
    return HyperbExpr(Sech{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Csch>([](ArgumentPtrVector args) {
    return HyperbExpr(Csch{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Asinh>([](ArgumentPtrVector args) {
    return InvHyperbExpr(Asinh{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Acosh>([](ArgumentPtrVector args) {
    return InvHyperbExpr(Acosh{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Atanh>([](ArgumentPtrVector args) {
    return InvHyperbExpr(Atanh{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Acoth>([](ArgumentPtrVector args) {
    return InvHyperbExpr(Acoth{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Asech>([](ArgumentPtrVector args) {
    return InvHyperbExpr(Asech{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Acsch>([](ArgumentPtrVector args) {
    return InvHyperbExpr(Acsch{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Deg>([](ArgumentPtrVector args) {
    static const ArgumentPtr deg1 = Deg{}(Integer(1));
    return mulExpr(std::move(args.front()), deg1);
  });

  Expression::registerExpressionConstructor<Floor>([](ArgumentPtrVector args) {
    return FloorCeilExpr(Floor{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Ceil>([](ArgumentPtrVector args) {
    return FloorCeilExpr(Ceil{}, std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Abs>([](ArgumentPtrVector args) {
    return AbsExpr(std::move(args.front())).clone();
  });

  Expression::registerExpressionConstructor<Sign>([](ArgumentPtrVector args) {
    return SignExpr(std::move(args.front())).clone();
  });
}

}
