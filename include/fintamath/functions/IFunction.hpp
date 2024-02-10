#pragma once

#include <concepts>
#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/core/Parser.hpp"
#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"

namespace fintamath {

class IFunction : public IMathObject {
  using FunctionOrderMap = std::unordered_map<std::string, size_t>;

  using FunctionParser = Parser<std::unique_ptr<IFunction>()>;

public:
  virtual const ArgumentTypeVector &getArgumentTypes() const = 0;

  virtual MathObjectType getReturnType() const = 0;

  virtual size_t getFunctionOrder() const = 0;

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

  static std::unique_ptr<IFunction> parse(const std::string &parsedStr) {
    return getParser().parse(parsedStr);
  }

  static std::unique_ptr<IFunction> parse(const std::string &parsedStr, size_t argSize) {
    const auto validator = [argSize](const std::unique_ptr<IFunction> &func) {
      return argSize == func->getArgumentTypes().size();
    };
    return getParser().parse(validator, parsedStr);
  }

  template <std::derived_from<IFunction> T>
  static void registerType() {
    getParser().registerType<T>();

    getFunctionOrderMutableMap()[T{}.toString()] = maxFunctionOrder;
    maxFunctionOrder++;
  }

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::IFunction;
  }

protected:
  virtual std::unique_ptr<IMathObject> callAbstract(const ArgumentRefVector &argVect) const = 0;

  virtual void validateArgsSize(const ArgumentRefVector &argVect) const;

  static const FunctionOrderMap &getFunctionOrderMap();

private:
  static FunctionOrderMap &getFunctionOrderMutableMap();

  static FunctionParser &getParser();

  inline static size_t maxFunctionOrder = 0;
};

template <typename Return, typename Derived, typename... Args>
  requires(sizeof...(Args) > 0)
class IFunctionCRTP : public IFunction {
#define I_FUNCTION_CRTP IFunctionCRTP<Return, Derived, Args...>
#include "fintamath/functions/IFunctionCRTP.hpp"
#undef I_FUNCTION_CRTP
};

}
