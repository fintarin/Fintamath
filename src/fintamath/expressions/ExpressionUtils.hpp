#pragma once

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/parser/Tokenizer.hpp"
#include <map>

namespace fintamath {
inline bool skipBrackets(const TokenVector &tokens, size_t &openBracketIndex) {
  if (openBracketIndex >= tokens.size() || tokens.at(openBracketIndex) != "(") {
    return false;
  }

  int64_t brackets = 0;

  for (size_t i = openBracketIndex; i < tokens.size(); i++) {
    if (tokens[i] == "(") {
      brackets++;
    } else if (tokens[i] == ")") {
      brackets--;
    }

    if (brackets == 0) {
      openBracketIndex = i + 1;
      return true;
    }
    if (brackets < 0) {
      throw InvalidInputException(Tokenizer::tokensToString(tokens));
    }
  }

  throw InvalidInputException(Tokenizer::tokensToString(tokens));
}

inline TokenVector cutBraces(const TokenVector &tokens) {
  if (tokens.empty()) {
    return tokens;
  }
  auto newTokens = tokens;
  if (newTokens.front() == "(" && newTokens.back() == ")") {
    newTokens.erase(newTokens.begin());
    newTokens.erase(newTokens.end() - 1);
  }
  return newTokens;
}

inline std::map<size_t, MathObjectPtr> findBinaryOperators(const TokenVector &tokens) {
  std::map<size_t, MathObjectPtr> operators;

  bool isPrevTokenOper = false;

  for (size_t i = 0; i < tokens.size(); i++) {
    if (skipBrackets(tokens, i)) {
      isPrevTokenOper = false;
      i--;
      continue;
    }

    if (auto oper = IOperator::parse(tokens.at(i)); oper && oper->getFunctionType() == IFunction::Type::Binary) {
      if (!isPrevTokenOper) {
        operators.insert({i, std::move(oper)});
        isPrevTokenOper = true;
      }
    } else {
      isPrevTokenOper = false;
    }
  }

  return operators;
}

inline ArgumentsPtrVector copy(const ArgumentsPtrVector &rhs) {
  ArgumentsPtrVector result;

  for (const auto &value : rhs) {
    result.emplace_back(value->clone());
  }

  return result;
}
}