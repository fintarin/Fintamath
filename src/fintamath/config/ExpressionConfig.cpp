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
#include "fintamath/expressions/unary/HyperbExpression.hpp"
#include "fintamath/expressions/unary/InvHyperbExpression.hpp"
#include "fintamath/expressions/unary/InvTrigExpression.hpp"
#include "fintamath/expressions/unary/NotExpression.hpp"
#include "fintamath/expressions/unary/TrigExpression.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Frac.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
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
#include "fintamath/functions/other/Deg.hpp"
#include "fintamath/functions/other/Index.hpp"
#include "fintamath/functions/other/Percent.hpp"
#include "fintamath/functions/powers/Exp.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/powers/PowF.hpp"
#include "fintamath/functions/powers/Root.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/functions/trigonometry/Acos.hpp"
#include "fintamath/functions/trigonometry/Acot.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"
#include "fintamath/functions/trigonometry/Atan.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/trigonometry/Cot.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/functions/trigonometry/Tan.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"

namespace fintamath {

Parser::Vector<std::unique_ptr<Term>, const Token &> &Expression::getTermMakers() {
  static Parser::Vector<std::unique_ptr<Term>, const Token &> maker;
  return maker;
}

Parser::Map<std::unique_ptr<IMathObject>, ArgumentPtrVector &&> &Expression::getExpressionMakers() {
  static Parser::Map<std::unique_ptr<IMathObject>, ArgumentPtrVector &&> maker;
  return maker;
}

}

using namespace fintamath;

namespace {

struct ExpressionConfig {
  ExpressionConfig() {
    registerTermsMakers();
    registerFunctionExpressionMakers();
  }

  static void registerTermsMakers() {
    Expression::registerTermsMaker([](const Token &token) {
      if (auto arg = IFunction::parse(token, IFunction::Type::Binary)) {
        return std::make_unique<Term>(token, std::move(arg));
      }

      if (auto arg = IFunction::parse(token)) {
        return std::make_unique<Term>(token, std::move(arg));
      }

      return std::unique_ptr<Term>();
    });

    Expression::registerTermsMaker([](const Token &token) {
      if (auto arg = ILiteral::parse(token)) {
        return std::make_unique<Term>(token, std::move(arg));
      }

      return std::unique_ptr<Term>();
    });

    Expression::registerTermsMaker([](const Token &token) {
      if (auto arg = INumber::parse(token)) {
        return std::make_unique<Term>(token, std::move(arg));
      }

      return std::unique_ptr<Term>();
    });
  }

