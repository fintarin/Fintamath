#pragma once

#include <algorithm>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/exceptions/InvalidInputFunctionException.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class IFunction : virtual public IMathObject {
public:
  enum class Type : uint16_t {
    None,   // 0 arguments
    Unary,  // 1 argument
    Binary, // 2 arguments
    Any,    // undefined number of arguments, but non 0
  };

public:
  virtual IFunction::Type getFunctionType() const = 0;

  virtual const std::type_info &getReturnType() const = 0;

  virtual ArgumentsTypesVector getArgsTypes() const = 0;

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

protected:
  virtual std::unique_ptr<IMathObject> callAbstract(const ArgumentsRefVector &argsVect) const = 0;

  static std::unique_ptr<IMathObject> makeExprSimpl(const IFunction &function, const ArgumentsRefVector &args);

  static std::unique_ptr<IMathObject> makeExpr(const IFunction &function, const ArgumentsRefVector &args);

private:
  static Parser::Map<std::unique_ptr<IFunction>> &getParser();
};

template <typename Return, typename Derived, typename... Args>
class IFunctionCRTP : virtual public IMathObjectCRTP<Derived>, virtual public IFunction {
public:
  IFunctionCRTP(bool isTypeAny = false, bool isNonExressionEvaluatable = true)
      : isTypeAnyFunc(isTypeAny),
        isNonExressionEvaluatableFunc(isNonExressionEvaluatable) {
  }

  IFunction::Type getFunctionType() const final {
    if (isTypeAnyFunc) {
      return Type::Any;
    }

    return IFunction::Type(sizeof...(Args));
  }

  const std::type_info &getReturnType() const final {
    return typeid(Return);
  }

  ArgumentsTypesVector getArgsTypes() const final {
    ArgumentsTypesVector argsTypes;
    getArgsTypes<0, Args...>(argsTypes);
    return argsTypes;
  }

  bool doArgsMatch(const ArgumentsRefVector &argsVect) const override {
    if (isTypeAnyFunc) {
      return doAnyArgsMatch(argsVect);
    }

    if (argsVect.size() != size_t(getFunctionType())) {
      return false;
    }

    return doArgsMatch<0, Args...>(argsVect);
  }

  bool isNonExressionEvaluatable() const final {
    return isNonExressionEvaluatableFunc;
  }

protected:
  virtual std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const = 0;

  std::unique_ptr<IMathObject> callAbstract(const ArgumentsRefVector &argsVect) const final {
    validateArgsSize(argsVect);

    if (doArgsMatch(argsVect)) {
      return call(argsVect);
    }

    return makeExprSimpl(*this, argsVect);
  }

  bool equals(const Derived &rhs) const override {
    return getFunctionType() == rhs.getFunctionType() && toString() == rhs.toString();
  }

private:
  template <size_t i, typename Head, typename... Tail>
  void getArgsTypes(ArgumentsTypesVector &outArgsTypes) const {
    outArgsTypes.emplace_back(typeid(Head));
    getArgsTypes<i + 1, Tail...>(outArgsTypes);
  }

  template <size_t>
  void getArgsTypes(ArgumentsTypesVector & /*outArgTypes*/) const {
  }

  template <size_t i, typename Head, typename... Tail>
  bool doArgsMatch(const ArgumentsRefVector &argsVect) const {
    if (!is<Head>(argsVect[i])) {
      return false;
    }

    return doArgsMatch<i + 1, Tail...>(argsVect);
  }

  template <size_t>
  bool doArgsMatch(const ArgumentsRefVector & /*unused*/) const {
    return true;
  }

  template <typename ArgumentsRefVectorType>
  bool doAnyArgsMatch(const ArgumentsRefVectorType &argsVect) const {
    for (const auto &arg : argsVect) {
      if (!(is<Args>(arg) || ...)) {
        return false;
      }
    }

    return true;
  }

  void validateArgsSize(const ArgumentsRefVector &argsVect) const {
    if (isTypeAnyFunc) {
      if (argsVect.empty()) {
        throwInvalidInputFunctionException(argsVect);
      }
    }
    else if (argsVect.size() != sizeof...(Args)) {
      throwInvalidInputFunctionException(argsVect);
    }
  }

  void throwInvalidInputFunctionException(const ArgumentsRefVector &argsVect) const {
    std::vector<std::string> argNamesVect(argsVect.size());

    for (size_t i = 0; i < argNamesVect.size(); i++) {
      argNamesVect[i] = argsVect[i].get().toString();
    }

    throw InvalidInputFunctionException(toString(), argNamesVect);
  }

private:
  bool isTypeAnyFunc;

  bool isNonExressionEvaluatableFunc;
};

}
