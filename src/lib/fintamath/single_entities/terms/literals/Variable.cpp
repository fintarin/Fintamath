#include "single_entities/terms/literals/Variable.hpp"

#include <stdexcept>
#include <string>

using namespace std;

Variable::Variable(const string &inStr) {
  if (!isType::isVariable(inStr)) {
    throw invalid_argument("Variable invalid input");
  }
  this->name = *inStr.begin();
}

namespace isType {
bool isVariable(const string &inStr) {
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

string Variable::getTypeName() const {
  return "Variable";
}

string Variable::toString() const {
  string res;
  res += this->name;
  return res;
}
