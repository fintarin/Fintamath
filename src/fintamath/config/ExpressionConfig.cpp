#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/binary/CompExpression.hpp"
#include "fintamath/expressions/binary/IndexExpression.hpp"
#include "fintamath/expressions/binary/PowExpression.hpp"
#include "fintamath/expressions/polynomial/AndExpression.hpp"
#include "fintamath/expressions/polynomial/MulExpression.hpp"
#include "fintamath/expressions/polynomial/OrExpression.hpp"
#include "fintamath/expressions/polynomial/SumExpression.hpp"
#include "fintamath/expressions/unary/DerivativeExpression.hpp"
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

namespace fintamath {

Parser::Map<std::unique_ptr<IExpression>, ArgumentsPtrVector &&> Expression::expressionBuildersMap;

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

    Expression::registerFunctionExpressionMaker<Pow>([](ArgumentsPtrVector &&args) {
      return std::make_unique<PowExpression>(std::move(args.front()), std::move(args.back()));
    });

    Expression::registerFunctionExpressionMaker<Neg>([](ArgumentsPtrVector &&args) {
      return std::make_unique<NegExpression>(std::move(args.front()));
    });

    Expression::registerFunctionExpressionMaker<UnaryPlus>([](ArgumentsPtrVector &&args) {
      return std::make_unique<Expression>(std::move(args.front()));
    });

    Expression::registerFunctionExpressionMaker<And>([](ArgumentsPtrVector &&args) {
      auto expr = std::make_unique<AndExpression>();
      expr->addElement(std::move(args.front()));
      expr->addElement(std::move(args.back()));
      return expr;
    });

    Expression::registerFunctionExpressionMaker<Or>([](ArgumentsPtrVector &&args) {
      auto expr = std::make_unique<OrExpression>();
      expr->addElement(std::move(args.front()));
      expr->addElement(std::move(args.back()));
      return expr;
    });

    Expression::registerFunctionExpressionMaker<Not>([](ArgumentsPtrVector &&args) {
      return std::make_unique<NotExpression>(std::move(args.front()));
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

    Expression::registerFunctionExpressionMaker<Impl>([](ArgumentsPtrVector &&args) {
      std::unique_ptr<IMathObject> &lhs = args.front();
      std::unique_ptr<IMathObject> &rhs = args.back();

      std::unique_ptr<IMathObject> notLhs =
          Expression::makeRawFunctionExpression(Not(), makeArgumentsPtrVector(std::move(lhs)));

      return Expression::makeRawFunctionExpression(Or(), makeArgumentsPtrVector(std::move(notLhs), std::move(rhs)));
    });

    Expression::registerFunctionExpressionMaker<Equiv>([](ArgumentsPtrVector &&args) {
      std::unique_ptr<IMathObject> &lhs = args.front();
      std::unique_ptr<IMathObject> &rhs = args.back();

      std::unique_ptr<IMathObject> notLhs =
          Expression::makeRawFunctionExpression(Not(), makeArgumentsPtrVector(lhs->clone()));
      std::unique_ptr<IMathObject> notRhs =
          Expression::makeRawFunctionExpression(Not(), makeArgumentsPtrVector(rhs->clone()));

      std::unique_ptr<IMathObject> lhsAndRhs =
          Expression::makeRawFunctionExpression(And(), makeArgumentsPtrVector(std::move(lhs), std::move(rhs)));
      std::unique_ptr<IMathObject> notLhsAndNotRhs =
          Expression::makeRawFunctionExpression(And(), makeArgumentsPtrVector(std::move(notLhs), std::move(notRhs)));

      return Expression::makeRawFunctionExpression(
          Or(), makeArgumentsPtrVector(std::move(lhsAndRhs), std::move(notLhsAndNotRhs)));
    });

    Expression::registerFunctionExpressionMaker<Nequiv>([](ArgumentsPtrVector &&args) {
      std::unique_ptr<IMathObject> &lhs = args.front();
      std::unique_ptr<IMathObject> &rhs = args.back();

      std::unique_ptr<IMathObject> notLhs =
          Expression::makeRawFunctionExpression(Not(), makeArgumentsPtrVector(lhs->clone()));
      std::unique_ptr<IMathObject> notRhs =
          Expression::makeRawFunctionExpression(Not(), makeArgumentsPtrVector(rhs->clone()));

      std::unique_ptr<IMathObject> notLhsAndRhs =
          Expression::makeRawFunctionExpression(And(), makeArgumentsPtrVector(std::move(notLhs), std::move(rhs)));
      std::unique_ptr<IMathObject> lhsAndNotRhs =
          Expression::makeRawFunctionExpression(And(), makeArgumentsPtrVector(std::move(lhs), std::move(notRhs)));

      return Expression::makeRawFunctionExpression(
          Or(), makeArgumentsPtrVector(std::move(notLhsAndRhs), std::move(lhsAndNotRhs)));
    });
  }
};

const ExpressionConfig config;

}
