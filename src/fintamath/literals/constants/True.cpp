#include "fintamath/literals/constants/True.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(True)

std::unique_ptr<IMathObject> True::call() const {
  return Boolean(true).clone();
}

}
