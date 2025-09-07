
#include "fintamath/constants/ImaginaryUnit.hpp"

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(ImaginaryUnit)

SharedPtr<IMathObject> ImaginaryUnit::getValue() const noexcept {
  static const auto obj = makeShared<Complex>(0, 1);
  return obj;
}

std::string ImaginaryUnit::toString() const noexcept {
  return "I";
}

}
