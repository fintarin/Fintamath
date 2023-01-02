#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace fintamath {

constexpr uint8_t FINTAMATH_DEFAULT_PRECISION = 100;
constexpr uint8_t FINTAMATH_ROUND_PRECISION = 80;

using ArgumentsVector = std::vector<std::reference_wrapper<const class IMathObject>>;
using TokenVector = std::vector<std::string>;

}
