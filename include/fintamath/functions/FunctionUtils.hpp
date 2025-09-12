#pragma once

#include <string>

#include "fintamath/functions/IFunction.hpp"

namespace fintamath::detail {

template <typename... Args, typename SimplifyFunctions>
SharedPtr<IMathObject> useSimplifyFunctions(const SimplifyFunctions &simplFuncs, const Args &...args) {
  for (const auto &simplFunc : simplFuncs) {
    if (auto res = simplFunc(args...)) {
      return res;
    }
  }

  return nullptr;
}

bool isInfinity(const SharedRef<IMathObject> &arg);

// bool isMulInfinity(const SharedRef<IMathObject> &arg);

// bool isNegated(const SharedRef<IMathObject> &arg);

bool isNumberNegated(const SharedRef<IMathObject> &arg);

bool isComplexNumber(const SharedRef<IMathObject> &arg);

// bool containsIf(const SharedRef<IMathObject> &arg, const std::function<bool(const SharedRef<IMathObject> &)> &comp);

// bool containsChild(const SharedRef<IMathObject> &arg, const SharedRef<IMathObject> &child);

// bool containsVariable(const SharedRef<IMathObject> &arg);

// bool containsVariable(const SharedRef<IMathObject> &arg, const Variable &var);

// bool containsInfinity(const SharedRef<IMathObject> &arg);

// bool containsComplex(const SharedRef<IMathObject> &arg);

// std::pair<SharedRef<IMathObject>, SharedRef<IMathObject>> splitMulExpr(const SharedRef<IMathObject> &inChild, bool checkVariables = true);

// std::pair<SharedRef<IMathObject>, SharedRef<IMathObject>> splitPowExpr(const SharedRef<IMathObject> &rhs);

// std::pair<SharedRef<IMathObject>, SharedRef<IMathObject>> splitRational(const SharedRef<IMathObject> &arg);

// SharedRef<IMathObject> negate(const SharedRef<IMathObject> &arg);

// SharedRef<IMathObject> invert(const SharedRef<IMathObject> &arg);

// IFunction::Arguments getPolynomChildren(const IFunction &func, const SharedRef<IMathObject> &arg);

std::string argumentToString(const IFunction::Declaration &decl, const SharedRef<IMathObject> &arg) noexcept;

}