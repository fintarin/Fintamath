#pragma once

#include <string>
#include <utility>

#include "fintamath/exceptions/Exception.hpp"

namespace fintamath {

class UndefinedException : public Exception {
public:
  explicit UndefinedException(std::string inMessage) noexcept : Exception(std::move(inMessage)) {}
};

}
