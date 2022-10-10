#include "fintamath/literals/Literal.hpp"

#include <stdexcept>

#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/Constant.hpp"

namespace fintamath {
  LiteralPtr Literal::parse(const std::string &str) {
    if (ConstantPtr ptr = Constant::parse(str)) {
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
