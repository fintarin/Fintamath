#include "fintamath/parser/Tokenizer.hpp"

#include <algorithm>
#include <regex>

namespace fintamath {

TokenVector Tokenizer::tokenize(std::string str) {
  handleSpaces(str);

  TokenVector tokens;
  Token numberToken;
  Token specialToken;

  for (char ch : str) {
    if (isDigitOrPoint(ch)) {
      appendToken(tokens, specialToken, true);
      numberToken.push_back(ch);
    }
    else if (isSpace(ch)) {
      appendToken(tokens, specialToken, true);
      appendToken(tokens, numberToken, false);
    }
    else {
      appendToken(tokens, numberToken, false);
      specialToken.push_back(ch);
    }
  }

  appendToken(tokens, numberToken, false);
  appendToken(tokens, specialToken, true);

  return tokens;
}

void Tokenizer::registerToken(const Token &token) {
  auto &tokens = getRegisteredTokens();
  tokens.insert(std::ranges::upper_bound(tokens, token, [](const Token &lhs, const Token &rhs) {
                  return lhs.length() > rhs.length();
                }),
                token);
}

bool Tokenizer::appendToken(TokenVector &tokens, Token &token, bool shouldSplit) {
  if (token.empty()) {
    return false;
  }

  if (!shouldSplit) {
    tokens.emplace_back(token);
    token.clear();
    return true;
  }

  while (!token.empty()) {
    std::string nestedToken = token.substr(0, getRegisteredTokens().front().length());
    bool isNestedTokenFind = false;

    for (const auto &registeredToken : getRegisteredTokens()) {
      if (nestedToken.length() < registeredToken.length()) {
        continue;
      }

      if (nestedToken.length() > registeredToken.length()) {
        nestedToken = token.substr(0, registeredToken.length());
      }

      if (nestedToken == registeredToken) {
        isNestedTokenFind = true;
        break;
      }
    }

    if (!isNestedTokenFind) {
      nestedToken = token.substr(0, 1);
    }

    tokens.emplace_back(nestedToken);
    token = token.substr(nestedToken.size());
  }

  token.clear();
  return true;
}

void Tokenizer::handleSpaces(std::string &str) {
  str = std::regex_replace(str, std::regex(R"([\s\r\n]+)"), " ");
}

bool Tokenizer::isDigitOrPoint(char ch) {
  return ch == '.' || (ch >= '0' && ch <= '9');
}

bool Tokenizer::isSpace(char ch) {
  return ch == ' ';
}

}
