#pragma once

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/Undefined.hpp"

namespace fintamath {

template <std::same_as<ArgumentPtr>... Args, std::invocable<IFunction, Args...> SimplifyFunction>
ArgumentPtr useSimplifyFunctions(const std::vector<SimplifyFunction> &simplFuncs,
                                 const IFunction &func,
                                 const Args &...args) {

  for (const auto &simplFunc : simplFuncs) {
    if (auto res = simplFunc(func, args...)) {
      return res;
    }
  }

  return {};
}

ArgumentPtr simplifyUndefined(const IFunction &func, const std::same_as<ArgumentPtr> auto &...args) {
  if ((is<Undefined>(args) || ...)) {
    static const size_t undefinedReturnType = Undefined{}.getReturnType();
    const size_t funcReturnType = func.getReturnType();

    if (!isBaseOf(undefinedReturnType, funcReturnType) &&
        !isBaseOf(funcReturnType, undefinedReturnType)) {

      throw InvalidInputFunctionException(func.toString(), {(args->toString(), ...)});
    }

    return Undefined{}.clone();
  }

  return {};
}

bool isInfinity(const ArgumentPtr &arg);

bool isMulInfinity(const ArgumentPtr &arg);

bool isNegated(const ArgumentPtr &arg);

bool isNegativeNumber(const ArgumentPtr &arg);

bool isComplexNumber(const ArgumentPtr &arg);

bool containsIf(const ArgumentPtr &arg, const std::function<bool(const ArgumentPtr &)> &comp);

bool containsChild(const ArgumentPtr &arg, const ArgumentPtr &child);

bool containsVariable(const ArgumentPtr &arg);

bool containsVariable(const ArgumentPtr &arg, const Variable &var);

bool containsInfinity(const ArgumentPtr &arg);

bool containsComplex(const ArgumentPtr &arg);

std::pair<ArgumentPtr, ArgumentPtr> splitMulExpr(const ArgumentPtr &inChild, bool checkVariables = true);

std::pair<ArgumentPtr, ArgumentPtr> splitPowExpr(const ArgumentPtr &rhs);

std::pair<ArgumentPtr, ArgumentPtr> splitRational(const ArgumentPtr &arg);

ArgumentPtr makePolynom(const IFunction &func, ArgumentPtrVector &&args);

ArgumentPtr makePolynom(const IFunction &func, const ArgumentPtrVector &args);

ArgumentPtrVector getPolynomChildren(const IFunction &func, const ArgumentPtr &arg);

std::vector<std::string> argumentVectorToStringVector(const ArgumentPtrVector &args);

ArgumentPtrVector argumentRefVectorToArgumentPtrVector(const ArgumentRefVector &args);

std::string putInBrackets(const std::string &str);

std::string putInSpaces(const std::string &str);

std::string functionToString(const IFunction &func, const ArgumentPtrVector &args);

std::string operatorChildToString(const IOperator &oper, const ArgumentPtr &child);

std::string binaryOperatorToString(const IOperator &oper, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

std::string prefixUnaryOperatorToString(const IOperator &oper, const ArgumentPtr &rhs);

std::string postfixUnaryOperatorToString(const IOperator &oper, const ArgumentPtr &rhs);

}