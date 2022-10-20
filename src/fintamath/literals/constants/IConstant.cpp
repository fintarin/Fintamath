#include "fintamath/literals/constants/IConstant.hpp"

#include <memory>

#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"

namespace fintamath {
  ConstantPtr IConstant::parse(const std::string &str) {
    if (str == "e") {
      return std::make_unique<E>();
    }
    if (str == "pi") {
      return std::make_unique<Pi>();
    }
    return nullptr;
  }
}
