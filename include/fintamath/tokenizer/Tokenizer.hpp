#pragma once

#include <string>
#include <vector>

namespace fintamath {

using TokenVector = std::vector<std::string>;

class Tokenizer {
public:
  static TokenVector tokenize(const std::string &str);

  static bool isLetter(char c); // TODO: remove

  static bool isOneSymbolToken(const std::string &token); // TODO: remove this and implement Expression::splitOperator

  static bool isOneSymbolToken(char token); // TODO: remove this and implement Expression::splitOperator

  static bool isSpecial(char c);

  static std::string tokensToString(const TokenVector &tokens);

private:
  static bool appendToken(TokenVector &tokens, std::string &token);

  static bool isDigit(char c);

  static bool isBracket(char c);

  static bool isBracket(const std::string &c);

  static bool isOpenBracket(char c);

  static bool isCloseBracket(char c);

  static std::string cutSpacesFromBeginEnd(const std::string &str);

  static bool isCanInsertMultiplyCharacter(char c);

  static bool findCharInStr(char c, const std::string &str);
};

}