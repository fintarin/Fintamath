#include "fintamath/expressions/IExpression.hpp"

#include <algorithm>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

TokenVector IExpression::tokenize(const std::string &str) {
  std::string tokenizeStr = cutSpacesFromBeginEnd(str);
  TokenVector tokens;
  std::string digitToken;
  std::string letterToken;
  std::string specialToken;

  for (size_t i = 0; i < tokenizeStr.size(); i++) {
    const auto &value = tokenizeStr[i];
    if (isDigit(value) || value == '.') {
      digitToken.push_back(value);
      appendToken(tokens, letterToken);
      appendToken(tokens, specialToken);

      if (!tokens.empty() && tokens.at(tokens.size() - 1) == ")") {
        tokens.emplace_back("*");
      }
      continue;
    }

    if (isLetter(value)) {
      letterToken.push_back(value);
      if (appendToken(tokens, digitToken)) {
        tokens.emplace_back("*");
      }
      appendToken(tokens, specialToken);

      if (!tokens.empty() && tokens.at(tokens.size() - 1) == ")") {
        tokens.emplace_back("*");
      }
      continue;
    }

    if (isBracket(value)) {
      appendToken(tokens, digitToken);
      appendToken(tokens, specialToken);
      appendToken(tokens, letterToken);

      if (((!tokens.empty() && tokens.at(tokens.size() - 1) == ")")) && isOpenBracket(value) && value == '(') {
        tokens.emplace_back("*");
      }

      tokens.emplace_back(1, value);
      continue;
    }

    if (isSpecial(value)) {
      appendToken(tokens, digitToken);
      appendToken(tokens, letterToken);
      if (isOneSymbolToken(value)) {
        appendToken(tokens, specialToken);
        tokens.emplace_back(1, value);
        continue;
      }
      specialToken.push_back(value);
      continue;
    }

    if (value == ' ') {
      appendToken(tokens, specialToken);
      if (!isCanInsertMultiplyCharacter(tokenizeStr[i + 1])) {
        continue;
      }
      if (appendToken(tokens, digitToken)) {
        tokens.emplace_back("*");
        continue;
      }
      if (!letterToken.empty() && isLetter(tokenizeStr[i + 1])) {
        appendToken(tokens, letterToken);
        tokens.emplace_back("*");
      }
    }
  }
  appendToken(tokens, digitToken);
  appendToken(tokens, specialToken);
  appendToken(tokens, letterToken);

  return tokens;
}

bool IExpression::findCharInStr(char c, const std::string &str) {
  return std::find(str.begin(), str.end(), c) != str.end();
}

bool IExpression::isCanInsertMultiplyCharacter(char c) {
  return c != ' ' && !isSpecial(c);
}
bool IExpression::isDigit(char c) {
  return c >= '0' && c <= '9';
}

bool IExpression::isLetter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool IExpression::isBracket(char c) {
  return c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']';
}

bool IExpression::isOpenBracket(char c) {
  return c == '(' || c == '{' || c == '[';
}

bool IExpression::isCloseBracket(char c) {
  return c == ')' || c == '}' || c == ']';
}

bool IExpression::isSpecial(char c) {
  return (c >= '!' && c <= '/') || (c >= ':' && c <= '@') || (c >= '[' && c <= '`') || (c >= '{' && c <= '~');
}

bool IExpression::appendToken(TokenVector &tokens, std::string &token) {
  if (!token.empty()) {
    tokens.emplace_back(token);
    token.clear();
    return true;
  }
  return false;
}

std::string IExpression::cutSpacesFromBeginEnd(const std::string &str) {
  std::string result = str;
  while (!result.empty() && result[result.size() - 1] == ' ') {
    result.pop_back();
  }
  while (!result.empty() && result[0] == ' ') {
    result.erase(result.begin());
  }
  return result;
}

bool IExpression::skipBrackets(const TokenVector &tokens, size_t &inOutIndex) {
  if (inOutIndex >= tokens.size() || tokens.at(inOutIndex) != "(") {
    return false;
  }

  int64_t brackets = 0;

  for (size_t i = inOutIndex; i < tokens.size(); i++) {
    if (tokens[i] == "(") {
      brackets++;
    } else if (tokens[i] == ")") {
      brackets--;
    }

    if (brackets == 0) {
      inOutIndex = i + 1;
      return true;
    }
    if (brackets < 0) {
      throw InvalidInputException(tokenVectorToString(tokens));
    }
  }

  throw InvalidInputException(tokenVectorToString(tokens));
}

bool IExpression::isBracket(const std::string &c) {
  return c.size() == 1 && isBracket(c[0]);
}

bool IExpression::isOneSymbolToken(char token) {
  static std::string oneSymbolTokens = "+-*/%^!";
  return findCharInStr(token, oneSymbolTokens);
}

bool IExpression::isOneSymbolToken(const std::string &token) {
  return token.size() == 1 && isOneSymbolToken(token[0]);
}

TokenVector IExpression::cutBraces(const TokenVector &tokens) {
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

std::string IExpression::tryPutInBracketsIfNeg(const MathObjectPtr &obj) {
  if (!obj->is<Expression>()) {
    return obj->toString();
  }
  const auto &exprObj = obj->to<Expression>();
  if (exprObj.getInfo()->is<Neg>()) {
    return "(" + exprObj.toString() + ")";
  }
  return obj->toString();
}

void IExpression::validateFunctionArgs(const IFunction &func, const ArgumentsVector &args) const {
  ArgumentsVector nonMatchingArgs = func.getNonMatchingArgs(args);

  for (const auto &arg : nonMatchingArgs) {
    if (!arg.get().is<Variable>() && !arg.get().instanceOf<IConstant>() && !arg.get().instanceOf<IExpression>()) {
      throw InvalidInputException(toString());
    }
  }
}

std::vector<MathObjectPtr> IExpression::getVariables() const {
  return {};
}

}
