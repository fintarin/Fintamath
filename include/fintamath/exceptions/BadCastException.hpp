#pragma once

#include "fintamath/exceptions/Exception.hpp"

namespace fintamath {

class BadCastException : public Exception {
public:
  explicit BadCastException(std::string_view fromClassName, std::string_view toClassName) noexcept;
};

}
