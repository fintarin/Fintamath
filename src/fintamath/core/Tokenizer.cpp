#include "fintamath/core/Tokenizer.hpp"

#include <algorithm>
#include <regex>
#include <string>

namespace fintamath::detail {

TokenVector Tokenizer::tokenize(std::string str) {
  handleSpaces(str);

  TokenVector tokens;
  Token numberToken;
  Token specialToken;

  for (const char ch : str) {
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

void Tokenizer::registerToken(const std::string_view tokenName) {
  getRegisteredTokens().add(tokenName);
}

bool Tokenizer::appendToken(TokenVector &tokens, Token &token, const bool shouldSplit) {
  if (token.empty()) {
    return false;
  }

  if (!shouldSplit) {
    tokens.emplace_back(token);
    token.clear();
    return true;
  }

  size_t i = 0;
  while (i < token.size()) {
    constexpr size_t minTokenSize = 1;
    const size_t tokenSize = std::max(getRegisteredTokens().getPrefixSize(token, i), minTokenSize);
    tokens.emplace_back(token.substr(i, tokenSize));
    i += tokenSize;
  }

  token.clear();
  return true;
}

void Tokenizer::handleSpaces(std::string &str) {
  str = std::regex_replace(str, std::regex(R"([\s\r\n]+)"), " ");
}

bool Tokenizer::isDigitOrPoint(const char ch) {
  return ch == '.' || (ch >= '0' && ch <= '9');
}

bool Tokenizer::isSpace(const char ch) {
  return ch == ' ';
}

PrefixTrie &Tokenizer::getRegisteredTokens() {
  static PrefixTrie registeredTokens;
  return registeredTokens;
}

}
