#include "fintamath/expressions/CompExpression.hpp"
#include "fintamath/expressions/DerivativeExpression.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/IndexExpression.hpp"
#include "fintamath/expressions/binary/PowExpression.hpp"
#include "fintamath/expressions/polynomial/AndExpression.hpp"
#include "fintamath/expressions/polynomial/MulExpression.hpp"
#include "fintamath/expressions/polynomial/SumExpression.hpp"
#include "fintamath/expressions/unary/InvExpression.hpp"
#include "fintamath/expressions/unary/NegExpression.hpp"
#include "fintamath/expressions/unary/NotExpression.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
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
#include "fintamath/functions/powers/Pow.hpp"
#include <memory>

namespace fintamath {

Parser::Map<ExpressionPtr, ArgumentsPtrVector &&> Expression::expressionBuildersMap;

}

using namespace fintamath;

namespace {

struct ExpressionConfig {
  ExpressionConfig() {
    Expression::registerFunctionExpressionMaker<Add>([](ArgumentsPtrVector &&args) {
      auto expr = std::make_unique<SumExpression>();
      expr->addElement(std::move(args.front()));
      expr->addElement(std::move(args.back()));
      return expr;
    });

    Expression::registerFunctionExpressionMaker<Sub>([](ArgumentsPtrVector &&args) {
      auto expr = std::make_unique<SumExpression>();
      expr->addElement(std::move(args.front()));
      expr->addElement(std::make_unique<NegExpression>(std::move(args.back())));
      return expr;
    });

    Expression::registerFunctionExpressionMaker<Mul>([](ArgumentsPtrVector &&args) {
      auto expr = std::make_unique<MulExpression>();
      expr->addElement(std::move(args.front()));
      expr->addElement(std::move(args.back()));
      return expr;
    });

    Expression::registerFunctionExpressionMaker<Div>([](ArgumentsPtrVector &&args) {
      auto expr = std::make_unique<MulExpression>();
      expr->addElement(std::move(args.front()));
      expr->addElement(std::make_unique<InvExpression>(std::move(args.back())));
      return expr;
    });

    Expression::registerFunctionExpressionMaker<And>([](ArgumentsPtrVector &&args) {
      auto expr = std::make_unique<AndExpression>();
      expr->addElement(std::move(args.front()));
      expr->addElement(std::move(args.back()));
      return expr;
    });

    Expression::registerFunctionExpressionMaker<UnaryPlus>([](ArgumentsPtrVector &&args) {
      return std::make_unique<Expression>(std::move(args.front()));
    });

    Expression::registerFunctionExpressionMaker<Neg>([](ArgumentsPtrVector &&args) {
      return std::make_unique<NegExpression>(std::move(args.front()));
    });

    Expression::registerFunctionExpressionMaker<Pow>([](ArgumentsPtrVector &&args) {
      return std::make_unique<PowExpression>(std::move(args.front()), std::move(args.back()));
    });

    Expression::registerFunctionExpressionMaker<Eqv>([](ArgumentsPtrVector &&args) {
      return std::make_unique<CompExpression>(Eqv(), std::move(args.front()), std::move(args.back()));
    });

    Expression::registerFunctionExpressionMaker<Neqv>([](ArgumentsPtrVector &&args) {
      return std::make_unique<CompExpression>(Neqv(), std::move(args.front()), std::move(args.back()));
    });

    Expression::registerFunctionExpressionMaker<Less>([](ArgumentsPtrVector &&args) {
      return std::make_unique<CompExpression>(Less(), std::move(args.front()), std::move(args.back()));
    });

    Expression::registerFunctionExpressionMaker<More>([](ArgumentsPtrVector &&args) {
      return std::make_unique<CompExpression>(More(), std::move(args.front()), std::move(args.back()));
    });

    Expression::registerFunctionExpressionMaker<LessEqv>([](ArgumentsPtrVector &&args) {
      return std::make_unique<CompExpression>(LessEqv(), std::move(args.front()), std::move(args.back()));
    });

    Expression::registerFunctionExpressionMaker<MoreEqv>([](ArgumentsPtrVector &&args) {
      return std::make_unique<CompExpression>(MoreEqv(), std::move(args.front()), std::move(args.back()));
    });

    Expression::registerFunctionExpressionMaker<Derivative>([](ArgumentsPtrVector &&args) {
      return std::make_unique<DerivativeExpression>(std::move(args.front()));
    });

    Expression::registerFunctionExpressionMaker<Index>([](ArgumentsPtrVector &&args) {
      return std::make_unique<IndexExpression>(std::move(args.front()), std::move(args.back()));
    });

    Expression::registerFunctionExpressionMaker<Not>([](ArgumentsPtrVector &&args) {
      return std::make_unique<NotExpression>(std::move(args.front()));
    });

    Expression::registerFunctionExpressionMaker<Impl>([](ArgumentsPtrVector &&args) {
      MathObjectPtr &lhs = args.front();
      MathObjectPtr &rhs = args.back();

      MathObjectPtr notLhs = Expression::makeRawFunctionExpression(Not(), makeArgumentsPtrVector(std::move(lhs)));

      return Expression::makeRawFunctionExpression(Or(), makeArgumentsPtrVector(std::move(notLhs), std::move(rhs)));
    });

    Expression::registerFunctionExpressionMaker<Equiv>([](ArgumentsPtrVector &&args) {
      MathObjectPtr &lhs = args.front();
      MathObjectPtr &rhs = args.back();

      MathObjectPtr notLhs = Expression::makeRawFunctionExpression(Not(), makeArgumentsPtrVector(lhs->clone()));
      MathObjectPtr notRhs = Expression::makeRawFunctionExpression(Not(), makeArgumentsPtrVector(rhs->clone()));

      MathObjectPtr lhsAndRhs =
          Expression::makeRawFunctionExpression(And(), makeArgumentsPtrVector(std::move(lhs), std::move(rhs)));
      MathObjectPtr notLhsAndNotRhs =
          Expression::makeRawFunctionExpression(And(), makeArgumentsPtrVector(std::move(notLhs), std::move(notRhs)));

      return Expression::makeRawFunctionExpression(
          Or(), makeArgumentsPtrVector(std::move(lhsAndRhs), std::move(notLhsAndNotRhs)));
    });

    Expression::registerFunctionExpressionMaker<Nequiv>([](ArgumentsPtrVector &&args) {
      MathObjectPtr &lhs = args.front();
      MathObjectPtr &rhs = args.back();

      MathObjectPtr notLhs = Expression::makeRawFunctionExpression(Not(), makeArgumentsPtrVector(lhs->clone()));
      MathObjectPtr notRhs = Expression::makeRawFunctionExpression(Not(), makeArgumentsPtrVector(rhs->clone()));

      MathObjectPtr notLhsAndRhs =
          Expression::makeRawFunctionExpression(And(), makeArgumentsPtrVector(std::move(notLhs), std::move(rhs)));
      MathObjectPtr lhsAndNotRhs =
          Expression::makeRawFunctionExpression(And(), makeArgumentsPtrVector(std::move(lhs), std::move(notRhs)));

      return Expression::makeRawFunctionExpression(
          Or(), makeArgumentsPtrVector(std::move(notLhsAndRhs), std::move(lhsAndNotRhs)));
    });
  }
};

const ExpressionConfig config;

}
