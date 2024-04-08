#include "fintamath/literals/constants/ComplexInf.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(ComplexInf)

std::unique_ptr<IMathObject> ComplexInf::call() const {
  return clone();
}

}
