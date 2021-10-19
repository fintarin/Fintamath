#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

#include "calculator/Tree.hpp"

class Parser {
public:
  std::vector<std::string> makeVectOfTokens(const std::string &) const;
  Tree makeTree(const std::vector<std::string> &) const;
};

#endif // PARSER_HPP