#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

#include "calculator/Expression.hpp"

class Parser {
public:
  static std::vector<std::string> makeVectOfTokens(const std::string &);
  static Expression makeTree(const std::vector<std::string> &);
};

#endif // PARSER_HPP