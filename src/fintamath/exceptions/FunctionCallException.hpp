#pragma once

#include <string>
#include <utility>
#include <vector>

#include "fintamath/exceptions/Exception.hpp"

namespace fintamath {
  class FunctionCallException : public Exception {
  public:
    FunctionCallException() = default;

    ~FunctionCallException() override = default;

    FunctionCallException(const std::string &func, const std::vector<std::string> &argsVect) {
      content += "Cannot call " + func + " for arguments (";

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

  protected:
    std::string content;
  };
}
