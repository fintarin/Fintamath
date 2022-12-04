#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {
  IExpression::TokenVector IExpression::tokenize(const std::string & str) {
    std::string tokenizeStr = cutSpacesFromBeginEnd(str);
    TokenVector tokens;
    std::string digitToken;
    std::string letterToken;
    std::string specialToken;

    for(const auto & value: tokenizeStr ){
      if(isDigit(value) || value == '.'){
        digitToken.push_back(value);
        appendToken(tokens, letterToken);
        appendToken(tokens, specialToken);
        continue;
      }

      if(isLetter(value)){
        letterToken.push_back(value);
        if(appendToken(tokens, digitToken)){
          tokens.push_back("*");
        }
        appendToken(tokens, specialToken);
        continue;
      }

      if(isBracket(value)){
        appendToken(tokens, digitToken);
        appendToken(tokens, specialToken);
        appendToken(tokens, letterToken);
        tokens.push_back(std::string(1, value));
        continue;
      }
      
      if(isSpecial(value)){
        specialToken.push_back(value);
        appendToken(tokens, digitToken);
        appendToken(tokens, letterToken);
        continue;
      }

      if(value == ' '){
        appendToken(tokens, digitToken);
        appendToken(tokens, specialToken);
        appendToken(tokens, letterToken);
        if(!tokens.empty() && tokens.back() != "*"){
          tokens.push_back("*");
        }
      }
    }
    appendToken(tokens, digitToken);
    appendToken(tokens, specialToken);
    appendToken(tokens, letterToken);
    return tokens;
  }

  bool IExpression::isDigit(char c){
    return c >= '0' && c <='9';
  }

  bool IExpression::isLetter(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
  }

  bool IExpression::isBracket(char c){
    return c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']';
  }

  bool IExpression::isSpecial(char c){
    return (c >='!' && c <= '/') || (c >= ':' && c <= '@') || (c >= '[' && c <= '`') || (c >= '{' && c <= '~');
  }

  bool IExpression::appendToken(TokenVector& tokens, std::string& token){
    if(!token.empty()){
      tokens.push_back(token);
      token.clear();
      return true;
    }
    return false;
  }

  std::string IExpression::cutSpacesFromBeginEnd(const std::string& str){
    std::string result = str;
    while(!result.empty() && result[result.size() - 1] == ' '){
      result.pop_back();
    }
    while(!result.empty() && result[0] == ' '){
      result.erase(result.begin());
    }
    return result;
  }
}
