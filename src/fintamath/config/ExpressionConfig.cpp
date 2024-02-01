#include "fintamath/config/ExpressionConfig.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/FunctionExpression.hpp"
#include "fintamath/expressions/binary/CompExpression.hpp"
#include "fintamath/expressions/binary/DerivativeExpression.hpp"
#include "fintamath/expressions/binary/DivExpression.hpp"
#include "fintamath/expressions/binary/IntegralExpression.hpp"
#include "fintamath/expressions/binary/LogExpression.hpp"
#include "fintamath/expressions/binary/PowExpression.hpp"
#include "fintamath/expressions/polynomial/AddExpression.hpp"
#include "fintamath/expressions/polynomial/AndExpression.hpp"
#include "fintamath/expressions/polynomial/MinMaxExpression.hpp"
#include "fintamath/expressions/polynomial/MulExpression.hpp"
#include "fintamath/expressions/polynomial/OrExpression.hpp"
#include "fintamath/expressions/unary/AbsExpression.hpp"
#include "fintamath/expressions/unary/FloorCeilExpression.hpp"
#include "fintamath/expressions/unary/HyperbExpression.hpp"
#include "fintamath/expressions/unary/InvHyperbExpression.hpp"
#include "fintamath/expressions/unary/InvTrigExpression.hpp"
#include "fintamath/expressions/unary/NotExpression.hpp"
#include "fintamath/expressions/unary/SignExpression.hpp"
#include "fintamath/expressions/unary/TrigExpression.hpp"
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
#include "fintamath/literals/constants/E.hpp"

