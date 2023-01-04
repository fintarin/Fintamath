#include "fintamath/parser/Tokenizer.hpp"

#include <algorithm>
#include <regex>

namespace fintamath {

// TODO: tokenize this way:
// if isDigitOrPoint(ch), then parse numberToken
// else parse registeredToken
// else parse char as it is

TokenVector Tokenizer::tokenize(std::string str) {
  handleSpaces(str);

  TokenVector tokens;
  Token numberToken;
  Token letterToken;
  Token specialToken;

  for (size_t i = 0; i < str.size(); i++) {
    const auto &ch = str[i];

    if (isDigitOrPoint(ch)) {
      appendToken(tokens, letterToken);
      appendToken(tokens, specialToken);
      numberToken.push_back(ch);

      if (!tokens.empty() && tokens.at(tokens.size() - 1) == ")") { // TODO: do it in IExpression or Expression
        tokens.emplace_back("*");
      }
      continue;
    }

    if (isLetter(ch)) {
      letterToken.push_back(ch);
      if (appendToken(tokens, numberToken, true)) {
        tokens.emplace_back("*");
      }
      appendToken(tokens, specialToken);

      if (!tokens.empty() && tokens.at(tokens.size() - 1) == ")") { // TODO: do it in IExpression or Expression
        tokens.emplace_back("*");
      }
      continue;
    }

    if (isBracket(ch)) {
      appendToken(tokens, numberToken, true);
      appendToken(tokens, specialToken);
      appendToken(tokens, letterToken);

      if (((!tokens.empty() && tokens.at(tokens.size() - 1) == ")")) && isOpenBracket(ch) &&
          ch == '(') { // TODO: do it in IExpression or Expression
        tokens.emplace_back("*");
      }

      tokens.emplace_back(1, ch);
      continue;
    }

    if (isSpecial(ch)) {
      appendToken(tokens, numberToken, true);
      appendToken(tokens, letterToken);
      specialToken.push_back(ch);
      continue;
    }

    if (ch == ' ') { // TODO: do it in IExpression or Expression
      appendToken(tokens, specialToken);
      if (!isCanInsertMultiplyCharacter(str[i + 1])) {
        continue;
      }
      if (appendToken(tokens, numberToken, true)) {
        tokens.emplace_back("*");
        continue;
      }
      if (!letterToken.empty() && isLetter(str[i + 1])) {
        appendToken(tokens, letterToken);
        tokens.emplace_back("*");
      }
    }
  }

  appendToken(tokens, numberToken, true);
  appendToken(tokens, specialToken);
  appendToken(tokens, letterToken);

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

bool Tokenizer::appendToken(TokenVector &tokens, Token &token, bool isNumber) {
  if (token.empty()) {
    return false;
  }

  if (isNumber) {
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
      tokens.emplace_back(token.substr(0, 1));
      token = token.substr(1);
    } else {
      tokens.emplace_back(nestedToken);
      token = token.substr(nestedToken.size());
    }
  }

  return true;
}

void Tokenizer::handleSpaces(std::string &str) {
  str = std::regex_replace(str, std::regex(R"([\s\r\n]+)"), " ");

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

bool Tokenizer::isLetter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Tokenizer::isBracket(char c) {
  return isOpenBracket(c) || isCloseBracket(c);
}

bool Tokenizer::isBracket(const std::string &c) {
  return c.size() == 1 && isBracket(c[0]);
}

bool Tokenizer::isOpenBracket(char c) {
  return c == '(' || c == '{' || c == '[';
}

bool Tokenizer::isCloseBracket(char c) {
  return c == ')' || c == '}' || c == ']';
}

bool Tokenizer::isSpecial(char c) {
  return (c >= '!' && c <= '/') || (c >= ':' && c <= '@') || (c >= '[' && c <= '`') || (c >= '{' && c <= '~');
}

bool Tokenizer::isCanInsertMultiplyCharacter(char c) {
  return c != ' ' && !isSpecial(c);
}

bool Tokenizer::findCharInStr(char c, const std::string &str) {
  return std::find(str.begin(), str.end(), c) != str.end();
}

}
