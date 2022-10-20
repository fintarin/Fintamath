#include "fintamath/numbers/INumber.hpp"

#include <memory>

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {
  NumberPtr fintamath::INumber::parse(const std::string &str) {
    try {
      return std::make_unique<Integer>(str);
    } catch (const std::invalid_argument &) {
      // do nothing
    };

    try {
      return std::make_unique<Rational>(str);
    } catch (const std::invalid_argument &) {
      // do nothing
    }

    return nullptr;
  }

  NumberPtr INumber::parse(int64_t num) {
    return std::make_unique<Integer>(num);
  }
}
