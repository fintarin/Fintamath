#include "fintamath/expressions/Expression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/binary/CompExpression.hpp"
#include "fintamath/expressions/binary/DivExpression.hpp"
#include "fintamath/expressions/binary/PowExpression.hpp"
#include "fintamath/expressions/polynomial/AndExpression.hpp"
#include "fintamath/expressions/polynomial/MulExpression.hpp"
#include "fintamath/expressions/polynomial/OrExpression.hpp"
#include "fintamath/expressions/polynomial/SumExpression.hpp"
#include "fintamath/expressions/unary/DerivativeExpression.hpp"
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
#include "fintamath/functions/other/Angle.hpp"
#include "fintamath/functions/other/Degrees.hpp"
#include "fintamath/functions/other/Index.hpp"
#include "fintamath/functions/other/Percent.hpp"
#include "fintamath/functions/other/Rad.hpp"
#include "fintamath/functions/powers/Exp.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

Parser::Vector<std::shared_ptr<Term>, const Token &> &Expression::getTermMakers() {
  static Parser::Vector<std::shared_ptr<Term>, const Token &> maker;
  return maker;
}

Parser::Map<std::shared_ptr<IExpression>, const ArgumentsPtrVector &> &Expression::getExpressionMakers() {
  static Parser::Map<std::shared_ptr<IExpression>, const ArgumentsPtrVector &> maker;
  return maker;
}
}

using namespace fintamath;

