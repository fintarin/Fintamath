#pragma once

#include <exception>
#include <string>
#include <utility>

namespace fintamath {

class Exception : public std::exception {
public:
  explicit Exception(std::string inMessage) noexcept : message(std::move(inMessage)) {}

  const char *what() const noexcept override {
    return message.data();
  }

private:
  std::string message;
};

}
