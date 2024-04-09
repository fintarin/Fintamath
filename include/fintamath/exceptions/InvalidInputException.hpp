#pragma once

#include <string>
#include <utility>

#include "fintamath/exceptions/Exception.hpp"

namespace fintamath {

class InvalidInputException : public Exception {
public:
  explicit InvalidInputException(std::string inMessage) noexcept : Exception(std::move(inMessage)) {}
};

}
