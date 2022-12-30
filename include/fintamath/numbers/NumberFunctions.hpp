#include "fintamath/numbers/INumber.hpp"

namespace fintamath {
  template <typename NumberT, typename = std::enable_if_t<std::is_base_of_v<INumber, NumberT>>>
  NumberT abs(const NumberT &rhs) {
    if (rhs < 0) {
      return -rhs;
    }
    return rhs;
  }
}
