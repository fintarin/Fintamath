#pragma once

#include <utility>
#include <vector>

#include "fintamath/exceptions/UndefinedException.hpp"

namespace fintamath {
  class UndefinedFunctionException : public UndefinedException {
  public:
    ~UndefinedFunctionException() override = default;

    UndefinedFunctionException(const std::string &func, const std::vector<std::string> &argsVect) {
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
