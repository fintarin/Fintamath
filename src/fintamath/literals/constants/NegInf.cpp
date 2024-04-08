#include "fintamath/literals/constants/NegInf.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(NegInf)

std::unique_ptr<IMathObject> NegInf::call() const {
  return clone();
}

}
