#include "fintamath/expressions/ExpressionFunctions.hpp"

#include "fintamath/functions/trigonometry/Sin.hpp"

namespace fintamath {

namespace {

template <typename ModifyCallback>
Expression modify(const Expression &rhs, const ModifyCallback &modifyCallback) {
  Expression::Argument arg = rhs.unwrapp();
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

Expression sin(const Expression &rhs) {
  return {Sin::make({rhs.unwrapp()})};
}

}