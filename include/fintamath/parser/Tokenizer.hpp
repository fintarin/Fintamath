#pragma once

#include <set>
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

  static bool isLetter(char c); // TODO: remove

private:
  static bool appendToken(TokenVector &tokens, Token &token, bool isNumber = false);

  static TokenVector splitTokens(const Token &token);

  static void handleSpaces(std::string &str);

  static bool isDigitOrPoint(char c);

  static bool isOneSymbolToken(const Token &token); // TODO: remove

  static bool isOneSymbolToken(char token); // TODO: remove

  static bool isSpecial(char c); // TODO: remove

  static bool isBracket(char c); // TODO: remove

  static bool isBracket(const std::string &c); // TODO: remove

  static bool isOpenBracket(char c); // TODO: remove

  static bool isCloseBracket(char c); // TODO: remove

  static bool isCanInsertMultiplyCharacter(char c); // TODO: remove

  static bool findCharInStr(char c, const std::string &str); // TODO: remove

  static TokenVector registeredTokens;
};

}