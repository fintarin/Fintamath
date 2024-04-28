#pragma once

#include <concepts>
#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"

#define FINTAMATH_FUNCTION_EXPRESSION(Function, name)                  \
  std::unique_ptr<IMathObject> name(auto &&...args) {                  \
    static const Function f;                                           \
    return detail::makeExpr(f, std::forward<decltype(args)>(args)...); \
  }

namespace fintamath {

class IFunction;

namespace detail {

extern std::unique_ptr<IMathObject> makeExpr(const IFunction &func, ArgumentPtrVector args);

std::unique_ptr<IMathObject> makeExpr(const IFunction &func, const ArgumentRefVector &args);

std::unique_ptr<IMathObject> makeExpr(const IFunction &func, const std::derived_from<IMathObject> auto &...args) {
  return makeExpr(func, ArgumentPtrVector{args.clone()...});
}

std::unique_ptr<IMathObject> makeExpr(const IFunction &func, std::convertible_to<ArgumentPtr> auto &&...args) {
  return makeExpr(func, ArgumentPtrVector{ArgumentPtr(std::forward<decltype(args)>(args))...});
}

extern std::unique_ptr<IMathObject> makeExprWithValidation(const IFunction &func, ArgumentPtrVector args);

std::unique_ptr<IMathObject> makeExprWithValidation(const IFunction &func, const ArgumentRefVector &args);

std::unique_ptr<IMathObject> makeExprWithValidation(const IFunction &func, const std::derived_from<IMathObject> auto &...args) {
  return makeExprWithValidation(func, ArgumentPtrVector{args.clone()...});
}

std::unique_ptr<IMathObject> makeExprWithValidation(const IFunction &func, std::convertible_to<ArgumentPtr> auto &&...args) {
  return makeExprWithValidation(func, ArgumentPtrVector{ArgumentPtr(std::forward<decltype(args)>(args))...});
}

ArgumentPtrVector argumentRefVectorToArgumentPtrVector(const ArgumentRefVector &args);

}

}
