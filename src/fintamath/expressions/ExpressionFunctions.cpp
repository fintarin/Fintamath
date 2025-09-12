#include "fintamath/expressions/ExpressionFunctions.hpp"

#include "fintamath/functions/arithmetic/Pow.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"

namespace fintamath {

namespace {

template <typename ModifyCallback>
Expression modify(const Expression &rhs, const ModifyCallback &modifyCallback) {
  auto arg = rhs.getArgument();
  modifyCallback(arg);
  return arg;
}

}

Expression simplify(const Expression &rhs) {
  return modify(rhs, &IFunction::simplify);
}

Expression solve(const Expression &rhs) {
  return modify(rhs, &IFunction::solve);
}

Expression approximate(const Expression &rhs) {
  return modify(rhs, &IFunction::approximate);
}

Expression pow(const Expression &lhs, const Expression &rhs) {
  return {makeShared<Pow>({lhs.getArgument(), rhs.getArgument()})};
}

Expression sin(const Expression &rhs) {
  return {makeShared<Sin>({rhs.getArgument()})};
}

}
