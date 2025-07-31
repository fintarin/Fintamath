#include "fintamath/core/Tokenizer.hpp"

#include <algorithm>
#include <regex>
#include <string>

namespace fintamath::detail {

void Token::clear() {
  name.clear();
  type = TokenType::Unknown;
}

TokenVector Tokenizer::tokenize(std::string str) {
  handleSpaces(str);

  TokenVector tokens;
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

void Tokenizer::registerToken(const std::string &tokenName) {
  auto &registeredTokenNames = getRegisteredTokenNames();
  const auto upperBound = std::ranges::upper_bound(
    registeredTokenNames, tokenName, [](const std::string &lhs, const std::string &rhs) {
      return lhs.size() > rhs.size();
    }
  );

  // TODO: check already registered tokens
  registeredTokenNames.insert(upperBound, tokenName);
}

bool Tokenizer::appendToken(TokenVector &tokens, Token &token) {
  if (token.name.empty()) {
    return false;
  }

  if (token.type != TokenType::Unknown) {
    tokens.emplace_back(std::move(token));
    return true;
  }

  while (!token.name.empty()) {
    std::vector<std::string> &registeredTokenNames = getRegisteredTokenNames();

    Token nestedToken = {
      .name = token.name.substr(0, registeredTokenNames.front().size()),
      .type = TokenType::Unknown,
    };

    for (const auto &registeredTokenName : registeredTokenNames) {
      if (nestedToken.name.size() < registeredTokenName.size()) {
        continue;
      }

      if (nestedToken.name.size() > registeredTokenName.size()) {
        nestedToken.name = token.name.substr(0, registeredTokenName.size());
      }

      if (nestedToken.name == registeredTokenName) {
        nestedToken.type = TokenType::Registered;
        break;
      }
    }

    if (nestedToken.type == TokenType::Unknown) {
      nestedToken.name = token.name.substr(0, 1);
      nestedToken.type = getUnregisteredTokenType(nestedToken.name);
    }

    token.name = token.name.substr(nestedToken.name.size());
    tokens.emplace_back(std::move(nestedToken));
    nestedToken.clear();
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

std::vector<std::string> &Tokenizer::getRegisteredTokenNames() {
  static std::vector<std::string> registeredTokenNames;
  return registeredTokenNames;
}

}
