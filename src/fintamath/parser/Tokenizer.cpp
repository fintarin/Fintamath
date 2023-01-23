#include "fintamath/parser/Tokenizer.hpp"

#include <algorithm>
#include <regex>

namespace fintamath {

TokenVector Tokenizer::tokenize(std::string str) {
  handleSpaces(str);

  TokenVector tokens;
  Token numberToken;
  Token specialToken;

  for (char &ch : str) {
    if (isBracket(ch)) {
      if (appendToken(tokens, numberToken, false)) {
        if (ch == '(') {
          tokens.emplace_back("*");
        }
      }

      appendToken(tokens, specialToken, true);

      if (!tokens.empty() && tokens.back() == ")" && ch == '(') { // TODO: do it in IExpression or Expression
        tokens.emplace_back("*");
      }

      tokens.emplace_back(1, ch);
    } else if (isDigitOrPoint(ch)) {
      appendToken(tokens, specialToken, true);
      numberToken.push_back(ch);

      if (!tokens.empty() && tokens.back() == ")") { // TODO: do it in IExpression or Expression
        tokens.emplace_back("*");
      }
    } else {
      appendToken(tokens, numberToken, false);
      specialToken.push_back(ch);
    }
  }

  appendToken(tokens, numberToken, false);
  appendToken(tokens, specialToken, true);

  return tokens;
}

std::string Tokenizer::tokensToString(const TokenVector &tokens) {
  std::string res;

  for (const auto &token : tokens) {
    res += token;
  }

  return res;
}

void Tokenizer::registerToken(const Token &token) {
  // TODO: use more efficient algorithm to emplace
  registeredTokens.emplace_back(token);
  std::sort(registeredTokens.begin(), registeredTokens.end(),
            [](const Token &a, const Token &b) { return a.length() > b.length(); });
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
    std::string nestedToken = token.substr(0, registeredTokens.front().length());
    bool isNestedTokenFind = false;

    for (const auto &registeredToken : registeredTokens) {
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

      // TODO: do it in IExpression or Expression
      if (!tokens.empty() && (isDigitOrPoint(tokens.back().back()) || tokens.at(tokens.size() - 1) == ")") &&
          token != ",") {
        tokens.emplace_back("*");
      }
    }

    tokens.emplace_back(nestedToken);
    token = token.substr(nestedToken.size());
  }

  token.clear();
  return true;
}

void Tokenizer::handleSpaces(std::string &str) {
  str = std::regex_replace(str, std::regex(R"([\s\r\n]+)"), "");

  if (str.front() == ' ') {
    str = str.substr(0);
  }
  if (str.back() == ' ') {
    str.pop_back();
  }
}

bool Tokenizer::isDigitOrPoint(char c) {
  return c == '.' || (c >= '0' && c <= '9');
}

bool Tokenizer::isBracket(char c) {
  return isOpenBracket(c) || isCloseBracket(c);
}

bool Tokenizer::isOpenBracket(char c) {
  return c == '(' || c == '{' || c == '[';
}

bool Tokenizer::isCloseBracket(char c) {
  return c == ')' || c == '}' || c == ']';
}

bool Tokenizer::findCharInStr(char c, const std::string &str) {
  return std::find(str.begin(), str.end(), c) != str.end();
}

}
