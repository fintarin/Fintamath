#include "fintamath/literals/constants/ComplexInf.hpp"

#include <memory>

#include "fintamath/numbers/Number.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(ComplexInf)

MathObjectClass ComplexInf::getValueClass() const noexcept {
  return Number::getClassStatic();
}

std::unique_ptr<MathObject> ComplexInf::getValue(const bool /*shouldApproximate*/) const noexcept {
  return nullptr;
}

}
