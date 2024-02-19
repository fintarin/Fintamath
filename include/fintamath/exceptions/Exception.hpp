#pragma once

#include <exception>
#include <string>
#include <string_view>

namespace fintamath {

class Exception : public std::exception {
public:
  explicit Exception(const std::string_view inMessage) : message(inMessage) {
  }

  const char *what() const noexcept override {
    return message.data();
  }

private:
  std::string message;
};

}
