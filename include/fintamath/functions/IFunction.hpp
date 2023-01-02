#pragma once

#include <algorithm>

#include "fintamath/exceptions/InvalidInputFunctionException.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/helpers/Parser.hpp"

template <typename Head, typename... Tail>
struct A {};

namespace fintamath {

class IFunction;
using FunctionPtr = std::unique_ptr<IFunction>;

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

  virtual bool doAgsMatch(const ArgumentsVector &argsVect) const = 0;

  template <typename... Args>
  MathObjectPtr operator()(const Args &...args) const {
    ArgumentsVector argsVect = {args...};
    return callAbstract(argsVect);
  }

  MathObjectPtr operator()(const ArgumentsVector &argsVect) const {
    return callAbstract(argsVect);
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IFunction, T>>>
  static void addParser() {
    helpers::addParser<T>(parserMap);
  }

  static FunctionPtr parse(const std::string &parsedStr, IFunction::Type type = IFunction::Type::Any) {
    return helpers::parse<FunctionPtr>(parserMap, parsedStr, [type](const FunctionPtr &func) {
      return type == IFunction::Type::Any || func->getFunctionType() == type;
    });
  }

protected:
  virtual MathObjectPtr callAbstract(const ArgumentsVector &argsVect) const = 0;

private:
  static helpers::ParserMap<FunctionPtr> parserMap;
};

template <typename Derived, typename... Args>
class IFunctionCRTP : virtual public IFunction, virtual public IMathObjectCRTP<Derived> {
public:
  IFunctionCRTP(bool inIsTypeAny = false) : isTypeAny(inIsTypeAny) {
  }

  IFunction::Type getFunctionType() const final {
    return IFunction::Type(sizeof...(Args));
  }

  bool doAgsMatch(const ArgumentsVector &argsVect) const override {
    if (!doesArgsSizeMatch(argsVect)) {
      return false;
    }

    if (isTypeAny) {
      return doAnyArgsMatch(argsVect);
    }

    return doAgsMatch<0, Args...>(argsVect);
  }

protected:
  virtual MathObjectPtr call(const ArgumentsVector &argsVect) const = 0;

  MathObjectPtr callAbstract(const ArgumentsVector &argsVect) const final {
    if (!doesArgsSizeMatch(argsVect)) {
      throwInvalidInputFunctionException(argsVect);
    }

    if (!doAgsMatch(argsVect)) {
      return Expression::buildFunctionExpression(*this, argsVect); // TODO: do not use Expression here
    }

    return call(argsVect);
  }

private:
  bool doesArgsSizeMatch(const ArgumentsVector &argsVect) const {
    return isTypeAny || argsVect.size() == sizeof...(Args);
  }

  template <size_t i, typename Head, typename... Tail>
  bool doAgsMatch(const ArgumentsVector &argsVect) const {
    if (!argsVect.at(i).get().instanceOf<Head>()) {
      return false;
    }

    return doAgsMatch<i + 1, Tail...>(argsVect);
  }

  template <size_t>
  bool doAgsMatch(const ArgumentsVector & /*unused*/) const {
    return true;
  }

  bool doAnyArgsMatch(const ArgumentsVector &argsVect) const {
    return std::all_of(argsVect.begin(), argsVect.end(), [](const auto &arg) {
      return (arg.get().template instanceOf<Args>() || ...); //
    });
  }

  void throwInvalidInputFunctionException(const ArgumentsVector &argsVect) const {
    std::vector<std::string> argNamesVect(argsVect.size());

    for (size_t i = 0; i < argNamesVect.size(); i++) {
      argNamesVect.at(i) = argsVect.at(i).get().toString();
    }

    throw InvalidInputFunctionException(toString(), argNamesVect);
  }

  bool isTypeAny;
};

}