  static void registerFunctionExpressionMakers() {
    Expression::registerFunctionExpressionMaker<Add, true>([](ArgumentPtrVector &&args) {
      return AddExpression(std::move(args)).clone();
    });

    Expression::registerFunctionExpressionMaker<Sub>([](ArgumentPtrVector &&args) {
      ArgumentPtr lhs = std::move(args.front());
      ArgumentPtr rhs = std::move(args.back());

      ArgumentPtr negRhs = negExpr(std::move(rhs));

      return AddExpression({std::move(lhs), std::move(negRhs)}).clone();
    });

    Expression::registerFunctionExpressionMaker<Mul, true>([](ArgumentPtrVector &&args) {
      return MulExpression(std::move(args)).clone();
    });

    Expression::registerFunctionExpressionMaker<Div>([](ArgumentPtrVector &&args) {
      return DivExpression(std::move(args.front()), std::move(args.back())).clone();
    });

    Expression::registerFunctionExpressionMaker<Frac>([](ArgumentPtrVector &&args) {
      return divExpr(std::move(args));
    });

    Expression::registerFunctionExpressionMaker<And, true>([](ArgumentPtrVector &&args) {
      return AndExpression(std::move(args)).clone();
    });

    Expression::registerFunctionExpressionMaker<Or, true>([](ArgumentPtrVector &&args) {
      return OrExpression(std::move(args)).clone();
    });

    Expression::registerFunctionExpressionMaker<Pow>([](ArgumentPtrVector &&args) {
      return PowExpression(std::move(args.front()), std::move(args.back())).clone();
    });

    Expression::registerFunctionExpressionMaker<PowF>([](ArgumentPtrVector &&args) {
      return PowExpression(std::move(args.front()), std::move(args.back())).clone();
    });

    Expression::registerFunctionExpressionMaker<Eqv>([](ArgumentPtrVector &&args) {
      return CompExpression(Eqv(), std::move(args.front()), std::move(args.back())).clone();
    });

    Expression::registerFunctionExpressionMaker<Neqv>([](ArgumentPtrVector &&args) {
      return CompExpression(Neqv(), std::move(args.front()), std::move(args.back())).clone();
    });

    Expression::registerFunctionExpressionMaker<Less>([](ArgumentPtrVector &&args) {
      return CompExpression(Less(), std::move(args.front()), std::move(args.back())).clone();
    });

    Expression::registerFunctionExpressionMaker<More>([](ArgumentPtrVector &&args) {
      return CompExpression(More(), std::move(args.front()), std::move(args.back())).clone();
    });

    Expression::registerFunctionExpressionMaker<LessEqv>([](ArgumentPtrVector &&args) {
      return CompExpression(LessEqv(), std::move(args.front()), std::move(args.back())).clone();
    });

    Expression::registerFunctionExpressionMaker<MoreEqv>([](ArgumentPtrVector &&args) {
      return CompExpression(MoreEqv(), std::move(args.front()), std::move(args.back())).clone();
    });

    Expression::registerFunctionExpressionMaker<Index>([](ArgumentPtrVector &&args) {
      static const Index func;
      ArgumentPtr lhs = std::move(args.front());
      ArgumentPtr rhs = std::move(args.back());

      if (!func.doArgsMatch({*lhs, *rhs})) {
        throw InvalidInputBinaryOperatorException(func.toString(), lhs->toString(), rhs->toString());
      }

      return Expression(func(*lhs, *rhs)).clone(); // TODO: looks weird
    });

    Expression::registerFunctionExpressionMaker<Impl>([](ArgumentPtrVector &&args) {
      ArgumentPtr lhs = std::move(args.front());
      ArgumentPtr rhs = std::move(args.back());

      ArgumentPtr notLhs = notExpr(std::move(lhs));

      return orExpr(std::move(notLhs), std::move(rhs));
    });

    Expression::registerFunctionExpressionMaker<Equiv>([](ArgumentPtrVector &&args) {
      ArgumentPtr lhs = std::move(args.front());
      ArgumentPtr rhs = std::move(args.back());

      ArgumentPtr notLhs = notExpr(lhs);
      ArgumentPtr notRhs = notExpr(rhs);

      ArgumentPtr lhsAndRhs = andExpr(std::move(lhs), std::move(rhs));
      ArgumentPtr notLhsAndNotRhs = andExpr(std::move(notLhs), std::move(notRhs));

      return orExpr(std::move(lhsAndRhs), std::move(notLhsAndNotRhs));
    });

    Expression::registerFunctionExpressionMaker<Nequiv>([](ArgumentPtrVector &&args) {
      ArgumentPtr lhs = std::move(args.front());
      ArgumentPtr rhs = std::move(args.back());

      ArgumentPtr notLhs = notExpr(lhs);
      ArgumentPtr notRhs = notExpr(rhs);

      ArgumentPtr notLhsAndRhs = andExpr(std::move(notLhs), std::move(rhs));
      ArgumentPtr lhsAndNotRhs = andExpr(std::move(lhs), std::move(notRhs));

      return orExpr(std::move(notLhsAndRhs), std::move(lhsAndNotRhs));
    });

    Expression::registerFunctionExpressionMaker<Neg>([](ArgumentPtrVector &&args) {
      static const ArgumentPtr negOne = Integer(-1).clone();
      return mulExpr(negOne, args.front());
    });

    Expression::registerFunctionExpressionMaker<UnaryPlus>([](ArgumentPtrVector &&args) {
      return std::move(args.front())->clone();
    });

    Expression::registerFunctionExpressionMaker<Not>([](ArgumentPtrVector &&args) {
      return NotExpression(std::move(args.front())).clone();
    });

    Expression::registerFunctionExpressionMaker<Derivative>([](ArgumentPtrVector &&args) {
      return DerivativeExpression(std::move(args.front()), std::move(args.back())).clone();
    });

    Expression::registerFunctionExpressionMaker<Integral>([](ArgumentPtrVector &&args) {
      return IntegralExpression(std::move(args.front()), std::move(args.back())).clone();
    });

    Expression::registerFunctionExpressionMaker<Log>([](ArgumentPtrVector &&args) {
      return LogExpression(std::move(args.front()), std::move(args.back())).clone();
    });

    Expression::registerFunctionExpressionMaker<Ln>([](ArgumentPtrVector &&args) {
      static const ArgumentPtr logBase = E().clone();
      return logExpr(logBase, args.front());
    });

    Expression::registerFunctionExpressionMaker<Lb>([](ArgumentPtrVector &&args) {
      static const ArgumentPtr logBase = Integer(2).clone();
      return logExpr(logBase, args.front());
    });

    Expression::registerFunctionExpressionMaker<Lg>([](ArgumentPtrVector &&args) {
      static const ArgumentPtr logBase = Integer(10).clone();
      return logExpr(logBase, args.front());
    });

    Expression::registerFunctionExpressionMaker<Exp>([](ArgumentPtrVector &&args) {
      static const ArgumentPtr powBase = E().clone();
      return powExpr(powBase, args.front());
    });

    Expression::registerFunctionExpressionMaker<Percent>([](ArgumentPtrVector &&args) {
      static const ArgumentPtr percentValue = Integer(100).clone();
      return divExpr(args.front(), percentValue);
    });

    Expression::registerFunctionExpressionMaker<Min>([](ArgumentPtrVector &&args) {
      return MinMaxExpression(Min(), std::move(args)).clone();
    });

    Expression::registerFunctionExpressionMaker<Max>([](ArgumentPtrVector &&args) {
      return MinMaxExpression(Max(), std::move(args)).clone();
    });

    Expression::registerFunctionExpressionMaker<Sqrt>([](ArgumentPtrVector &&args) {
      static const ArgumentPtr powRate = Rational(1, 2).clone();
      return powExpr(args.front(), powRate);
    });

    Expression::registerFunctionExpressionMaker<Root>([](ArgumentPtrVector &&args) {
      ArgumentPtr lhs = std::move(args.front());
      ArgumentPtr rhs = std::move(args.back());

      if (const auto rhsNum = cast<INumber>(rhs); rhsNum && *rhsNum != Integer(0)) {
        return powExpr(std::move(lhs), Rational(1) / (*rhsNum));
      }

      static const ArgumentPtr one = Integer(1).clone();
      ArgumentPtr invRhs = divExpr(one, rhs);

      return powExpr(std::move(lhs), std::move(invRhs));
    });

    Expression::registerFunctionExpressionMaker<Sin>([](ArgumentPtrVector &&args) {
      return TrigExpression(Sin(), std::move(args.front())).clone();
    });

    Expression::registerFunctionExpressionMaker<Cos>([](ArgumentPtrVector &&args) {
      return TrigExpression(Cos(), std::move(args.front())).clone();
    });

    Expression::registerFunctionExpressionMaker<Tan>([](ArgumentPtrVector &&args) {
      return TrigExpression(Tan(), std::move(args.front())).clone();
    });

    Expression::registerFunctionExpressionMaker<Cot>([](ArgumentPtrVector &&args) {
      return TrigExpression(Cot(), std::move(args.front())).clone();
    });

    Expression::registerFunctionExpressionMaker<Asin>([](ArgumentPtrVector &&args) {
      return InvTrigExpression(Asin(), std::move(args.front())).clone();
    });

    Expression::registerFunctionExpressionMaker<Acos>([](ArgumentPtrVector &&args) {
      return InvTrigExpression(Acos(), std::move(args.front())).clone();
    });

    Expression::registerFunctionExpressionMaker<Atan>([](ArgumentPtrVector &&args) {
      return InvTrigExpression(Atan(), std::move(args.front())).clone();
    });

    Expression::registerFunctionExpressionMaker<Acot>([](ArgumentPtrVector &&args) {
      return InvTrigExpression(Acot(), std::move(args.front())).clone();
    });

    Expression::registerFunctionExpressionMaker<Sinh>([](ArgumentPtrVector &&args) {
      return HyperbExpression(Sinh(), std::move(args.front())).clone();
    });

    Expression::registerFunctionExpressionMaker<Cosh>([](ArgumentPtrVector &&args) {
      return HyperbExpression(Cosh(), std::move(args.front())).clone();
    });

    Expression::registerFunctionExpressionMaker<Tanh>([](ArgumentPtrVector &&args) {
      return HyperbExpression(Tanh(), std::move(args.front())).clone();
    });

    Expression::registerFunctionExpressionMaker<Coth>([](ArgumentPtrVector &&args) {
      return HyperbExpression(Coth(), std::move(args.front())).clone();
    });

    Expression::registerFunctionExpressionMaker<Asinh>([](ArgumentPtrVector &&args) {
      return InvHyperbExpression(Asinh(), std::move(args.front())).clone();
    });

    Expression::registerFunctionExpressionMaker<Acosh>([](ArgumentPtrVector &&args) {
      return InvHyperbExpression(Acosh(), std::move(args.front())).clone();
    });

    Expression::registerFunctionExpressionMaker<Atanh>([](ArgumentPtrVector &&args) {
      return InvHyperbExpression(Atanh(), std::move(args.front())).clone();
    });

    Expression::registerFunctionExpressionMaker<Acoth>([](ArgumentPtrVector &&args) {
      return InvHyperbExpression(Acoth(), std::move(args.front())).clone();
    });

    Expression::registerFunctionExpressionMaker<Deg>([](ArgumentPtrVector &&args) {
      static const ArgumentPtr deg1 = Deg()(Integer(1));
      return mulExpr(args.front(), deg1);
    });
  }
};

const ExpressionConfig config;
}
