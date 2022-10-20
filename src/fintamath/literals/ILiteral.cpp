#include "fintamath/literals/ILiteral.hpp"

#include <stdexcept>

#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {
  LiteralPtr ILiteral::parse(const std::string &str) {
    if (ConstantPtr ptr = IConstant::parse(str)) {
      return ptr;
    }

    try {
      return std::make_unique<Variable>(str);
    } catch (const std::invalid_argument &) {
      // do nothing
    }

    return nullptr;
  }
}
