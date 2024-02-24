#include "fintamath/config/ExpressionConfig.hpp"

#include <memory>
#include <utility>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/Tokenizer.hpp"
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
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Frac.hpp"
#include "fintamath/functions/arithmetic/FracMixed.hpp"
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
#include "fintamath/functions/other/Deg.hpp"
#include "fintamath/functions/other/Index.hpp"
#include "fintamath/functions/other/Percent.hpp"
#include "fintamath/functions/powers/Exp.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/powers/PowFunction.hpp"
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

namespace {

void registerTermParsers() {
  Expression::registerTermParser([](const Token &token) {
    if (auto arg = IOperator::parse(token, 2)) {
      return std::make_unique<Term>(token, std::move(arg));
    }

    if (auto arg = IOperator::parse(token, 1)) {
      return std::make_unique<Term>(token, std::move(arg));
    }

    if (auto arg = IFunction::parse(token)) {
      return std::make_unique<Term>(token, std::move(arg));
    }

    return std::unique_ptr<Term>{};
  });

  Expression::registerTermParser([](const Token &token) {
    if (auto arg = ILiteral::parse(token)) {
      return std::make_unique<Term>(token, std::move(arg));
    }

    return std::unique_ptr<Term>{};
  });

  Expression::registerTermParser([](const Token &token) {
    if (auto arg = INumber::parse(token)) {
      return std::make_unique<Term>(token, std::move(arg));
    }

    return std::unique_ptr<Term>{};
  });
}

void registerFunctionExpressionMakers() {
  Expression::registerFunctionExpressionMaker<Add, true>([](ArgumentPtrVector &&args) {
    return AddExpr(std::move(args)).clone();
  });

  Expression::registerFunctionExpressionMaker<Sub>([](ArgumentPtrVector args) {
    ArgumentPtr lhs = std::move(args.front());
    ArgumentPtr rhs = std::move(args.back());

    ArgumentPtr negRhs = negExpr(std::move(rhs));

    return AddExpr({std::move(lhs), std::move(negRhs)}).clone();
  });

  Expression::registerFunctionExpressionMaker<Mul, true>([](ArgumentPtrVector &&args) {
    return MulExpr(std::move(args)).clone();
  });

  Expression::registerFunctionExpressionMaker<Div>([](ArgumentPtrVector args) {
    return DivExpr(std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerFunctionExpressionMaker<Frac>([](ArgumentPtrVector &&args) {
    return divExpr(std::move(args));
  });

  Expression::registerFunctionExpressionMaker<FracMixed>([](ArgumentPtrVector args) {
    ArgumentPtr integ = std::move(args[0]);
    ArgumentPtr numer = std::move(args[1]);
    ArgumentPtr denom = std::move(args[2]);

    return addExpr(std::move(integ), divExpr(std::move(numer), std::move(denom)));
  });

  Expression::registerFunctionExpressionMaker<And, true>([](ArgumentPtrVector &&args) {
    return AndExpr(std::move(args)).clone();
  });

  Expression::registerFunctionExpressionMaker<Or, true>([](ArgumentPtrVector &&args) {
    return OrExpr(std::move(args)).clone();
  });

  Expression::registerFunctionExpressionMaker<Pow>([](ArgumentPtrVector args) {
    return PowExpr(std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerFunctionExpressionMaker<PowFunction>([](ArgumentPtrVector &&args) {
    return powExpr(std::move(args));
  });

  Expression::registerFunctionExpressionMaker<Eqv>([](ArgumentPtrVector args) {
    return CompExpr(Eqv{}, std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerFunctionExpressionMaker<Neqv>([](ArgumentPtrVector args) {
    return CompExpr(Neqv{}, std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerFunctionExpressionMaker<Less>([](ArgumentPtrVector args) {
    return CompExpr(Less{}, std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerFunctionExpressionMaker<More>([](ArgumentPtrVector args) {
    return CompExpr(More{}, std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerFunctionExpressionMaker<LessEqv>([](ArgumentPtrVector args) {
    return CompExpr(LessEqv{}, std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerFunctionExpressionMaker<MoreEqv>([](ArgumentPtrVector args) {
    return CompExpr(MoreEqv{}, std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerFunctionExpressionMaker<Index>([](const ArgumentPtrVector &args) {
    static const Index indexFunc;

    const ArgumentPtr &lhs = args.front();
    const ArgumentPtr &rhs = args.back();

    if (!indexFunc.doArgsMatch({*lhs, *rhs})) {
      throw InvalidInputBinaryOperatorException(indexFunc.toString(), lhs->toString(), rhs->toString());
    }

    return Expression(indexFunc(*lhs, *rhs)).clone(); // TODO: looks weird
  });

  Expression::registerFunctionExpressionMaker<Impl>([](ArgumentPtrVector args) {
    ArgumentPtr lhs = std::move(args.front());
    ArgumentPtr rhs = std::move(args.back());

    ArgumentPtr notLhs = notExpr(std::move(lhs));

    return orExpr(std::move(notLhs), std::move(rhs));
  });

  Expression::registerFunctionExpressionMaker<Equiv>([](ArgumentPtrVector args) {
    ArgumentPtr lhs = std::move(args.front());
    ArgumentPtr rhs = std::move(args.back());

    ArgumentPtr notLhs = notExpr(lhs);
    ArgumentPtr notRhs = notExpr(rhs);

    ArgumentPtr lhsAndRhs = andExpr(std::move(lhs), std::move(rhs));
    ArgumentPtr notLhsAndNotRhs = andExpr(std::move(notLhs), std::move(notRhs));

    return orExpr(std::move(lhsAndRhs), std::move(notLhsAndNotRhs));
  });

  Expression::registerFunctionExpressionMaker<Nequiv>([](ArgumentPtrVector args) {
    ArgumentPtr lhs = std::move(args.front());
    ArgumentPtr rhs = std::move(args.back());

    ArgumentPtr notLhs = notExpr(lhs);
    ArgumentPtr notRhs = notExpr(rhs);

    ArgumentPtr notLhsAndRhs = andExpr(std::move(notLhs), std::move(rhs));
    ArgumentPtr lhsAndNotRhs = andExpr(std::move(lhs), std::move(notRhs));

    return orExpr(std::move(notLhsAndRhs), std::move(lhsAndNotRhs));
  });

  Expression::registerFunctionExpressionMaker<Neg>([](ArgumentPtrVector args) {
    static const ArgumentPtr negOne = Integer(-1).clone();
    return mulExpr(negOne, std::move(args.front()));
  });

  Expression::registerFunctionExpressionMaker<UnaryPlus>([](ArgumentPtrVector args) {
    return std::move(args.front())->clone();
  });

  Expression::registerFunctionExpressionMaker<Not>([](ArgumentPtrVector args) {
    return NotExpr(std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Derivative>([](ArgumentPtrVector args) {
    return DerivativeExpr(std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerFunctionExpressionMaker<Integral>([](ArgumentPtrVector args) {
    return IntegralExpr(std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerFunctionExpressionMaker<Log>([](ArgumentPtrVector args) {
    return LogExpr(std::move(args.front()), std::move(args.back())).clone();
  });

  Expression::registerFunctionExpressionMaker<Ln>([](ArgumentPtrVector args) {
    static const ArgumentPtr logBase = E{}.clone();
    return logExpr(logBase, std::move(args.front()));
  });

  Expression::registerFunctionExpressionMaker<Lb>([](ArgumentPtrVector args) {
    static const ArgumentPtr logBase = Integer(2).clone();
    return logExpr(logBase, std::move(args.front()));
  });

  Expression::registerFunctionExpressionMaker<Lg>([](ArgumentPtrVector args) {
    static const ArgumentPtr logBase = Integer(10).clone();
    return logExpr(logBase, std::move(args.front()));
  });

  Expression::registerFunctionExpressionMaker<Exp>([](ArgumentPtrVector args) {
    static const ArgumentPtr powBase = E{}.clone();
    return powExpr(powBase, std::move(args.front()));
  });

  Expression::registerFunctionExpressionMaker<Percent>([](ArgumentPtrVector args) {
    static const ArgumentPtr percentValue = Integer(100).clone();
    return divExpr(std::move(args.front()), percentValue);
  });

  Expression::registerFunctionExpressionMaker<Min>([](ArgumentPtrVector &&args) {
    return MinMaxExpr(Min{}, std::move(args)).clone();
  });

  Expression::registerFunctionExpressionMaker<Max>([](ArgumentPtrVector &&args) {
    return MinMaxExpr(Max{}, std::move(args)).clone();
  });

  Expression::registerFunctionExpressionMaker<Sqr>([](ArgumentPtrVector args) {
    static const ArgumentPtr powRate = Integer(2).clone();
    return powExpr(std::move(args.front()), powRate);
  });

  Expression::registerFunctionExpressionMaker<Sqrt>([](ArgumentPtrVector args) {
    static const ArgumentPtr powRate = Rational(1, 2).clone();
    return powExpr(std::move(args.front()), powRate);
  });

  Expression::registerFunctionExpressionMaker<Root>([](ArgumentPtrVector args) {
    ArgumentPtr lhs = std::move(args.front());
    ArgumentPtr rhs = std::move(args.back());

    if (const auto rhsNum = cast<INumber>(rhs); rhsNum && *rhsNum != Integer(0)) {
      return powExpr(std::move(lhs), Rational(1) / (*rhsNum));
    }

    static const ArgumentPtr one = Integer(1).clone();
    ArgumentPtr invRhs = divExpr(one, std::move(rhs));

    return powExpr(std::move(lhs), std::move(invRhs));
  });

  Expression::registerFunctionExpressionMaker<Sin>([](ArgumentPtrVector args) {
    return TrigExpr(Sin{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Cos>([](ArgumentPtrVector args) {
    return TrigExpr(Cos{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Tan>([](ArgumentPtrVector args) {
    return TrigExpr(Tan{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Cot>([](ArgumentPtrVector args) {
    return TrigExpr(Cot{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Sec>([](ArgumentPtrVector args) {
    return TrigExpr(Sec{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Csc>([](ArgumentPtrVector args) {
    return TrigExpr(Csc{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Asin>([](ArgumentPtrVector args) {
    return InvTrigExpr(Asin{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Acos>([](ArgumentPtrVector args) {
    return InvTrigExpr(Acos{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Atan>([](ArgumentPtrVector args) {
    return InvTrigExpr(Atan{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Acot>([](ArgumentPtrVector args) {
    return InvTrigExpr(Acot{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Asec>([](ArgumentPtrVector args) {
    return InvTrigExpr(Asec{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Acsc>([](ArgumentPtrVector args) {
    return InvTrigExpr(Acsc{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Sinh>([](ArgumentPtrVector args) {
    return HyperbExpr(Sinh{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Cosh>([](ArgumentPtrVector args) {
    return HyperbExpr(Cosh{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Tanh>([](ArgumentPtrVector args) {
    return HyperbExpr(Tanh{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Coth>([](ArgumentPtrVector args) {
    return HyperbExpr(Coth{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Sech>([](ArgumentPtrVector args) {
    return HyperbExpr(Sech{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Csch>([](ArgumentPtrVector args) {
    return HyperbExpr(Csch{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Asinh>([](ArgumentPtrVector args) {
    return InvHyperbExpr(Asinh{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Acosh>([](ArgumentPtrVector args) {
    return InvHyperbExpr(Acosh{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Atanh>([](ArgumentPtrVector args) {
    return InvHyperbExpr(Atanh{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Acoth>([](ArgumentPtrVector args) {
    return InvHyperbExpr(Acoth{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Asech>([](ArgumentPtrVector args) {
    return InvHyperbExpr(Asech{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Acsch>([](ArgumentPtrVector args) {
    return InvHyperbExpr(Acsch{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Deg>([](ArgumentPtrVector args) {
    static const ArgumentPtr deg1 = Deg{}(Integer(1));
    return mulExpr(std::move(args.front()), deg1);
  });

  Expression::registerFunctionExpressionMaker<Floor>([](ArgumentPtrVector args) {
    return FloorCeilExpr(Floor{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Ceil>([](ArgumentPtrVector args) {
    return FloorCeilExpr(Ceil{}, std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Abs>([](ArgumentPtrVector args) {
    return AbsExpr(std::move(args.front())).clone();
  });

  Expression::registerFunctionExpressionMaker<Sign>([](ArgumentPtrVector args) {
    return SignExpr(std::move(args.front())).clone();
  });
}

}

ExpressionConfig::ExpressionConfig() {
  registerTermParsers();
  registerFunctionExpressionMakers();
}

}
