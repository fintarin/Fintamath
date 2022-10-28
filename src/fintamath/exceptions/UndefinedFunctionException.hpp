#pragma once

#include <utility>

#include "fintamath/exceptions/UndefinedException.hpp"

namespace fintamath {
  class UndefinedFunctionException : public UndefinedException {
  public:
    ~UndefinedFunctionException() override = default;

    template <typename... Args>
    UndefinedFunctionException(const std::string &func, const Args &...args) {
      static_assert((std::is_same_v<Args, std::string> && ...));

      static const std::string delimiter = ", ";

      content = func + "(";
      content += ((args + delimiter) + ...);
      content = content.substr(0, content.length() - delimiter.length());
      content += ") is undefined";
    }

    const char *what() const noexcept override {
      return content.c_str();
    }

  private:
    std::string content;
  };
}
