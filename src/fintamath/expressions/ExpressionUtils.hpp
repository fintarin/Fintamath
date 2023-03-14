#pragma once

#include <map>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/parser/Tokenizer.hpp"

namespace fintamath {

class IExpression;

bool skipBrackets(const TokenVector &tokens, size_t &openBracketIndex);

TokenVector cutBraces(const TokenVector &tokens);

map<size_t, ArgumentPtr> findBinaryOperators(const TokenVector &tokens);

string putInBrackets(const string &str);

string binaryOperatorToString(const IOperator &oper, const ArgumentsPtrVector &values);

string postfixUnaryOperatorToString(const IOperator &oper, const ArgumentPtr &lhs);

extern unique_ptr<IMathObject> makeFunctionExpression(const IFunction &func, const ArgumentsRefVector &args);

extern ArgumentPtr makeFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args);

extern shared_ptr<IExpression> makeRawFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args);

}