namespace {

struct ExpressionConfig {
  ExpressionConfig() {
    Expression::registerTermsMaker([](const Token &token) {
      ArgumentsPtrVector args;

      for (auto i = size_t(IFunction::Type::None); i < size_t(IFunction::Type::Any); i++) {
        if (std::shared_ptr<IMathObject> arg = IFunction::parse(token, IFunction::Type(i))) {
          args.emplace_back(arg);
        }
      }

      if (!args.empty()) {
        return std::make_shared<Term>(token, args);
      }

      return std::shared_ptr<Term>();
    });

    Expression::registerTermsMaker([](const Token &token) {
      if (std::shared_ptr<IMathObject> arg = ILiteral::parse(token)) {
        return std::make_shared<Term>(token, ArgumentsPtrVector{arg});
      }

      return std::shared_ptr<Term>();
    });

    Expression::registerTermsMaker([](const Token &token) {
      if (std::shared_ptr<IMathObject> arg = INumber::parse(token)) {
        return std::make_shared<Term>(token, ArgumentsPtrVector{arg});
      }

      return std::shared_ptr<Term>();
    });

    //---------------------------------------------------------------------------------------------------------//

    Expression::registerFunctionExpressionMaker<Add, true>([](const ArgumentsPtrVector &args) {
      return std::make_shared<SumExpression>(args);
    });

    Expression::registerFunctionExpressionMaker<Sub>([](const ArgumentsPtrVector &args) {
      return std::make_shared<SumExpression>(
          ArgumentsPtrVector{args.front(), std::make_shared<NegExpression>(args.back())});
    });

    Expression::registerFunctionExpressionMaker<Mul, true>([](const ArgumentsPtrVector &args) {
      return std::make_shared<MulExpression>(args);
    });

    Expression::registerFunctionExpressionMaker<Div>([](const ArgumentsPtrVector &args) {
      return std::make_shared<DivExpression>(args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<And, true>([](const ArgumentsPtrVector &args) {
      return std::make_shared<AndExpression>(args);
    });

    Expression::registerFunctionExpressionMaker<Or, true>([](const ArgumentsPtrVector &args) {
      return std::make_shared<OrExpression>(args);
    });

    Expression::registerFunctionExpressionMaker<Pow>([](const ArgumentsPtrVector &args) {
      return std::make_shared<PowExpression>(args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<Eqv>([](const ArgumentsPtrVector &args) {
      return std::make_shared<CompExpression>(Eqv(), args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<Neqv>([](const ArgumentsPtrVector &args) {
      return std::make_shared<CompExpression>(Neqv(), args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<Less>([](const ArgumentsPtrVector &args) {
      return std::make_shared<CompExpression>(Less(), args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<More>([](const ArgumentsPtrVector &args) {
      return std::make_shared<CompExpression>(More(), args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<LessEqv>([](const ArgumentsPtrVector &args) {
      return std::make_shared<CompExpression>(LessEqv(), args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<MoreEqv>([](const ArgumentsPtrVector &args) {
      return std::make_shared<CompExpression>(MoreEqv(), args.front(), args.back());
    });

    Expression::registerFunctionExpressionMaker<Index>([](const ArgumentsPtrVector &args) {
      const ArgumentPtr &lhs = args.front();
      const ArgumentPtr &rhs = args.back();
      const Index func;

      if (!func.doArgsMatch({*lhs, *rhs})) {
        throw InvalidInputBinaryOperatorException(func.toString(), lhs->toString(), rhs->toString());
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
      return std::make_shared<NegExpression>(args.front());
    });

    Expression::registerFunctionExpressionMaker<UnaryPlus>([](const ArgumentsPtrVector &args) {
      return std::make_shared<Expression>(args.front());
    });

    Expression::registerFunctionExpressionMaker<Not>([](const ArgumentsPtrVector &args) {
      return std::make_shared<NotExpression>(args.front());
    });

    Expression::registerFunctionExpressionMaker<Derivative>([](const ArgumentsPtrVector &args) {
      return std::make_shared<DerivativeExpression>(args.front());
    });

    Expression::registerFunctionExpressionMaker<Log>([](const ArgumentsPtrVector &args) {
      return makeRawFunctionExpression(
          Div(), {makeRawFunctionExpression(Ln(), {args.back()}), {makeRawFunctionExpression(Ln(), {args.front()})}});
    });

    Expression::registerFunctionExpressionMaker<Lb>([](const ArgumentsPtrVector &args) {
      return makeRawFunctionExpression(
          Div(), {makeRawFunctionExpression(Ln(), {args.back()}), {makeRawFunctionExpression(Ln(), {TWO.clone()})}});
    });

    Expression::registerFunctionExpressionMaker<Lg>([](const ArgumentsPtrVector &args) {
      return makeRawFunctionExpression(
          Div(), {makeRawFunctionExpression(Ln(), {args.back()}), {makeRawFunctionExpression(Ln(), {TEN.clone()})}});
    });

    Expression::registerFunctionExpressionMaker<Exp>([](const ArgumentsPtrVector &args) {
      return makeRawFunctionExpression(Pow(), {E().clone(), args.front()});
    });

    Expression::registerFunctionExpressionMaker<Percent>([](const ArgumentsPtrVector &args) {
      static const auto PERCENT_VALUE = std::make_shared<Integer>(100);
      return makeRawFunctionExpression(Div(), {args.front(), PERCENT_VALUE});
    });

    Expression::registerFunctionExpressionMaker<Rad>([](const ArgumentsPtrVector &args) {
      static const auto ANGLE = std::make_shared<Integer>(180);
      return makeRawFunctionExpression(Mul(), {args.front(), makeRawFunctionExpression(Div(), {Pi().clone(), ANGLE})});
    });

    Expression::registerFunctionExpressionMaker<Degrees>([](const ArgumentsPtrVector &args) {
      static const auto ANGLE = std::make_shared<Integer>(180);
      return makeRawFunctionExpression(Mul(), {args.front(), makeRawFunctionExpression(Div(), {ANGLE, Pi().clone()})});
    });

    Expression::registerFunctionExpressionMaker<Angle>([](const ArgumentsPtrVector &args) {
      return makeRawFunctionExpression(Rad(), {args.front()});
    });
  }
};

const ExpressionConfig config;
}
