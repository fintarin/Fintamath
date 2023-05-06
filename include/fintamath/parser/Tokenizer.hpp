#pragma once

#include <string>
#include <vector>

namespace fintamath {

using Token = std::string;
using TokenVector = std::vector<Token>;

class Tokenizer {
public:
  static TokenVector tokenize(std::string str);

  static void registerToken(const Token &token);

private:
  static bool appendToken(TokenVector &tokens, Token &token, bool shouldSplit = false);

  static TokenVector splitTokens(const Token &token);

  static void handleSpaces(std::string &str);

  static bool isDigitOrPoint(char ch);

  static bool isSpace(char ch);

  static TokenVector &getRegisteredTokens();
};

}