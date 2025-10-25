#pragma once

#include "fintamath/exceptions/Exception.hpp"

namespace fintamath {

class NullPointerException : public Exception {
public:
  explicit NullPointerException() noexcept : Exception("Null pointer received") {}
};

}
