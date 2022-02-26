#include "fintamath/math_objects/MathObjectParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/nodes/NodeParser.hpp"
#include "fintamath/math_objects/relations/RelationParser.hpp"

namespace fintamath {
  std::string_view MathObjectParser::deleteOpenAndCloseBracket(const std::string_view &str) {
    if (str[0] != '(') {
      return str;
    }
    int leftBracket = 0;
    int rightBracket = 0;
    int position = 0;
    while (position < str.size()) {
      if (str[position] == '(') {
        leftBracket++;
      }
      if (str[position] == ')') {
        rightBracket++;
      } else if (leftBracket == rightBracket) {
        break;
      }
      position++;
    }
    if (position == str.size()) {
      throw std::invalid_argument("");
    }
    if (position == str.size() - 1) {
      return str.substr(1, str.size() - 2);
    }
    return str;
  }
  std::unique_ptr<MathObject> MathObjectParser::parse(const std::string_view &str) {
    auto strForParsing = deleteOpenAndCloseBracket(str);
    if (auto res = RelationParser::parse(strForParsing); res) {
      return res;
    }
    return NodeParser::parse(strForParsing);
  }
}
