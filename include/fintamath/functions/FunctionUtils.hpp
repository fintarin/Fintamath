#pragma once

#include <algorithm>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/parser/Parser.hpp"

#define FINTAMATH_FUNCTION_EXPRESSION(Function, name)          \
  std::unique_ptr<IMathObject> name(auto &&...args) {          \
    static const Function f;                                   \
    return makeExpr(f, std::forward<decltype(args)>(args)...); \
  }

namespace fintamath {

class IFunction;

extern bool isExpression(const IMathObject &arg);

extern std::unique_ptr<IMathObject> makeExprChecked(const IFunction &func, const ArgumentsPtrVector &args);

extern std::unique_ptr<IMathObject> makeExprChecked(const IFunction &func, const ArgumentsRefVector &args);

extern std::unique_ptr<IMathObject> makeExpr(const IFunction &func, const ArgumentsPtrVector &args);

extern std::unique_ptr<IMathObject> makeExpr(const IFunction &func, const ArgumentsRefVector &args);

template <std::convertible_to<ArgumentPtr> T>
ArgumentPtr toArgumentPtr(T &arg) {
  if constexpr (std::is_copy_constructible_v<T>) {
    return arg;
  }
  else {
    return std::move(arg);
  }
}

std::unique_ptr<IMathObject> makeExprChecked(const IFunction &func, const std::derived_from<IMathObject> auto &...args) {
  return makeExprChecked(func, ArgumentsRefVector{args...});
}

std::unique_ptr<IMathObject> makeExpr(const IFunction &func, const std::derived_from<IMathObject> auto &...args) {
  return makeExpr(func, ArgumentsPtrVector{args.clone()...});
}

std::unique_ptr<IMathObject> makeExpr(const IFunction &func, std::convertible_to<ArgumentPtr> auto &&...args) {
  return makeExpr(func, ArgumentsPtrVector{toArgumentPtr(args)...});
}

}
