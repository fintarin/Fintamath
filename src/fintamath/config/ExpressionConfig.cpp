#include "fintamath/expressions/Expression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/binary/CompExpression.hpp"
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
#include "fintamath/functions/arithmetic/Inv.hpp"
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

Parser::Map<shared_ptr<IExpression>, const ArgumentsPtrVector &> Expression::expressionBuildersMap;

}

using namespace fintamath;

namespace {

struct ExpressionConfig {
  ExpressionConfig() {
    Expression::registerFunctionExpressionMaker<Add, true>([](const ArgumentsPtrVector &args) {
      return make_shared<SumExpression>(args);
    });

    Expression::registerFunctionExpressionMaker<Sub>([](const ArgumentsPtrVector &args) {
      return make_shared<SumExpression>(ArgumentsPtrVector{args.front(), make_shared<NegExpression>(args.back())});
    });

    Expression::registerFunctionExpressionMaker<Mul, true>([](const ArgumentsPtrVector &args) {
      return make_shared<MulExpression>(args);
    });

    Expression::registerFunctionExpressionMaker<Div>([](const ArgumentsPtrVector &args) {
      return make_shared<MulExpression>(ArgumentsPtrVector{args.front(), make_shared<InvExpression>(args.back())});
    });

    Expression::registerFunctionExpressionMaker<And, true>([](const ArgumentsPtrVector &args) {
      return make_shared<AndExpression>(args);
    });

    Expression::registerFunctionExpressionMaker<Or, true>([](const ArgumentsPtrVector &args) {
      return make_shared<OrExpression>(args);
    });

    Expression::registerFunctionExpressionMaker<Pow>([](const ArgumentsPtrVector &args) {
      return make_shared<PowExpression>(args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<Eqv>([](const ArgumentsPtrVector &args) {
      return make_shared<CompExpression>(Eqv(), args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<Neqv>([](const ArgumentsPtrVector &args) {
      return make_shared<CompExpression>(Neqv(), args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<Less>([](const ArgumentsPtrVector &args) {
      return make_shared<CompExpression>(Less(), args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<More>([](const ArgumentsPtrVector &args) {
      return make_shared<CompExpression>(More(), args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<LessEqv>([](const ArgumentsPtrVector &args) {
      return make_shared<CompExpression>(LessEqv(), args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<MoreEqv>([](const ArgumentsPtrVector &args) {
      return make_shared<CompExpression>(MoreEqv(), args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<Index>([](const ArgumentsPtrVector &args) {
      const ArgumentPtr &lhs = args.front();
      const ArgumentPtr &rhs = args.back();
      const Index func;

      if (!func.doArgsMatch({*lhs, *rhs})) {
        throw InvalidInputBinaryOpearatorException(func.toString(), lhs->toString(), rhs->toString());
      }

      ArgumentPtr res = func(*args.front(), *args.back());
      return std::make_shared<Expression>(res);
    });

    Expression::registerFunctionExpressionMaker<Impl>([](const ArgumentsPtrVector &args) {
      const ArgumentPtr &lhs = args.front();
      const ArgumentPtr &rhs = args.back();

      ArgumentPtr notLhs = makeRawFunctionExpression(Not(), {lhs});

      return makeRawFunctionExpression(Or(), {notLhs, rhs});
    });

    Expression::registerFunctionExpressionMaker<Equiv>([](const ArgumentsPtrVector &args) {
      const ArgumentPtr &lhs = args.front();
      const ArgumentPtr &rhs = args.back();

      ArgumentPtr notLhs = makeRawFunctionExpression(Not(), {lhs});
      ArgumentPtr notRhs = makeRawFunctionExpression(Not(), {rhs});

      ArgumentPtr lhsAndRhs = makeRawFunctionExpression(And(), {lhs, rhs});
      ArgumentPtr notLhsAndNotRhs = makeRawFunctionExpression(And(), {notLhs, notRhs});

      return makeRawFunctionExpression(Or(), {lhsAndRhs, notLhsAndNotRhs});
    });

    Expression::registerFunctionExpressionMaker<Nequiv>([](const ArgumentsPtrVector &args) {
      const ArgumentPtr &lhs = args.front();
      const ArgumentPtr &rhs = args.back();

      ArgumentPtr notLhs = makeRawFunctionExpression(Not(), {lhs});
      ArgumentPtr notRhs = makeRawFunctionExpression(Not(), {rhs});

      ArgumentPtr notLhsAndRhs = makeRawFunctionExpression(And(), {notLhs, rhs});
      ArgumentPtr lhsAndNotRhs = makeRawFunctionExpression(And(), {lhs, notRhs});

      return makeRawFunctionExpression(Or(), {notLhsAndRhs, lhsAndNotRhs});
    });

    Expression::registerFunctionExpressionMaker<Neg>([](const ArgumentsPtrVector &args) {
      return make_shared<NegExpression>(args.front());
    });

    Expression::registerFunctionExpressionMaker<Inv>([](const ArgumentsPtrVector &args) {
      return make_shared<InvExpression>(args.front());
    });

    Expression::registerFunctionExpressionMaker<UnaryPlus>([](const ArgumentsPtrVector &args) {
      return make_shared<Expression>(args.front());
    });

    Expression::registerFunctionExpressionMaker<Not>([](const ArgumentsPtrVector &args) {
      return make_shared<NotExpression>(args.front());
    });

    Expression::registerFunctionExpressionMaker<Derivative>([](const ArgumentsPtrVector &args) {
      return make_shared<DerivativeExpression>(args.front());
    });
  }
};

const ExpressionConfig config;

}
