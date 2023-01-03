#include "fintamath/tokenizer/Tokenizer.hpp"

#include <algorithm>

namespace fintamath {

TokenVector Tokenizer::tokenize(const std::string &str) {
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

bool Tokenizer::isLetter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Tokenizer::isOneSymbolToken(const std::string &token) {
  return token.size() == 1 && isOneSymbolToken(token[0]);
}

bool Tokenizer::isOneSymbolToken(char token) {
  static std::string oneSymbolTokens = "+-*/%^!";
  return findCharInStr(token, oneSymbolTokens);
}

std::string Tokenizer::tokensToString(const TokenVector &tokens) {
  std::string res;

  for (const auto &token : tokens) {
    res += token;
  }

  return res;
}

bool Tokenizer::appendToken(TokenVector &tokens, std::string &token) {
  if (!token.empty()) {
    tokens.emplace_back(token);
    token.clear();
    return true;
  }

  return false;
}

bool Tokenizer::isDigit(char c) {
  return c >= '0' && c <= '9';
}

bool Tokenizer::isBracket(char c) {
  return isOpenBracket(c) || isCloseBracket(c);
}

bool Tokenizer::isBracket(const std::string &c) {
  return c.size() == 1 && isBracket(c[0]);
}

bool Tokenizer::isOpenBracket(char c) {
  return c == '(' || c == '{' || c == '[';
}

bool Tokenizer::isCloseBracket(char c) {
  return c == ')' || c == '}' || c == ']';
}

bool Tokenizer::isSpecial(char c) { // TODO: remove
  return (c >= '!' && c <= '/') || (c >= ':' && c <= '@') || (c >= '[' && c <= '`') || (c >= '{' && c <= '~');
}

std::string Tokenizer::cutSpacesFromBeginEnd(const std::string &str) {
  std::string result = str;

  while (!result.empty() && result[result.size() - 1] == ' ') {
    result.pop_back();
  }

  while (!result.empty() && result[0] == ' ') {
    result.erase(result.begin());
  }

  return result;
}

bool Tokenizer::isCanInsertMultiplyCharacter(char c) {
  return c != ' ' && !isSpecial(c);
}

bool Tokenizer::findCharInStr(char c, const std::string &str) {
  return std::find(str.begin(), str.end(), c) != str.end();
}

}
