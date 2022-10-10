#include "fintamath/literals/constants/Constant.hpp"

#include <memory>

#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"

namespace fintamath {
  ConstantPtr Constant::parse(const std::string &str) {
    if (str == "e") {
      return std::make_unique<E>();
    }
    if (str == "pi") {
      return std::make_unique<Pi>();
    }
    return nullptr;
  }
}
