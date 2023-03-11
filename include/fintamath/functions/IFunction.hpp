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
    None,    // 0 arguments
    Unary,   // 1 argument
    Binary,  // 2 arguments
    Ternary, // 3 arguments
    Any,     // undefined number of arguments
  };

public:
  virtual IFunction::Type getFunctionType() const = 0;

  virtual const std::type_info &getReturnType() const = 0;

  virtual ArgumentsTypesVector getArgsTypes() const = 0;

  virtual bool doArgsMatch(const ArgumentsVector &argsVect) const = 0;

  template <typename... Args, typename = std::enable_if_t<(std::is_base_of_v<IMathObject, Args> && ...)>>
  std::unique_ptr<IMathObject> operator()(const Args &...args) const {
    ArgumentsVector argsVect = {args...};
    return callAbstract(argsVect);
  }

  std::unique_ptr<IMathObject> operator()(const ArgumentsVector &argsVect) const {
    return callAbstract(argsVect);
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IFunction, T>>>
  static void registerType() {
    Parser::registerType<T>(parserMap);
  }

  static std::unique_ptr<IFunction> parse(const std::string &parsedStr, IFunction::Type type = IFunction::Type::Any) {
    Parser::Comparator<const std::unique_ptr<IFunction> &> comp = [type](const std::unique_ptr<IFunction> &func) {
      return type == IFunction::Type::Any || func->getFunctionType() == type;
    };
    return Parser::parse<std::unique_ptr<IFunction>>(parserMap, comp, parsedStr);
  }

protected:
  virtual std::unique_ptr<IMathObject> callAbstract(const ArgumentsVector &argsVect) const = 0;

  static const std::function<std::unique_ptr<IMathObject>(const IFunction &function, ArgumentsPtrVector &&args)>
      makeFunctionExpression;

private:
  static Parser::Map<std::unique_ptr<IFunction>> parserMap;
};

template <typename Return, typename Derived, typename... Args>
class IFunctionCRTP : virtual public IMathObjectCRTP<Derived>, virtual public IFunction {
public:
  IFunctionCRTP(bool inIsTypeAny = false) : isTypeAny(inIsTypeAny) {
  }

  IFunction::Type getFunctionType() const final {
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

  bool doArgsMatch(const ArgumentsVector &argsVect) const override {
    if (isTypeAny) {
      return doAnyArgsMatch(argsVect);
    }

    return doArgsMatch<0, Args...>(argsVect);
  }

protected:
  virtual std::unique_ptr<IMathObject> call(const ArgumentsVector &argsVect) const = 0;

  std::unique_ptr<IMathObject> callAbstract(const ArgumentsVector &argsVect) const final {
    validateArgsSize(argsVect);

    if (!doArgsMatch(argsVect)) {
      return makeFunctionExpression(*this, toArgumentsPtrVect(argsVect));
    }

    return call(argsVect);
  }

  virtual bool equals(const Derived &rhs) const {
    return getFunctionType() == rhs.getFunctionType() && toString() == rhs.toString();
  }

private:
  template <size_t i, typename Head, typename... Tail>
  void getArgsTypes(ArgumentsTypesVector &outArgsTypes) const {
    outArgsTypes.emplace_back(typeid(Head));
    getArgsTypes<i + 1, Tail...>(outArgsTypes);
  }

  template <size_t>
  void getArgsTypes(ArgumentsTypesVector &outArgTypes) const {
  }

  template <size_t i, typename Head, typename... Tail>
  bool doArgsMatch(const ArgumentsVector &argsVect) const {
    if (!is<Head>(argsVect[i])) {
      return false;
    }

    return doArgsMatch<i + 1, Tail...>(argsVect);
  }

  template <size_t>
  bool doArgsMatch(const ArgumentsVector & /*unused*/) const {
    return true;
  }

  template <typename ArgumentsVectorType>
  bool doAnyArgsMatch(const ArgumentsVectorType &argsVect) const {
    return std::all_of(argsVect.begin(), argsVect.end(), [](const auto &arg) {
      return (is<Args>(arg) || ...);
    });
  }

  void validateArgsSize(const ArgumentsVector &argsVect) const {
    if (!isTypeAny && argsVect.size() != sizeof...(Args)) {
      throwInvalidInputFunctionException(argsVect);
    }
  }

  void throwInvalidInputFunctionException(const ArgumentsVector &argsVect) const {
    std::vector<std::string> argNamesVect(argsVect.size());

    for (size_t i = 0; i < argNamesVect.size(); i++) {
      argNamesVect[i] = argsVect[i].get().toString();
    }

    throw InvalidInputFunctionException(toString(), argNamesVect);
  }

  bool isTypeAny;
};

}
