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
        static const std::string delimiter = ", ";

        for (const auto &arg : argsVect) {
          content += arg + delimiter;
        }

        content = content.substr(0, content.length() - delimiter.length());
      }

      content += ")";
    }

    const char *what() const noexcept override {
      return content.c_str();
    }
  };
}
