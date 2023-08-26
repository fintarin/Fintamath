#pragma once

#include <map>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/Undefined.hpp"

namespace fintamath {

std::string putInBrackets(const std::string &str);

std::string putInSpaces(const std::string &str);

std::string functionToString(const IFunction &func, const ArgumentsPtrVector &args);

std::string binaryOperatorToString(const IOperator &oper, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

std::string prefixUnaryOperatorToString(const IOperator &oper, const ArgumentPtr &rhs);

std::string postfixUnaryOperatorToString(const IOperator &oper, const ArgumentPtr &rhs);

bool hasVariable(const ArgumentPtr &arg);

bool hasVariable(const ArgumentPtr &arg, const Variable &var);

bool hasInfinity(const ArgumentPtr &arg);

bool isInfinity(const ArgumentPtr &arg);

bool isNegated(const ArgumentPtr &arg);

std::vector<std::string> argumentVectorToStringVector(const ArgumentsPtrVector &args);

ArgumentsPtrVector argumentRefVectorToArgumentPtrVector(const ArgumentsRefVector &args);

template <typename... Args>
ArgumentPtr simplifyUndefined(const IFunction &func, const Args &...args) {
  if ((is<Undefined>(args) || ...)) {
    static const size_t undefinedReturnTypeId = Undefined().getReturnTypeId();
    const size_t funcReturnTypeId = func.getReturnTypeId();

    if (!isBaseOf(undefinedReturnTypeId, funcReturnTypeId) && !isBaseOf(funcReturnTypeId, undefinedReturnTypeId)) {
      throw InvalidInputFunctionException(func.toString(), {(args->toString(), ...)});
    }

    return Undefined().clone();
  }

  return {};
}

}
