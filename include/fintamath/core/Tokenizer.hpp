#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "fintamath/core/PrefixTrie.hpp"

namespace fintamath::detail {

enum class TokenType : uint8_t {
  Unknown,
  Registered,
  Variable,
  Integer,
  Decimal,
  RoundBracketOpen,
  RoundBracketClose,
};

struct Token {
  std::string name;
  TokenType type = TokenType::Unknown;

public:
  void clear();
};

using TokenVector = std::vector<Token>;

class Tokenizer final {
public:
  static TokenVector tokenize(std::string str);

  static void registerToken(std::string_view tokenName);

private:
  static bool appendToken(TokenVector &tokens, Token &token);

  static void handleSpaces(std::string &str);

  static TokenType getUnregisteredTokenType(const std::string &tokenName);

  static PrefixTrie &getRegisteredTokens();
};

}
