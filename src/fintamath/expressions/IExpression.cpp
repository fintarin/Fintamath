#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/core/Defines.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/helpers/Converter.hpp"
#include <algorithm>

namespace fintamath {
  TokenVector IExpression::tokenize(const std::string &str) {
    static const std::string oneSymbolTokens = "+-*/%";
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

        if(!tokens.empty() && tokens.at(tokens.size() - 1) == ")"){
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

        if(!tokens.empty() && tokens.at(tokens.size() - 1) == ")"){
          tokens.emplace_back("*");
        }
        continue;
      }

      if (isBracket(value)) {
        if ((appendToken(tokens, digitToken) || (!tokens.empty() && tokens.at(tokens.size() - 1) == ")")) && isOpenBracket(value) && value == '(') {
          tokens.emplace_back("*");
        }
        appendToken(tokens, specialToken);
        appendToken(tokens, letterToken);
        tokens.emplace_back(1, value);
        continue;
      }

      if (isSpecial(value)) {
        appendToken(tokens, digitToken);
        appendToken(tokens, letterToken);
        if (isOneSymbolToken(value)) {
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

  std::string IExpression::tokensToString(const TokenVector &tokens) {
    std::string result;
    for (const auto &token : tokens) {
      result += token;
    }
    return result;
  }

  bool IExpression::findCharInStr(char c, const std::string &str) {
    return std::find(str.begin(), str.end(), c) != str.end();
  }

  bool IExpression::isCanInsertMultiplyCharacter(char c) {
    return !(c == ' ' || isSpecial(c));
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

  bool IExpression::skipBrackets(const TokenVector &tokens, size_t &openBracketIndex) {
    if (openBracketIndex >= tokens.size()) {
      return true;
    }
    if (tokens[openBracketIndex] != "(") {
      return true;
    }

    int leftBrackets = 0;
    int rightBrackets = 0;
    for (size_t position = openBracketIndex; position < tokens.size(); position++) {
      if (tokens[position] == ")") {
        rightBrackets++;
      }
      if (tokens[position] == "(") {
        leftBrackets++;
      }
      if (leftBrackets == rightBrackets) {
        openBracketIndex = position + 1;
        return true;
      }
    }
    return false;
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

  std::vector<MathObjectPtr> IExpression::getVariables() const{
    return {};
  }


}
