#pragma once

#include <algorithm>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/parser/Parser.hpp"

#define FINTAMATH_FUNCTION_EXPRESSION(Function, name) \
  template <typename... Args>                         \
  std::unique_ptr<IMathObject> name(Args &&...args) { \
    static const Function f;                          \
    return makeExpr(f, std::forward<Args>(args)...);  \
  }

namespace fintamath {

class IFunction;

extern bool isExpression(const IMathObject &arg);

extern std::unique_ptr<IMathObject> makeExprChecked(const IFunction &func, const ArgumentsPtrVector &args);

extern std::unique_ptr<IMathObject> makeExprChecked(const IFunction &func, const ArgumentsRefVector &args);

extern std::unique_ptr<IMathObject> makeExpr(const IFunction &func, const ArgumentsPtrVector &args);

extern std::unique_ptr<IMathObject> makeExpr(const IFunction &func, const ArgumentsRefVector &args);

template <typename T, typename = std::enable_if_t<std::is_convertible_v<T, ArgumentPtr>>>
ArgumentPtr toArgumentPtr(T &arg) {
  if constexpr (std::is_copy_constructible_v<T>) {
    return arg;
  }
  else {
    return std::move(arg);
  }
}

template <typename... Args, typename = std::enable_if_t<(std::is_base_of_v<IMathObject, Args> && ...)>>
std::unique_ptr<IMathObject> makeExprChecked(const IFunction &func, const Args &...args) {
  return makeExprChecked(func, ArgumentsRefVector{args...});
}

template <typename... Args, typename = std::enable_if_t<(std::is_base_of_v<IMathObject, Args> && ...)>>
std::unique_ptr<IMathObject> makeExpr(const IFunction &func, const Args &...args) {
  return makeExpr(func, ArgumentsPtrVector{args.clone()...});
}

template <typename... Args, typename = std::enable_if_t<(std::is_convertible_v<Args, ArgumentPtr> && ...)>>
std::unique_ptr<IMathObject> makeExpr(const IFunction &func, Args &&...args) {
  return makeExpr(func, ArgumentsPtrVector{toArgumentPtr(args)...});
}

}
