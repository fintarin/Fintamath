#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/core/Parser.hpp"
#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"

namespace fintamath {

template <typename T>
struct IsFunctionTypeAny : std::false_type {};

class IFunction : public IMathObject {
  using FunctionOrderMap = std::unordered_map<std::string, size_t>;
  using FunctionParser = Parser<std::unique_ptr<IFunction>()>;

public:
  enum class Type : uint8_t {
    None,       // 0 arguments
    Unary,      // 1 argument
    Binary,     // 2 arguments
    Ternary,    // 3 arguments
    Quaternary, // 4 arguments
    Quinary,    // 5 arguments
    Senary,     // 6 arguments
    Septenary,  // 7 arguments
    Any,        // undefined number of arguments, but non 0
  };

public:
  virtual IFunction::Type getFunctionType() const = 0;

  virtual MathObjectType getReturnType() const = 0;

  virtual ArgumentTypeVector getArgTypes() const = 0;

  virtual size_t getFunctionOrder() const = 0;

  virtual bool doArgsMatch(const ArgumentRefVector &argVect) const = 0;

  virtual bool isEvaluatable() const = 0;

  std::unique_ptr<IMathObject> operator()(const std::derived_from<IMathObject> auto &...args) const {
    const ArgumentRefVector argVect = {args...};
    return callAbstract(argVect);
  }

  std::unique_ptr<IMathObject> operator()(const ArgumentRefVector &argVect) const {
    return callAbstract(argVect);
  }

  static std::unique_ptr<IFunction> parse(const std::string &parsedStr, Type type = Type::Any) {
    const auto validator = [type](const std::unique_ptr<IFunction> &func) {
      return type == Type::Any || func->getFunctionType() == type;
    };
    return getParser().parse(validator, parsedStr);
  }

  template <std::derived_from<IFunction> T>
  static void registerType() {
    getParser().registerType<T>();

    getFunctionOrderMutableMap()[T{}.toString()] = maxFunctionOrder;
    maxFunctionOrder++;
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::IFunction;
  }

protected:
  virtual std::unique_ptr<IMathObject> callAbstract(const ArgumentRefVector &argVect) const = 0;

  static const FunctionOrderMap &getFunctionOrderMap();

private:
  static FunctionOrderMap &getFunctionOrderMutableMap();

  static FunctionParser &getParser();

  inline static size_t maxFunctionOrder = 0;
};

template <typename Return, typename Derived, typename... Args>
class IFunctionCRTP : public IFunction {
#define I_FUNCTION_CRTP IFunctionCRTP<Return, Derived, Args...>
#include "fintamath/functions/IFunctionCRTP.hpp"
#undef I_FUNCTION_CRTP

public:
  explicit IFunctionCRTP(const bool isEvaluatable = true) : isEvaluatableFunc(isEvaluatable) {
    if constexpr (IsFunctionTypeAny<Derived>::value) {
      type = Type::Any;
    }
    else {
      type = static_cast<Type>(sizeof...(Args));
    }
  }
};

}
