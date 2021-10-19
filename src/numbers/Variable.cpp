#include "Variable.hpp"

#include <string>

#include "../calculator/ExceptionClasses.hpp"

Variable::Variable(const Variable &other) {
  this->name = other.name;
}

Variable::Variable(const std::string &inStr) {
  if (!isType::isVariable(inStr)) {
    throw IncorrectInput("Variable");
  }
  this->name = *inStr.begin();
}

Variable &Variable::operator=(const Variable &other) {
  this->name = other.name;
  return *this;
}

namespace isType {
bool isVariable(const std::string &inStr) {
  if (inStr.size() != 1) {
    return false;
  }
  if (*inStr.begin() >= 'A' && *inStr.begin() <= 'Z') {
    return true;
  }
  if (*inStr.begin() >= 'a' && *inStr.begin() <= 'z') {
    return true;
  }
  return false;
}
} // namespace isType

char Variable::getName() const {
  return this->name;
}

const std::string Variable::getTypeName() const {
  return "Variable";
}

const std::string Variable::toString() const {
  std::string res;
  res += this->name;
  return res;
}
