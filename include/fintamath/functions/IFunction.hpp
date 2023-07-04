#pragma once

#include <algorithm>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class IFunction : public IMathObject {
public:
  enum class Type : uint16_t {
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

  virtual size_t getReturnTypeId() const = 0;

  virtual ArgumentsTypeIdsVector getArgsTypeIds() const = 0;

  virtual bool doArgsMatch(const ArgumentsRefVector &argsVect) const = 0;

  virtual bool isNonExressionEvaluatable() const = 0;

  template <typename... Args, typename = std::enable_if_t<(std::is_base_of_v<IMathObject, Args> && ...)>>
  std::unique_ptr<IMathObject> operator()(const Args &...args) const {
    ArgumentsRefVector argsVect = {args...};
    return callAbstract(argsVect);
  }

  std::unique_ptr<IMathObject> operator()(const ArgumentsRefVector &argsVect) const {
    return callAbstract(argsVect);
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IFunction, T>>>
  static void registerType() {
    Parser::registerType<T>(getParser());
  }

  static std::unique_ptr<IFunction> parse(const std::string &parsedStr, IFunction::Type type = IFunction::Type::Any) {
    Parser::Comparator<const std::unique_ptr<IFunction> &> comp = [type](const std::unique_ptr<IFunction> &func) {
      return type == IFunction::Type::Any || func->getFunctionType() == type;
    };
    return Parser::parse<std::unique_ptr<IFunction>>(getParser(), comp, parsedStr);
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::IFunction);
  }

protected:
  virtual std::unique_ptr<IMathObject> callAbstract(const ArgumentsRefVector &argsVect) const = 0;

private:
  static Parser::Map<std::unique_ptr<IFunction>> &getParser();
};

template <typename Return, typename Derived, typename... Args>
class IFunctionCRTP : public IFunction {
#define FINTAMATH_I_FUNCTION_CRTP IFunctionCRTP<Return, Derived, Args...>
#include "fintamath/functions/IFunctionCRTP.hpp"
#undef FINTAMATH_I_FUNCTION_CRTP

public:
  IFunctionCRTP(bool isNonExressionEvaluatable = true) : isNonExressionEvaluatableFunc(isNonExressionEvaluatable) {
    if constexpr (IsFunctionTypeAny<Derived>::value) {
      type = Type::Any;
    }
    else {
      type = Type(sizeof...(Args));
    }
  }
};

}
