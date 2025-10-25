#include "fintamath/core/Tokenizer.hpp"

#include <algorithm>
#include <regex>
#include <string>

namespace fintamath::detail {

void Token::clear() {
  name.clear();
  type = TokenType::Unknown;
}

Tokens Tokenizer::tokenize(std::string str) {
  handleSpaces(str);

  Tokens tokens;
  Token unknownToken;
  Token numberToken;

  for (const char ch : str) {
    if (ch >= '0' && ch <= '9') {
      appendToken(tokens, unknownToken);
      numberToken.name.push_back(ch);

      if (numberToken.type != TokenType::Decimal) {
        numberToken.type = TokenType::Integer;
      }
    }
    else if (ch == '.') {
      appendToken(tokens, unknownToken);
      numberToken.name.push_back(ch);
      numberToken.type = TokenType::Decimal;
    }
    else if (ch == ' ') {
      appendToken(tokens, unknownToken);
      appendToken(tokens, numberToken);
    }
    else {
      appendToken(tokens, numberToken);
      unknownToken.name.push_back(ch);
    }
  }

  appendToken(tokens, numberToken);
  appendToken(tokens, unknownToken);

  return tokens;
}

void Tokenizer::registerToken(const std::string_view tokenName) {
  getRegisteredTokens().add(tokenName);
}

bool Tokenizer::appendToken(Tokens &tokens, Token &token) {
  if (token.name.empty()) {
    return false;
  }

  if (token.type != TokenType::Unknown) {
    tokens.emplace_back(std::move(token));
    return true;
  }

  size_t i = 0;
  while (i < token.name.size()) {
    size_t tokenSize = getRegisteredTokens().getPrefixSize(token.name, i);
    const bool isTokenRegistered = tokenSize > 0;
    if (!isTokenRegistered) {
      tokenSize++;
    }

    std::string name = token.name.substr(i, tokenSize);
    TokenType type = isTokenRegistered ? TokenType::Registered : getUnregisteredTokenType(name);
    tokens.emplace_back(Token{
      .name = std::move(name),
      .type = type,
    });

    i += tokenSize;
  }

  token.name.clear();
  token.type = TokenType::Unknown;

  return true;
}

void Tokenizer::handleSpaces(std::string &str) {
  str = std::regex_replace(str, std::regex(R"([\s\r\n]+)"), " ");
}

TokenType Tokenizer::getUnregisteredTokenType(const std::string &tokenName) {
  if (tokenName.size() == 1 && tokenName.front() >= 'a' && tokenName.front() <= 'z') {
    return TokenType::Variable;
  }
  if (tokenName == "(") {
    return TokenType::RoundBracketOpen;
  }
  if (tokenName == ")") {
    return TokenType::RoundBracketClose;
  }
  return TokenType::Unknown;
}

PrefixTrie &Tokenizer::getRegisteredTokens() {
  static PrefixTrie registeredTokens;
  return registeredTokens;
}

}
