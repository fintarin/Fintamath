#include "fintamath/expressions/ExpressionFunctions.hpp"

#include "fintamath/functions/trigonometry/Sin.hpp"

namespace fintamath {

namespace {

template <typename ModifyCallback>
Expression modify(const Expression &rhs, const ModifyCallback &modifyCallback) {
  auto arg = rhs.unwrapp().toRef();
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
  return modify(rhs, [](SharedRef<IMathObject> &arg) {
    arg = Sin::make({arg});
  });
}

}