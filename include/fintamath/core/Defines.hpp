#pragma once

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {
  using ArgumentsVector = std::vector<std::reference_wrapper<const IMathObject>>;
  using TokenVector = std::vector<std::string>;
}
