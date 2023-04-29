#pragma once

#include <map>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/parser/Tokenizer.hpp"

namespace fintamath {

class IExpression;

bool skipBrackets(const TokenVector &tokens, size_t &openBracketIndex);

TokenVector cutBrackets(const TokenVector &tokens);

// TODO: remove
std::map<size_t, ArgumentPtr> findBinaryOperators(const TokenVector &tokens);

std::string putInBrackets(const std::string &str);

std::string putInSpaces(const std::string &str);

std::string binaryOperatorToString(const IOperator &oper, const ArgumentsPtrVector &values);

std::string postfixUnaryOperatorToString(const IOperator &oper, const ArgumentPtr &lhs);

bool hasVariables(const std::shared_ptr<const IExpression> &expr, const std::shared_ptr<const Variable> &var);

extern std::unique_ptr<IMathObject> makeFunctionExpression(const IFunction &func, const ArgumentsRefVector &args);

extern ArgumentPtr makeFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args);

extern std::shared_ptr<IExpression> makeRawFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args);

}
