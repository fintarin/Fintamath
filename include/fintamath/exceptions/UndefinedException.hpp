#pragma once

#include <string>
#include <utility>

#include "fintamath/exceptions/Exception.hpp"

namespace fintamath {

class UndefinedException : public Exception {
public:
  UndefinedException() = default;

  ~UndefinedException() override = default;

  UndefinedException(const string &input) {
    content += ": " + input;
  }

  const char *what() const noexcept override {
    return content.c_str();
  }

protected:
  string content = "Undefined";
};

}
