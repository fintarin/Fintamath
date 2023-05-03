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

std::string functionToString(const IFunction &func, const ArgumentsPtrVector &args);

std::string binaryOperatorToString(const IOperator &oper, const ArgumentsPtrVector &values);

std::string prefixUnaryOperatorToString(const IOperator &oper, const ArgumentPtr &rhs);

std::string postfixUnaryOperatorToString(const IOperator &oper, const ArgumentPtr &rhs);

bool hasVariables(const std::shared_ptr<const IExpression> &expr);

bool hasVariable(const std::shared_ptr<const IExpression> &expr, const Variable &var);

extern std::unique_ptr<IMathObject> makeFunctionExpression(const IFunction &func, const ArgumentsRefVector &args);

extern ArgumentPtr makeFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args);

extern std::shared_ptr<IExpression> makeRawFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args);

}
