#pragma once

#include <map>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/parser/Tokenizer.hpp"

namespace fintamath {

bool skipBrackets(const TokenVector &tokens, size_t &openBracketIndex);

TokenVector cutBraces(const TokenVector &tokens);

std::map<size_t, std::shared_ptr<IMathObject>> findBinaryOperators(const TokenVector &tokens);

std::string putInBrackets(const std::string &str);

std::string binaryOperatorToString(const IOperator &oper, const ArgumentsPtrVector &values);

std::string postfixUnaryOperatorToString(const IOperator &oper, const std::shared_ptr<IMathObject> &lhs);

}