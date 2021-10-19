#include "Calculator.hpp"

#include <algorithm>
#include <string>
#include <vector>

#include "../operators/NamespaceFunctions.hpp"

Fraction Calculator::E = functions::getE(PRECISION_OF_CONSTANTS + 1).round(PRECISION_OF_CONSTANTS);
Fraction Calculator::PI = functions::getPi(PRECISION_OF_CONSTANTS + 1).round(PRECISION_OF_CONSTANTS);

Fraction &Calculator::getE() {
  return Calculator::E;
}

Fraction &Calculator::getPi() {
  return Calculator::PI;
}

void addPoint(std::string &str) {
  str.insert(str.begin() + 1, '.');
  str += '0';
  str = Fraction(str).toString();
}

size_t cutZeros(std::string &str) {
  size_t order = 0;
  while (*str.begin() == '0') {
    str.erase(str.begin());
    ++order;
  }
  return order;
}

void toFloatingPoint(std::string &str) {
  bool minus = (*str.begin() == '-');
  if (minus) {
    str.erase(0, 1);
  }

  if (str == "0") {
    return;
  }
  if (*str.begin() == '0') {
    str.erase(str.begin() + 1);
    if (str.size() > PRECISION + 1) {
      str.erase(PRECISION + 2);
    }

    size_t order = cutZeros(str);
    addPoint(str);

    str += "*10^(-";
    str += std::to_string(order) + ')';
  } else {
    size_t order = std::distance(std::begin(str), std::find(std::begin(str), std::end(str), '.'));
    if (order != str.size()) {
      str.erase(order, 1);
    }
    if (str.size() > PRECISION + 1) {
      str.erase(PRECISION + 2);
    }

    addPoint(str);

    if (order > 1) {
      str += "*10^";
      str += std::to_string(order - 1);
    }
  }

  if (minus) {
    str.insert(str.begin(), '-');
  }
}

std::string Calculator::calculate(const std::string &inStr) {
  std::vector<std::string> vectIOfTokens = this->parser.makeVectOfTokens(inStr);
  auto firstEqual = std::find(std::begin(vectIOfTokens), std::end(vectIOfTokens), "=");

  Tree tree = this->parser.makeTree(std::vector<std::string>(vectIOfTokens.begin(), firstEqual));
  Fraction res = this->solver.solve(tree);
  if (firstEqual != vectIOfTokens.end()) {
    this->solver.solveEquals(std::vector<std::string>(firstEqual, vectIOfTokens.end()), res);
  }

  std::string resStr = res.toString(PRECISION);
  toFloatingPoint(resStr);
  return resStr;
}
