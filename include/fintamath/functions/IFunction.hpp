#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <memory>
#include <string>
#include <tuple>
#include <unordered_map>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/Parser.hpp"
#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"

namespace fintamath {

class IFunction : public IMathObject {
  FINTAMATH_PARENT_CLASS_BODY(IFunction, IMathObject)

  using ClassToOrderMap = std::unordered_map<MathObjectClass, size_t>;

public:
  virtual const ArgumentTypeVector &getArgumentClasses() const noexcept = 0;

  virtual MathObjectClass getReturnClass() const noexcept = 0;

  virtual bool doArgsMatch(const ArgumentRefVector &argVect) const = 0;

  virtual bool isVariadic() const = 0;

  virtual bool isEvaluatable() const = 0;

  std::unique_ptr<IMathObject> operator()(const std::derived_from<IMathObject> auto &...args) const {
    const ArgumentRefVector argVect = {args...};
    return callAbstract(argVect);
  }

  std::unique_ptr<IMathObject> operator()(const ArgumentRefVector &argVect) const {
    return callAbstract(argVect);
  }

protected:
  virtual std::unique_ptr<IMathObject> callAbstract(const ArgumentRefVector &argVect) const = 0;
};

template <typename Return, typename Derived, typename... Args>
  requires(sizeof...(Args) > 0)
class IFunctionCRTP : public IFunction {
#define I_FUNCTION_CRTP IFunctionCRTP<Return, Derived, Args...>
#include "fintamath/functions/IFunctionCRTP.hpp"
#undef I_FUNCTION_CRTP
};

}
