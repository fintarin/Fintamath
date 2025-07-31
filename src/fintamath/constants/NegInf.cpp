#include "fintamath/constants/NegInf.hpp"

#include <memory>

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(NegInf)

std::unique_ptr<IMathObject> NegInf::getValue(bool /*shouldApproximate*/) const noexcept {
  return nullptr;
}

}
