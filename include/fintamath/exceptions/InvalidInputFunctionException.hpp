#pragma once

#include <utility>
#include <vector>

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

class InvalidInputFunctionException : public InvalidInputException {
public:
  ~InvalidInputFunctionException() override = default;

  InvalidInputFunctionException(const string &func, const vector<string> &argsVect) {
    content += ": " + func + "(";

    if (!argsVect.empty()) {
      for (const auto &arg : argsVect) {
        content += arg + ',';
      }

      content.pop_back();
    }

    content += ")";
  }

  const char *what() const noexcept override {
    return content.c_str();
  }
};

}
