#pragma once

#include <string>
#include <vector>

namespace fintamath {

using Token = std::string;
using TokenVector = std::vector<Token>;

class Tokenizer {
public:
  static TokenVector tokenize(std::string str);

  static std::string tokensToString(const TokenVector &tokens);

  static void registerToken(const Token &token);

private:
  static bool appendToken(TokenVector &tokens, Token &token, bool shouldSplit);

  static TokenVector splitTokens(const Token &token);

  static void handleSpaces(std::string &str);

  static bool isDigitOrPoint(char c);

  static bool isLowerLetter(char c);

  static bool isUpperLetter(char c);

  static bool isBracket(char c);

  static bool isOpenBracket(char c);

  static bool isCloseBracket(char c);

  static TokenVector &getRegisteredTokens() {
    static TokenVector registeredTokens;
    return registeredTokens;
  }
};

}