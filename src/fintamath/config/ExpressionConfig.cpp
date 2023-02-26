#include "fintamath/expressions/CompExpression.hpp"
#include "fintamath/expressions/DerivativeExpression.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/IndexExpression.hpp"
#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/expressions/SumExpression.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/functions/comparison/Less.hpp"
#include "fintamath/functions/comparison/LessEqv.hpp"
#include "fintamath/functions/comparison/More.hpp"
#include "fintamath/functions/comparison/MoreEqv.hpp"
#include "fintamath/functions/comparison/Neqv.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/Equiv.hpp"
#include "fintamath/functions/logic/Impl.hpp"
#include "fintamath/functions/logic/Nequiv.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"
#include "fintamath/functions/other/Index.hpp"

namespace fintamath {

Parser::Map<ExpressionPtr, ArgumentsPtrVector &&> Expression::expressionBuildersMap;

}

using namespace fintamath;

namespace {

struct ExpressionConfig {
  ExpressionConfig() {
    Expression::registerExpressionBuilder<Add>([](ArgumentsPtrVector &&args) {
      auto expr = std::make_unique<SumExpression>();
      expr->addElement({std::move(args.front())});
      expr->addElement({std::move(args.back())});
      return expr;
    });

    Expression::registerExpressionBuilder<Sub>([](ArgumentsPtrVector &&args) {
      auto expr = std::make_unique<SumExpression>();
      expr->addElement({std::move(args.front())});
      expr->addElement({std::move(args.back()), true});
      return expr;
    });

    Expression::registerExpressionBuilder<Mul>([](ArgumentsPtrVector &&args) {
      auto expr = std::make_unique<MulExpression>();
      expr->addElement({std::move(args.front())});
      expr->addElement({std::move(args.back())});
      return expr;
    });

    Expression::registerExpressionBuilder<Div>([](ArgumentsPtrVector &&args) {
      auto expr = std::make_unique<MulExpression>();
      expr->addElement({std::move(args.front())});
      expr->addElement({std::move(args.back()), true});
      return expr;
    });

    Expression::registerExpressionBuilder<UnaryPlus>([](ArgumentsPtrVector &&args) {
      return std::make_unique<Expression>(std::move(args.front()));
    });

    Expression::registerExpressionBuilder<Eqv>([](ArgumentsPtrVector &&args) {
      return std::make_unique<CompExpression>(Eqv(), std::move(args.front()), std::move(args.back()));
    });

    Expression::registerExpressionBuilder<Neqv>([](ArgumentsPtrVector &&args) {
      return std::make_unique<CompExpression>(Neqv(), std::move(args.front()), std::move(args.back()));
    });

    Expression::registerExpressionBuilder<Less>([](ArgumentsPtrVector &&args) {
      return std::make_unique<CompExpression>(Less(), std::move(args.front()), std::move(args.back()));
    });

    Expression::registerExpressionBuilder<More>([](ArgumentsPtrVector &&args) {
      return std::make_unique<CompExpression>(More(), std::move(args.front()), std::move(args.back()));
    });

    Expression::registerExpressionBuilder<LessEqv>([](ArgumentsPtrVector &&args) {
      return std::make_unique<CompExpression>(LessEqv(), std::move(args.front()), std::move(args.back()));
    });

    Expression::registerExpressionBuilder<MoreEqv>([](ArgumentsPtrVector &&args) {
      return std::make_unique<CompExpression>(MoreEqv(), std::move(args.front()), std::move(args.back()));
    });

    Expression::registerExpressionBuilder<Derivative>([](ArgumentsPtrVector &&args) {
      return std::make_unique<DerivativeExpression>(std::move(args.front()));
    });

    Expression::registerExpressionBuilder<Index>([](ArgumentsPtrVector &&args) {
      return std::make_unique<IndexExpression>(std::move(args.front()), std::move(args.back()));
    });

    Expression::registerExpressionBuilder<Impl>([](ArgumentsPtrVector &&args) {
      MathObjectPtr &lhs = args.front();
      MathObjectPtr &rhs = args.back();

      MathObjectPtr notLhs = Expression::buildRawFunctionExpression(Not(), makeArgumentsPtrVector(std::move(lhs)));

      return Expression::buildRawFunctionExpression(Or(), makeArgumentsPtrVector(std::move(notLhs), std::move(rhs)));
    });

    Expression::registerExpressionBuilder<Equiv>([](ArgumentsPtrVector &&args) {
      MathObjectPtr &lhs = args.front();
      MathObjectPtr &rhs = args.back();

      MathObjectPtr notLhs = Expression::buildRawFunctionExpression(Not(), makeArgumentsPtrVector(lhs->clone()));
      MathObjectPtr notRhs = Expression::buildRawFunctionExpression(Not(), makeArgumentsPtrVector(rhs->clone()));

      MathObjectPtr lhsAndRhs =
          Expression::buildRawFunctionExpression(And(), makeArgumentsPtrVector(std::move(lhs), std::move(rhs)));
      MathObjectPtr notLhsAndNotRhs =
          Expression::buildRawFunctionExpression(And(), makeArgumentsPtrVector(std::move(notLhs), std::move(notRhs)));

      return Expression::buildRawFunctionExpression(
          Or(), makeArgumentsPtrVector(std::move(lhsAndRhs), std::move(notLhsAndNotRhs)));
    });

    Expression::registerExpressionBuilder<Nequiv>([](ArgumentsPtrVector &&args) {
      MathObjectPtr &lhs = args.front();
      MathObjectPtr &rhs = args.back();

      MathObjectPtr notLhs = Expression::buildRawFunctionExpression(Not(), makeArgumentsPtrVector(lhs->clone()));
      MathObjectPtr notRhs = Expression::buildRawFunctionExpression(Not(), makeArgumentsPtrVector(rhs->clone()));

      MathObjectPtr notLhsAndRhs =
          Expression::buildRawFunctionExpression(And(), makeArgumentsPtrVector(std::move(notLhs), std::move(rhs)));
      MathObjectPtr lhsAndNotRhs =
          Expression::buildRawFunctionExpression(And(), makeArgumentsPtrVector(std::move(lhs), std::move(notRhs)));

      return Expression::buildRawFunctionExpression(
          Or(), makeArgumentsPtrVector(std::move(notLhsAndRhs), std::move(lhsAndNotRhs)));
    });
  }
};

const ExpressionConfig config;

}
