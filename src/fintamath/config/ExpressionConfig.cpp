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

Parser::Map<std::unique_ptr<IMathObject>, const ArgumentPtrVector &> &Expression::getExpressionMakers() {
  static Parser::Map<std::unique_ptr<IMathObject>, const ArgumentPtrVector &> maker;
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
      if (ArgumentPtr arg = IFunction::parse(token, IFunction::Type::Binary)) {
        return std::make_unique<Term>(token, arg);
      }

      if (ArgumentPtr arg = IFunction::parse(token)) {
        return std::make_unique<Term>(token, arg);
      }

      return std::unique_ptr<Term>();
    });

    Expression::registerTermsMaker([](const Token &token) {
      if (ArgumentPtr arg = ILiteral::parse(token)) {
        return std::make_unique<Term>(token, arg);
      }

      return std::unique_ptr<Term>();
    });

    Expression::registerTermsMaker([](const Token &token) {
      if (ArgumentPtr arg = INumber::parse(token)) {
        return std::make_unique<Term>(token, arg->toMinimalObject());
      }

      return std::unique_ptr<Term>();
    });
  }

  static void registerFunctionExpressionMakers() {
    Expression::registerFunctionExpressionMaker<Add, true>([](const ArgumentPtrVector &args) {
      return AddExpression(args).clone();
    });

    Expression::registerFunctionExpressionMaker<Sub>([](const ArgumentPtrVector &args) {
      return AddExpression(ArgumentPtrVector{args.front(), negExpr(args.back())}).clone();
    });

    Expression::registerFunctionExpressionMaker<Mul, true>([](const ArgumentPtrVector &args) {
      return MulExpression(args).clone();
    });

    Expression::registerFunctionExpressionMaker<Div>([](const ArgumentPtrVector &args) {
      return DivExpression(args.front(), args.back()).clone();
    });

    Expression::registerFunctionExpressionMaker<Frac>([](const ArgumentPtrVector &args) {
      return DivExpression(args.front(), args.back()).clone();
    });

    Expression::registerFunctionExpressionMaker<And, true>([](const ArgumentPtrVector &args) {
      return AndExpression(args).clone();
    });

    Expression::registerFunctionExpressionMaker<Or, true>([](const ArgumentPtrVector &args) {
      return OrExpression(args).clone();
    });

    Expression::registerFunctionExpressionMaker<Pow>([](const ArgumentPtrVector &args) {
      return PowExpression(args.front(), args.back()).clone();
    });

    Expression::registerFunctionExpressionMaker<PowF>([](const ArgumentPtrVector &args) {
      return PowExpression(args.front(), args.back()).clone();
    });

    Expression::registerFunctionExpressionMaker<Eqv>([](const ArgumentPtrVector &args) {
      return CompExpression(Eqv(), args.front(), args.back()).clone();
    });

    Expression::registerFunctionExpressionMaker<Neqv>([](const ArgumentPtrVector &args) {
      return CompExpression(Neqv(), args.front(), args.back()).clone();
    });

    Expression::registerFunctionExpressionMaker<Less>([](const ArgumentPtrVector &args) {
      return CompExpression(Less(), args.front(), args.back()).clone();
    });

    Expression::registerFunctionExpressionMaker<More>([](const ArgumentPtrVector &args) {
      return CompExpression(More(), args.front(), args.back()).clone();
    });

    Expression::registerFunctionExpressionMaker<LessEqv>([](const ArgumentPtrVector &args) {
      return CompExpression(LessEqv(), args.front(), args.back()).clone();
    });

    Expression::registerFunctionExpressionMaker<MoreEqv>([](const ArgumentPtrVector &args) {
      return CompExpression(MoreEqv(), args.front(), args.back()).clone();
    });

    Expression::registerFunctionExpressionMaker<Index>([](const ArgumentPtrVector &args) {
      const ArgumentPtr &lhs = args.front();
      const ArgumentPtr &rhs = args.back();
      const Index func;

      if (!func.doArgsMatch({*lhs, *rhs})) {
        throw InvalidInputBinaryOperatorException(func.toString(), lhs->toString(), rhs->toString());
      }

      ArgumentPtr res = func(*args.front(), *args.back());
      return Expression(res).clone(); // TODO: looks weird
    });

    Expression::registerFunctionExpressionMaker<Impl>([](const ArgumentPtrVector &args) {
      const ArgumentPtr &lhs = args.front();
      const ArgumentPtr &rhs = args.back();

      ArgumentPtr notLhs = notExpr(lhs);

      return orExpr(notLhs, rhs);
    });

    Expression::registerFunctionExpressionMaker<Equiv>([](const ArgumentPtrVector &args) {
      const ArgumentPtr &lhs = args.front();
      const ArgumentPtr &rhs = args.back();

      ArgumentPtr notLhs = notExpr(lhs);
      ArgumentPtr notRhs = notExpr(rhs);

      ArgumentPtr lhsAndRhs = andExpr(lhs, rhs);
      ArgumentPtr notLhsAndNotRhs = andExpr(notLhs, notRhs);

      return orExpr(lhsAndRhs, notLhsAndNotRhs);
    });

    Expression::registerFunctionExpressionMaker<Nequiv>([](const ArgumentPtrVector &args) {
      const ArgumentPtr &lhs = args.front();
      const ArgumentPtr &rhs = args.back();

      ArgumentPtr notLhs = notExpr(lhs);
      ArgumentPtr notRhs = notExpr(rhs);

      ArgumentPtr notLhsAndRhs = andExpr(notLhs, rhs);
      ArgumentPtr lhsAndNotRhs = andExpr(lhs, notRhs);

      return orExpr(notLhsAndRhs, lhsAndNotRhs);
    });

    Expression::registerFunctionExpressionMaker<Neg>([](const ArgumentPtrVector &args) {
      return mulExpr(Integer(-1).clone(), args.front());
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
      return LogExpression(E().clone(), args.front()).clone();
    });

    Expression::registerFunctionExpressionMaker<Lb>([](const ArgumentPtrVector &args) {
      return LogExpression(Integer(2).clone(), args.front()).clone();
    });

    Expression::registerFunctionExpressionMaker<Lg>([](const ArgumentPtrVector &args) {
      return LogExpression(Integer(10).clone(), args.front()).clone();
    });

    Expression::registerFunctionExpressionMaker<Exp>([](const ArgumentPtrVector &args) {
      return powExpr(E().clone(), args.front());
    });

    Expression::registerFunctionExpressionMaker<Percent>([](const ArgumentPtrVector &args) {
      static const ArgumentPtr PERCENT_VALUE = Integer(100).clone();
      return divExpr(args.front(), PERCENT_VALUE);
    });

    Expression::registerFunctionExpressionMaker<Min>([](const ArgumentPtrVector &args) {
      return MinMaxExpression(Min(), args).clone();
    });

    Expression::registerFunctionExpressionMaker<Max>([](const ArgumentPtrVector &args) {
      return MinMaxExpression(Max(), args).clone();
    });

    Expression::registerFunctionExpressionMaker<Sqrt>([](const ArgumentPtrVector &args) {
      return powExpr(args.front(), Rational(1, 2).clone());
    });

    Expression::registerFunctionExpressionMaker<Root>([](const ArgumentPtrVector &args) {
      if (const auto num = cast<INumber>(args.back())) {
        return powExpr(args.front(), Rational(1) / (*num));
      }

      return powExpr(args.front(), divExpr(Integer(1).clone(), args.back()));
    });

    Expression::registerFunctionExpressionMaker<Sin>([](const ArgumentPtrVector &args) {
      return TrigExpression(Sin(), args.front()).clone();
    });

    Expression::registerFunctionExpressionMaker<Cos>([](const ArgumentPtrVector &args) {
      return TrigExpression(Cos(), args.front()).clone();
    });

    Expression::registerFunctionExpressionMaker<Tan>([](const ArgumentPtrVector &args) {
      return TrigExpression(Tan(), args.front()).clone();
    });

    Expression::registerFunctionExpressionMaker<Cot>([](const ArgumentPtrVector &args) {
      return TrigExpression(Cot(), args.front()).clone();
    });

    Expression::registerFunctionExpressionMaker<Asin>([](const ArgumentPtrVector &args) {
      return InvTrigExpression(Asin(), args.front()).clone();
    });

    Expression::registerFunctionExpressionMaker<Acos>([](const ArgumentPtrVector &args) {
      return InvTrigExpression(Acos(), args.front()).clone();
    });

    Expression::registerFunctionExpressionMaker<Atan>([](const ArgumentPtrVector &args) {
      return InvTrigExpression(Atan(), args.front()).clone();
    });

    Expression::registerFunctionExpressionMaker<Acot>([](const ArgumentPtrVector &args) {
      return InvTrigExpression(Acot(), args.front()).clone();
    });

    Expression::registerFunctionExpressionMaker<Sinh>([](const ArgumentPtrVector &args) {
      return HyperbExpression(Sinh(), args.front()).clone();
    });

    Expression::registerFunctionExpressionMaker<Cosh>([](const ArgumentPtrVector &args) {
      return HyperbExpression(Cosh(), args.front()).clone();
    });

    Expression::registerFunctionExpressionMaker<Tanh>([](const ArgumentPtrVector &args) {
      return HyperbExpression(Tanh(), args.front()).clone();
    });

    Expression::registerFunctionExpressionMaker<Coth>([](const ArgumentPtrVector &args) {
      return HyperbExpression(Coth(), args.front()).clone();
    });

    Expression::registerFunctionExpressionMaker<Asinh>([](const ArgumentPtrVector &args) {
      return InvHyperbExpression(Asinh(), args.front()).clone();
    });

    Expression::registerFunctionExpressionMaker<Acosh>([](const ArgumentPtrVector &args) {
      return InvHyperbExpression(Acosh(), args.front()).clone();
    });

    Expression::registerFunctionExpressionMaker<Atanh>([](const ArgumentPtrVector &args) {
      return InvHyperbExpression(Atanh(), args.front()).clone();
    });

    Expression::registerFunctionExpressionMaker<Acoth>([](const ArgumentPtrVector &args) {
      return InvHyperbExpression(Acoth(), args.front()).clone();
    });

    Expression::registerFunctionExpressionMaker<Deg>([](const ArgumentPtrVector &args) {
      static const ArgumentPtr deg1 = Deg()(Integer(1));
      return mulExpr(args.front(), deg1);
    });
  }
};

const ExpressionConfig config;
}
