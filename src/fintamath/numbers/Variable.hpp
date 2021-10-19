#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <string>

#include "calculator/NodeType.hpp"

class Variable : public NodeType {
public:
  explicit Variable(const std::string &);
  char getName() const;
  std::string getTypeName() const override;
  std::string toString() const override;

private:
  char name{};
};

namespace isType {
bool isVariable(const std::string &);
}

#endif // VARIABLE_HPP