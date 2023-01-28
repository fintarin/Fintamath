#pragma once

#include <algorithm>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/exceptions/InvalidInputFunctionException.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

using ArgumentsVector = std::vector<std::reference_wrapper<const class IMathObject>>;

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

  virtual ArgumentsVector getNonMatchingArgs(const ArgumentsVector &argsVect) const = 0;

  template <typename... Args>
  MathObjectPtr operator()(const Args &...args) const {
    ArgumentsVector argsVect = {args...};
    return callAbstract(argsVect);
  }

  MathObjectPtr operator()(const ArgumentsVector &argsVect) const {
    return callAbstract(argsVect);
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IFunction, T>>>
  static void registerParser() {
    Parser::registerParser<T>(parserMap);
  }

  static FunctionPtr parse(const std::string &parsedStr, IFunction::Type type = IFunction::Type::Any) {
    return Parser::parse<FunctionPtr>(parserMap, parsedStr, [type](const FunctionPtr &func) {
      return type == IFunction::Type::Any || func->getFunctionType() == type;
    });
  }

protected:
  virtual MathObjectPtr callAbstract(const ArgumentsVector &argsVect) const = 0;

  static const std::function<MathObjectPtr(const IFunction &function, const ArgumentsVector &args)>
      buildFunctionExpression;

private:
  static Parser::ParserMap<FunctionPtr> parserMap;
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
    validateArgsSize(argsVect);

    if (isTypeAny) {
      return doAnyArgsMatch(argsVect);
    }

    return doAgsMatch<0, Args...>(argsVect);
  }

  ArgumentsVector getNonMatchingArgs(const ArgumentsVector &argsVect) const override {
    validateArgsSize(argsVect);

    if (isTypeAny) {
      return doAnyArgsMatch(argsVect) ? ArgumentsVector() : argsVect;
    }

    ArgumentsVector nonMatchingArgsVect;
    getNonMatchingArgs<0, Args...>(argsVect, nonMatchingArgsVect);
    return nonMatchingArgsVect;
  }

protected:
  virtual MathObjectPtr call(const ArgumentsVector &argsVect) const = 0;

  MathObjectPtr callAbstract(const ArgumentsVector &argsVect) const final {
    if (!doAgsMatch(argsVect)) {
      return buildFunctionExpression(*this, argsVect);
    }

    return call(argsVect);
  }

private:
  template <size_t i, typename Head, typename... Tail>
  bool doAgsMatch(const ArgumentsVector &argsVect) const {
    if (!is<Head>(argsVect.at(i))) {
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
      return (is<Args>(arg) || ...); //
    });
  }

  template <size_t i, typename Head, typename... Tail>
  void getNonMatchingArgs(const ArgumentsVector &argsVect, ArgumentsVector &nonMatchingArgsVect) const {
    if (!is<Head>(&argsVect.at(i).get())) {
      nonMatchingArgsVect.push_back(argsVect.at(i));
    }

    getNonMatchingArgs<i + 1, Tail...>(argsVect, nonMatchingArgsVect);
  }

  template <size_t>
  void getNonMatchingArgs(const ArgumentsVector &argsVect, ArgumentsVector &nonMatchingArgsVect) const {
  }

  void validateArgsSize(const ArgumentsVector &argsVect) const {
    if (!isTypeAny && argsVect.size() != sizeof...(Args)) {
      throwInvalidInputFunctionException(argsVect);
    }
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
