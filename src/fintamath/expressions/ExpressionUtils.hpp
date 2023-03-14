#pragma once

#include <map>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/parser/Tokenizer.hpp"

namespace fintamath {

bool skipBrackets(const TokenVector &tokens, size_t &openBracketIndex);

TokenVector cutBraces(const TokenVector &tokens);

map<size_t, shared_ptr<IMathObject>> findBinaryOperators(const TokenVector &tokens);

string putInBrackets(const string &str);

string binaryOperatorToString(const IOperator &oper, const ArgumentsPtrVector &values);

string postfixUnaryOperatorToString(const IOperator &oper, const shared_ptr<IMathObject> &lhs);

}