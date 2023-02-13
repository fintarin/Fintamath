#include "fintamath/expressions/DerivativeExpression.hpp"
#include "fintamath/expressions/EqvExpression.hpp"
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

Parser::Map<ExpressionPtr, ArgumentsVector> Expression::expressionBuildersMap;

}

using namespace fintamath;

namespace {

struct ExpressionConfig {
  ExpressionConfig() {
    Expression::registerExpressionBuilder<Add>([](const ArgumentsVector &args) {
      auto expr = std::make_unique<SumExpression>();
      expr->addElement({args.front().get().clone()});
      expr->addElement({args.back().get().clone()});
      return expr;
    });

    Expression::registerExpressionBuilder<Sub>([](const ArgumentsVector &args) {
      auto expr = std::make_unique<SumExpression>();
      expr->addElement({args.front().get().clone()});
      expr->addElement({args.back().get().clone(), true});
      return expr;
    });

    Expression::registerExpressionBuilder<Mul>([](const ArgumentsVector &args) {
      auto expr = std::make_unique<MulExpression>();
      expr->addElement({args.front().get().clone()});
      expr->addElement({args.back().get().clone()});
      return expr;
    });

    Expression::registerExpressionBuilder<Div>([](const ArgumentsVector &args) {
      auto expr = std::make_unique<MulExpression>();
      expr->addElement({args.front().get().clone()});
      expr->addElement({args.back().get().clone(), true});
      return expr;
    });

    Expression::registerExpressionBuilder<UnaryPlus>([](const ArgumentsVector &args) {
      return std::make_unique<Expression>(args.front().get());
    });

    Expression::registerExpressionBuilder<Eqv>([](const ArgumentsVector &args) {
      return std::make_unique<EqvExpression>(Eqv(), args.front().get(), args.back().get());
    });

    Expression::registerExpressionBuilder<Neqv>([](const ArgumentsVector &args) {
      return std::make_unique<EqvExpression>(Neqv(), args.front().get(), args.back().get());
    });

    Expression::registerExpressionBuilder<Less>([](const ArgumentsVector &args) {
      return std::make_unique<EqvExpression>(Less(), args.front().get(), args.back().get());
    });

    Expression::registerExpressionBuilder<More>([](const ArgumentsVector &args) {
      return std::make_unique<EqvExpression>(More(), args.front().get(), args.back().get());
    });

    Expression::registerExpressionBuilder<LessEqv>([](const ArgumentsVector &args) {
      return std::make_unique<EqvExpression>(LessEqv(), args.front().get(), args.back().get());
    });

    Expression::registerExpressionBuilder<MoreEqv>([](const ArgumentsVector &args) {
      return std::make_unique<EqvExpression>(MoreEqv(), args.front().get(), args.back().get());
    });

    Expression::registerExpressionBuilder<Derivative>([](const ArgumentsVector &args) {
      return std::make_unique<DerivativeExpression>(args.front().get());
    });

    Expression::registerExpressionBuilder<Index>([](const ArgumentsVector &args) {
      return std::make_unique<IndexExpression>(args.front().get(), args.back().get());
    });

    Expression::registerExpressionBuilder<Impl>([](const ArgumentsVector &args) {
      const IMathObject &lhs = args.front().get();
      const IMathObject &rhs = args.back().get();
      const MathObjectPtr notLhs = Expression::buildRawFunctionExpression(Not(), {lhs});
      return Expression::buildRawFunctionExpression(Or(), {*notLhs, rhs});
    });

    Expression::registerExpressionBuilder<Equiv>([](const ArgumentsVector &args) {
      const IMathObject &lhs = args.front().get();
      const IMathObject &rhs = args.back().get();
      const MathObjectPtr notLhs = Expression::buildRawFunctionExpression(Not(), {lhs});
      const MathObjectPtr notRhs = Expression::buildRawFunctionExpression(Not(), {rhs});
      const MathObjectPtr lhsAndRhs = Expression::buildRawFunctionExpression(And(), {lhs, rhs});
      const MathObjectPtr notLhsAndNotRhs = Expression::buildRawFunctionExpression(And(), {*notLhs, *notRhs});
      return Expression::buildRawFunctionExpression(Or(), {*lhsAndRhs, *notLhsAndNotRhs});
    });

    Expression::registerExpressionBuilder<Nequiv>([](const ArgumentsVector &args) {
      const IMathObject &lhs = args.front().get();
      const IMathObject &rhs = args.back().get();
      const MathObjectPtr notLhs = Expression::buildRawFunctionExpression(Not(), {lhs});
      const MathObjectPtr notRhs = Expression::buildRawFunctionExpression(Not(), {rhs});
      const MathObjectPtr notLhsAndRhs = Expression::buildRawFunctionExpression(And(), {*notLhs, rhs});
      const MathObjectPtr lhsAndNotRhs = Expression::buildRawFunctionExpression(And(), {lhs, *notRhs});
      return Expression::buildRawFunctionExpression(Or(), {*notLhsAndRhs, *lhsAndNotRhs});
    });
  }
};

const ExpressionConfig config;

}
