#pragma once

#include <algorithm>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

template <typename T>
struct IsFunctionTypeAny : std::false_type {};

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

  virtual MathObjectType getReturnType() const = 0;

  virtual ArgumentTypeVector getArgTypes() const = 0;

  virtual bool doArgsMatch(const ArgumentRefVector &argsVect) const = 0;

  virtual bool isEvaluatable() const = 0;

  std::unique_ptr<IMathObject> operator()(const std::derived_from<IMathObject> auto &...args) const {
    ArgumentRefVector argsVect = {args...};
    return callAbstract(argsVect);
  }

  std::unique_ptr<IMathObject> operator()(const ArgumentRefVector &argsVect) const {
    return callAbstract(argsVect);
  }

  template <std::derived_from<IFunction> T>
  static void registerType() {
    Parser::registerType<T>(getParser());
  }

  static std::unique_ptr<IFunction> parse(const std::string &parsedStr, IFunction::Type type = IFunction::Type::Any) {
    Parser::Comparator<const std::unique_ptr<IFunction> &> comp = [type](const std::unique_ptr<IFunction> &func) {
      return type == IFunction::Type::Any || func->getFunctionType() == type;
    };
    return Parser::parse<std::unique_ptr<IFunction>>(getParser(), comp, parsedStr);
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::IFunction;
  }

protected:
  virtual std::unique_ptr<IMathObject> callAbstract(const ArgumentRefVector &argsVect) const = 0;

private:
  static Parser::Map<std::unique_ptr<IFunction>> &getParser();
};

template <typename Return, typename Derived, typename... Args>
class IFunctionCRTP : public IFunction {
#define I_FUNCTION_CRTP IFunctionCRTP<Return, Derived, Args...>
#include "fintamath/functions/IFunctionCRTP.hpp"
#undef I_FUNCTION_CRTP

public:
  explicit IFunctionCRTP(bool isEvaluatable = true) : isEvaluatableFunc(isEvaluatable) {
    if constexpr (IsFunctionTypeAny<Derived>::value) {
      type = Type::Any;
    }
    else {
      type = Type(sizeof...(Args));
    }
  }
};

}
