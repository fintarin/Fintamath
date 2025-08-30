#include "fintamath/constants/Inf.hpp"

#include <memory>

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Inf)

std::unique_ptr<IMathObject> Inf::getValue(bool /*shouldApproximate*/) const noexcept {
  return nullptr;
}

}
