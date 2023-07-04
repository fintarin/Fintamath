#include "fintamath/expressions/Expression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
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
#include "fintamath/expressions/unary/HyperbolicExpression.hpp"
#include "fintamath/expressions/unary/NegExpression.hpp"
#include "fintamath/expressions/unary/NotExpression.hpp"
#include "fintamath/expressions/unary/TrigonometryExpression.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
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
#include "fintamath/functions/other/Index.hpp"
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
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"

namespace fintamath {

Parser::Vector<std::unique_ptr<Term>, const Token &> &Expression::getTermMakers() {
  static Parser::Vector<std::unique_ptr<Term>, const Token &> maker;
  return maker;
}

Parser::Map<std::unique_ptr<IMathObject>, const ArgumentsPtrVector &> &Expression::getExpressionMakers() {
  static Parser::Map<std::unique_ptr<IMathObject>, const ArgumentsPtrVector &> maker;
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
      ArgumentsPtrVector args;

      for (auto i = size_t(IFunction::Type::None); i <= size_t(IOperator::Priority::Any); i++) {
        if (ArgumentPtr arg = IOperator::parse(token, IOperator::Priority(i))) {
          args.emplace_back(arg);
        }
      }

      if (args.empty()) {
        for (auto i = size_t(IFunction::Type::None); i <= size_t(IFunction::Type::Any); i++) {
          if (ArgumentPtr arg = IFunction::parse(token, IFunction::Type(i))) {
            args.emplace_back(arg);
          }
        }
      }

      if (!args.empty()) {
        return std::make_unique<Term>(token, args);
      }

      return std::unique_ptr<Term>();
    });

    Expression::registerTermsMaker([](const Token &token) {
      if (ArgumentPtr arg = ILiteral::parse(token)) {
        return std::make_unique<Term>(token, ArgumentsPtrVector{arg});
      }

      return std::unique_ptr<Term>();
    });

    Expression::registerTermsMaker([](const Token &token) {
      if (ArgumentPtr arg = INumber::parse(token)) {
        return std::make_unique<Term>(token, ArgumentsPtrVector{arg});
      }

      return std::unique_ptr<Term>();
    });
  }

  static void registerFunctionExpressionMakers() {
    Expression::registerFunctionExpressionMaker<Add, true>([](const ArgumentsPtrVector &args) {
      return std::make_unique<AddExpression>(args);
    });

    Expression::registerFunctionExpressionMaker<Sub>([](const ArgumentsPtrVector &args) {
      return std::make_unique<AddExpression>(
          ArgumentsPtrVector{args.front(), std::make_shared<NegExpression>(args.back())});
    });

    Expression::registerFunctionExpressionMaker<Mul, true>([](const ArgumentsPtrVector &args) {
      return std::make_unique<MulExpression>(args);
    });

    Expression::registerFunctionExpressionMaker<Div>([](const ArgumentsPtrVector &args) {
      return std::make_unique<DivExpression>(args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<And, true>([](const ArgumentsPtrVector &args) {
      return std::make_unique<AndExpression>(args);
    });

    Expression::registerFunctionExpressionMaker<Or, true>([](const ArgumentsPtrVector &args) {
      return std::make_unique<OrExpression>(args);
    });

    Expression::registerFunctionExpressionMaker<Pow>([](const ArgumentsPtrVector &args) {
      return std::make_unique<PowExpression>(args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<Eqv>([](const ArgumentsPtrVector &args) {
      return std::make_unique<CompExpression>(Eqv(), args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<Neqv>([](const ArgumentsPtrVector &args) {
      return std::make_unique<CompExpression>(Neqv(), args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<Less>([](const ArgumentsPtrVector &args) {
      return std::make_unique<CompExpression>(Less(), args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<More>([](const ArgumentsPtrVector &args) {
      return std::make_unique<CompExpression>(More(), args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<LessEqv>([](const ArgumentsPtrVector &args) {
      return std::make_unique<CompExpression>(LessEqv(), args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<MoreEqv>([](const ArgumentsPtrVector &args) {
      return std::make_unique<CompExpression>(MoreEqv(), args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<Index>([](const ArgumentsPtrVector &args) {
      const ArgumentPtr &lhs = args.front();
      const ArgumentPtr &rhs = args.back();
      const Index func;

      if (!func.doArgsMatch({*lhs, *rhs})) {
        throw InvalidInputBinaryOperatorException(func.toString(), lhs->toString(), rhs->toString());
      }

      ArgumentPtr res = func(*args.front(), *args.back());
      return std::make_unique<Expression>(res);
    });

    Expression::registerFunctionExpressionMaker<Impl>([](const ArgumentsPtrVector &args) {
      const ArgumentPtr &lhs = args.front();
      const ArgumentPtr &rhs = args.back();

      ArgumentPtr notLhs = makeExpr(Not(), lhs);

      return makeExpr(Or(), notLhs, rhs);
    });

    Expression::registerFunctionExpressionMaker<Equiv>([](const ArgumentsPtrVector &args) {
      const ArgumentPtr &lhs = args.front();
      const ArgumentPtr &rhs = args.back();

      ArgumentPtr notLhs = makeExpr(Not(), lhs);
      ArgumentPtr notRhs = makeExpr(Not(), rhs);

      ArgumentPtr lhsAndRhs = makeExpr(And(), lhs, rhs);
      ArgumentPtr notLhsAndNotRhs = makeExpr(And(), notLhs, notRhs);

      return makeExpr(Or(), lhsAndRhs, notLhsAndNotRhs);
    });

    Expression::registerFunctionExpressionMaker<Nequiv>([](const ArgumentsPtrVector &args) {
      const ArgumentPtr &lhs = args.front();
      const ArgumentPtr &rhs = args.back();

      ArgumentPtr notLhs = makeExpr(Not(), lhs);
      ArgumentPtr notRhs = makeExpr(Not(), rhs);

      ArgumentPtr notLhsAndRhs = makeExpr(And(), notLhs, rhs);
      ArgumentPtr lhsAndNotRhs = makeExpr(And(), lhs, notRhs);

      return makeExpr(Or(), notLhsAndRhs, lhsAndNotRhs);
    });

    Expression::registerFunctionExpressionMaker<Neg>([](const ArgumentsPtrVector &args) {
      return std::make_unique<NegExpression>(args.front());
    });

    Expression::registerFunctionExpressionMaker<UnaryPlus>([](const ArgumentsPtrVector &args) {
      return std::make_unique<Expression>(args.front());
    });

    Expression::registerFunctionExpressionMaker<Not>([](const ArgumentsPtrVector &args) {
      return std::make_unique<NotExpression>(args.front());
    });

    Expression::registerFunctionExpressionMaker<Derivative>([](const ArgumentsPtrVector &args) {
      return std::make_unique<DerivativeExpression>(args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<Integral>([](const ArgumentsPtrVector &args) {
      return std::make_unique<IntegralExpression>(args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<Log>([](const ArgumentsPtrVector &args) {
      return std::make_unique<LogExpression>(args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<Ln>([](const ArgumentsPtrVector &args) {
      return std::make_unique<LogExpression>(E().clone(), args.front());
    });

    Expression::registerFunctionExpressionMaker<Lb>([](const ArgumentsPtrVector &args) {
      return std::make_unique<LogExpression>(std::make_shared<Integer>(2), args.front());
    });

    Expression::registerFunctionExpressionMaker<Lg>([](const ArgumentsPtrVector &args) {
      return std::make_unique<LogExpression>(std::make_shared<Integer>(10), args.front());
    });

    Expression::registerFunctionExpressionMaker<Exp>([](const ArgumentsPtrVector &args) {
      return makeExpr(Pow(), E().clone(), args.front());
    });

    Expression::registerFunctionExpressionMaker<Percent>([](const ArgumentsPtrVector &args) {
      static const auto PERCENT_VALUE = std::make_shared<Integer>(100);
      return makeExpr(Div(), args.front(), PERCENT_VALUE);
    });

    Expression::registerFunctionExpressionMaker<Min>([](const ArgumentsPtrVector &args) {
      return std::make_unique<MinMaxExpression>(Min(), args);
    });

    Expression::registerFunctionExpressionMaker<Max>([](const ArgumentsPtrVector &args) {
      return std::make_unique<MinMaxExpression>(Max(), args);
    });

    Expression::registerFunctionExpressionMaker<Sqrt>([](const ArgumentsPtrVector &args) {
      return makeExpr(Pow(), args.front(), std::make_shared<Rational>(1, 2));
    });

    Expression::registerFunctionExpressionMaker<Sin>([](const ArgumentsPtrVector &args) {
      return std::make_unique<TrigonometryExpression>(Sin(), args.front());
    });

    Expression::registerFunctionExpressionMaker<Cos>([](const ArgumentsPtrVector &args) {
      return std::make_unique<TrigonometryExpression>(Cos(), args.front());
    });

    Expression::registerFunctionExpressionMaker<Tan>([](const ArgumentsPtrVector &args) {
      return std::make_unique<TrigonometryExpression>(Tan(), args.front());
    });

    Expression::registerFunctionExpressionMaker<Cot>([](const ArgumentsPtrVector &args) {
      return std::make_unique<TrigonometryExpression>(Cot(), args.front());
    });

    Expression::registerFunctionExpressionMaker<Asin>([](const ArgumentsPtrVector &args) {
      return std::make_unique<TrigonometryExpression>(Asin(), args.front());
    });

    Expression::registerFunctionExpressionMaker<Acos>([](const ArgumentsPtrVector &args) {
      return std::make_unique<TrigonometryExpression>(Acos(), args.front());
    });

    Expression::registerFunctionExpressionMaker<Atan>([](const ArgumentsPtrVector &args) {
      return std::make_unique<TrigonometryExpression>(Atan(), args.front());
    });

    Expression::registerFunctionExpressionMaker<Acot>([](const ArgumentsPtrVector &args) {
      return std::make_unique<TrigonometryExpression>(Acot(), args.front());
    });

    Expression::registerFunctionExpressionMaker<Sinh>([](const ArgumentsPtrVector &args) {
      return std::make_unique<HyperbolicExpression>(Sinh(), args.front());
    });

    Expression::registerFunctionExpressionMaker<Cosh>([](const ArgumentsPtrVector &args) {
      return std::make_unique<HyperbolicExpression>(Cosh(), args.front());
    });

    Expression::registerFunctionExpressionMaker<Tanh>([](const ArgumentsPtrVector &args) {
      return std::make_unique<HyperbolicExpression>(Tanh(), args.front());
    });

    Expression::registerFunctionExpressionMaker<Coth>([](const ArgumentsPtrVector &args) {
      return std::make_unique<HyperbolicExpression>(Coth(), args.front());
    });

    Expression::registerFunctionExpressionMaker<Asinh>([](const ArgumentsPtrVector &args) {
      return std::make_unique<HyperbolicExpression>(Asinh(), args.front());
    });

    Expression::registerFunctionExpressionMaker<Acosh>([](const ArgumentsPtrVector &args) {
      return std::make_unique<HyperbolicExpression>(Acosh(), args.front());
    });

    Expression::registerFunctionExpressionMaker<Atanh>([](const ArgumentsPtrVector &args) {
      return std::make_unique<HyperbolicExpression>(Atanh(), args.front());
    });

    Expression::registerFunctionExpressionMaker<Acoth>([](const ArgumentsPtrVector &args) {
      return std::make_unique<HyperbolicExpression>(Acoth(), args.front());
    });
  }
};

const ExpressionConfig config;
}