namespace fintamath {

namespace {

void registerTermParsers() {
  Expression::registerTermParser([](const Token &token) {
    if (auto arg = IFunction::parse(token, IFunction::Type::Binary)) {
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
    return AddExpression(std::move(args)).clone();
  });

  Expression::registerFunctionExpressionMaker<Sub>([](const ArgumentPtrVector &args) {
    ArgumentPtr lhs = args.front();
    ArgumentPtr rhs = args.back();

    ArgumentPtr negRhs = negExpr(rhs);

    return AddExpression({lhs, negRhs}).clone();
  });

  Expression::registerFunctionExpressionMaker<Mul, true>([](ArgumentPtrVector &&args) {
    return MulExpression(std::move(args)).clone();
  });

  Expression::registerFunctionExpressionMaker<Div>([](const ArgumentPtrVector &args) {
    return DivExpression(args.front(), args.back()).clone();
  });

  Expression::registerFunctionExpressionMaker<Frac>([](ArgumentPtrVector &&args) {
    return divExpr(std::move(args));
  });

  Expression::registerFunctionExpressionMaker<FracMixed>([](const ArgumentPtrVector &args) {
    ArgumentPtr integ = args[0];
    ArgumentPtr numer = args[1];
    ArgumentPtr denom = args[2];

    return addExpr(integ, divExpr(numer, denom));
  });

  Expression::registerFunctionExpressionMaker<And, true>([](ArgumentPtrVector &&args) {
    return AndExpression(std::move(args)).clone();
  });

  Expression::registerFunctionExpressionMaker<Or, true>([](ArgumentPtrVector &&args) {
    return OrExpression(std::move(args)).clone();
  });

  Expression::registerFunctionExpressionMaker<Pow>([](const ArgumentPtrVector &args) {
    return PowExpression(args.front(), args.back()).clone();
  });

  Expression::registerFunctionExpressionMaker<PowFunction>([](ArgumentPtrVector &&args) {
    return powExpr(std::move(args));
  });

  Expression::registerFunctionExpressionMaker<Eqv>([](const ArgumentPtrVector &args) {
    return CompExpression(Eqv{}, args.front(), args.back()).clone();
  });

  Expression::registerFunctionExpressionMaker<Neqv>([](const ArgumentPtrVector &args) {
    return CompExpression(Neqv{}, args.front(), args.back()).clone();
  });

  Expression::registerFunctionExpressionMaker<Less>([](const ArgumentPtrVector &args) {
    return CompExpression(Less{}, args.front(), args.back()).clone();
  });

  Expression::registerFunctionExpressionMaker<More>([](const ArgumentPtrVector &args) {
    return CompExpression(More{}, args.front(), args.back()).clone();
  });

  Expression::registerFunctionExpressionMaker<LessEqv>([](const ArgumentPtrVector &args) {
    return CompExpression(LessEqv{}, args.front(), args.back()).clone();
  });

  Expression::registerFunctionExpressionMaker<MoreEqv>([](const ArgumentPtrVector &args) {
    return CompExpression(MoreEqv{}, args.front(), args.back()).clone();
  });

  Expression::registerFunctionExpressionMaker<Index>([](const ArgumentPtrVector &args) {
    static const Index func;
    ArgumentPtr lhs = args.front();
    ArgumentPtr rhs = args.back();

    if (!func.doArgsMatch({*lhs, *rhs})) {
      throw InvalidInputBinaryOperatorException(func.toString(), lhs->toString(), rhs->toString());
    }

    return Expression(func(*lhs, *rhs)).clone(); // TODO: looks weird
  });

  Expression::registerFunctionExpressionMaker<Impl>([](const ArgumentPtrVector &args) {
    ArgumentPtr lhs = args.front();
    ArgumentPtr rhs = args.back();

    ArgumentPtr notLhs = notExpr(lhs);

    return orExpr(notLhs, rhs);
  });

  Expression::registerFunctionExpressionMaker<Equiv>([](const ArgumentPtrVector &args) {
    ArgumentPtr lhs = args.front();
    ArgumentPtr rhs = args.back();

    ArgumentPtr notLhs = notExpr(lhs);
    ArgumentPtr notRhs = notExpr(rhs);

    ArgumentPtr lhsAndRhs = andExpr(lhs, rhs);
    ArgumentPtr notLhsAndNotRhs = andExpr(notLhs, notRhs);

    return orExpr(lhsAndRhs, notLhsAndNotRhs);
  });

  Expression::registerFunctionExpressionMaker<Nequiv>([](const ArgumentPtrVector &args) {
    ArgumentPtr lhs = args.front();
    ArgumentPtr rhs = args.back();

    ArgumentPtr notLhs = notExpr(lhs);
    ArgumentPtr notRhs = notExpr(rhs);

    ArgumentPtr notLhsAndRhs = andExpr(notLhs, rhs);
    ArgumentPtr lhsAndNotRhs = andExpr(lhs, notRhs);

    return orExpr(notLhsAndRhs, lhsAndNotRhs);
  });

  Expression::registerFunctionExpressionMaker<Neg>([](const ArgumentPtrVector &args) {
    static const ArgumentPtr negOne = Integer(-1).clone();
    return mulExpr(negOne, args.front());
  });

  Expression::registerFunctionExpressionMaker<UnaryPlus>([](const ArgumentPtrVector &args) {
    return args.front()->clone();
  });

  Expression::registerFunctionExpressionMaker<Not>([](const ArgumentPtrVector &args) {
    return NotExpression(args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Derivative>([](const ArgumentPtrVector &args) {
    return DerivativeExpression(args.front(), args.back()).clone();
  });

  Expression::registerFunctionExpressionMaker<Integral>([](const ArgumentPtrVector &args) {
    return IntegralExpression(args.front(), args.back()).clone();
  });

  Expression::registerFunctionExpressionMaker<Log>([](const ArgumentPtrVector &args) {
    return LogExpression(args.front(), args.back()).clone();
  });

  Expression::registerFunctionExpressionMaker<Ln>([](const ArgumentPtrVector &args) {
    static const ArgumentPtr logBase = E{}.clone();
    return logExpr(logBase, args.front());
  });

  Expression::registerFunctionExpressionMaker<Lb>([](const ArgumentPtrVector &args) {
    static const ArgumentPtr logBase = Integer(2).clone();
    return logExpr(logBase, args.front());
  });

  Expression::registerFunctionExpressionMaker<Lg>([](const ArgumentPtrVector &args) {
    static const ArgumentPtr logBase = Integer(10).clone();
    return logExpr(logBase, args.front());
  });

  Expression::registerFunctionExpressionMaker<Exp>([](const ArgumentPtrVector &args) {
    static const ArgumentPtr powBase = E{}.clone();
    return powExpr(powBase, args.front());
  });

  Expression::registerFunctionExpressionMaker<Percent>([](const ArgumentPtrVector &args) {
    static const ArgumentPtr percentValue = Integer(100).clone();
    return divExpr(args.front(), percentValue);
  });

  Expression::registerFunctionExpressionMaker<Min>([](ArgumentPtrVector &&args) {
    return MinMaxExpression(Min{}, std::move(args)).clone();
  });

  Expression::registerFunctionExpressionMaker<Max>([](ArgumentPtrVector &&args) {
    return MinMaxExpression(Max{}, std::move(args)).clone();
  });

  Expression::registerFunctionExpressionMaker<Sqr>([](const ArgumentPtrVector &args) {
    static const ArgumentPtr powRate = Integer(2).clone();
    return powExpr(args.front(), powRate);
  });

  Expression::registerFunctionExpressionMaker<Sqrt>([](const ArgumentPtrVector &args) {
    static const ArgumentPtr powRate = Rational(1, 2).clone();
    return powExpr(args.front(), powRate);
  });

  Expression::registerFunctionExpressionMaker<Root>([](const ArgumentPtrVector &args) {
    ArgumentPtr lhs = args.front();
    ArgumentPtr rhs = args.back();

    if (const auto rhsNum = cast<INumber>(rhs); rhsNum && *rhsNum != Integer(0)) {
      return powExpr(lhs, Rational(1) / (*rhsNum));
    }

    static const ArgumentPtr one = Integer(1).clone();
    ArgumentPtr invRhs = divExpr(one, rhs);

    return powExpr(lhs, invRhs);
  });

  Expression::registerFunctionExpressionMaker<Sin>([](const ArgumentPtrVector &args) {
    return TrigExpression(Sin{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Cos>([](const ArgumentPtrVector &args) {
    return TrigExpression(Cos{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Tan>([](const ArgumentPtrVector &args) {
    return TrigExpression(Tan{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Cot>([](const ArgumentPtrVector &args) {
    return TrigExpression(Cot{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Sec>([](const ArgumentPtrVector &args) {
    return TrigExpression(Sec{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Csc>([](const ArgumentPtrVector &args) {
    return TrigExpression(Csc{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Asin>([](const ArgumentPtrVector &args) {
    return InvTrigExpression(Asin{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Acos>([](const ArgumentPtrVector &args) {
    return InvTrigExpression(Acos{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Atan>([](const ArgumentPtrVector &args) {
    return InvTrigExpression(Atan{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Acot>([](const ArgumentPtrVector &args) {
    return InvTrigExpression(Acot{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Asec>([](const ArgumentPtrVector &args) {
    return InvTrigExpression(Asec{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Acsc>([](const ArgumentPtrVector &args) {
    return InvTrigExpression(Acsc{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Sinh>([](const ArgumentPtrVector &args) {
    return HyperbExpression(Sinh{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Cosh>([](const ArgumentPtrVector &args) {
    return HyperbExpression(Cosh{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Tanh>([](const ArgumentPtrVector &args) {
    return HyperbExpression(Tanh{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Coth>([](const ArgumentPtrVector &args) {
    return HyperbExpression(Coth{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Sech>([](const ArgumentPtrVector &args) {
    return HyperbExpression(Sech{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Csch>([](const ArgumentPtrVector &args) {
    return HyperbExpression(Csch{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Asinh>([](const ArgumentPtrVector &args) {
    return InvHyperbExpression(Asinh{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Acosh>([](const ArgumentPtrVector &args) {
    return InvHyperbExpression(Acosh{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Atanh>([](const ArgumentPtrVector &args) {
    return InvHyperbExpression(Atanh{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Acoth>([](const ArgumentPtrVector &args) {
    return InvHyperbExpression(Acoth{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Asech>([](const ArgumentPtrVector &args) {
    return InvHyperbExpression(Asech{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Acsch>([](const ArgumentPtrVector &args) {
    return InvHyperbExpression(Acsch{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Deg>([](const ArgumentPtrVector &args) {
    static const ArgumentPtr deg1 = Deg{}(Integer(1));
    return mulExpr(args.front(), deg1);
  });

  Expression::registerFunctionExpressionMaker<Floor>([](const ArgumentPtrVector &args) {
    return FloorCeilExpression(Floor{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Ceil>([](const ArgumentPtrVector &args) {
    return FloorCeilExpression(Ceil{}, args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Abs>([](const ArgumentPtrVector &args) {
    return AbsExpression(args.front()).clone();
  });

  Expression::registerFunctionExpressionMaker<Sign>([](const ArgumentPtrVector &args) {
    return SignExpression(args.front()).clone();
  });
}

}

ExpressionConfig::ExpressionConfig() {
  registerTermParsers();
  registerFunctionExpressionMakers();
}

}
