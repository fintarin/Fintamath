#pragma once

#include <string>
#include <vector>

#include "fintamath/core/CoreDefines.hpp"

namespace fintamath {

using Token = string;
using TokenVector = vector<Token>;

class Tokenizer {
public:
  static TokenVector tokenize(string str);

  static string tokensToString(const TokenVector &tokens);

  static void registerToken(const Token &token);

private:
  static bool appendToken(TokenVector &tokens, Token &token, bool shouldSplit);

  static TokenVector splitTokens(const Token &token);

  static void handleSpaces(string &str);

  static bool isDigitOrPoint(char c);

  static bool isLowerLetter(char c);

  static bool isUpperLetter(char c);

  static bool isBracket(char c);

  static bool isOpenBracket(char c);

  static bool isCloseBracket(char c);

  static TokenVector registeredTokens;
};

}