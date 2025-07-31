#include "fintamath/constants/ComplexInf.hpp"

#include <memory>

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(ComplexInf)

std::unique_ptr<IMathObject> ComplexInf::getValue(const bool /*shouldApproximate*/) const noexcept {
  return nullptr;
}

}
