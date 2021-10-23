#include "calculator/Calculator.hpp"

#include <algorithm>
#include <string>
#include <vector>

#include "single_entities/operators/NamespaceFunctions.hpp"

using namespace std;

static void addPoint(string &str);

size_t cutZeros(string &str) {
  size_t order = 0;
  while (*str.begin() == '0') {
    str.erase(str.begin());
    ++order;
  }
  return order;
}

void Calculator::toFloatingPoint(string &str) {
  bool minus = (*str.begin() == '-');
  if (minus) {
    str.erase(0, 1);
  }

  if (str == "0") {
    return;
  }
  if (*str.begin() == '0') {
    str.erase(str.begin() + 1);
    if (str.size() > 1 && str.size() > solver.getPrecision() + 2) {
      str.erase(solver.getPrecision() + 2);
    }

    size_t order = cutZeros(str);
    addPoint(str);

    str += "*10^(-";
    str += to_string(order) + ')';
  } else {
    size_t order = distance(begin(str), find(begin(str), end(str), '.'));
    if (order != str.size()) {
      str.erase(order, 1);
    }
    if (str.size() > solver.getPrecision() + 1) {
      str.erase(solver.getPrecision() + 2);
    }

    addPoint(str);

    if (order > 1) {
      str += "*10^";
      str += to_string(order - 1);
    }
  }

  if (minus) {
    str.insert(str.begin(), '-');
  }
}

string Calculator::calculate(const string &inStr) {
  Expression Expression(inStr);
  Rational res = this->solver.solve(Expression);
  string resStr = res.toString(solver.getPrecision());
  toFloatingPoint(resStr);
  return resStr;
}

int64_t Calculator::getPrecision() {
  return solver.getPrecision();
}

inline void addPoint(string &str) {
  str.insert(str.begin() + 1, '.');
  str += '0';
  str = Rational(str).toString();
}

void Calculator::setPrecision(int64_t precision) {
  solver.setPrecision(precision);
}
