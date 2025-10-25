#include "fintamath/exceptions/BadCastException.hpp"

#include <fmt/format.h>

namespace fintamath {

BadCastException::BadCastException(std::string_view fromClassName, std::string_view toClassName) noexcept
    : Exception(fmt::format("Bad cast from {} to {}", fromClassName, toClassName)) {}

}
