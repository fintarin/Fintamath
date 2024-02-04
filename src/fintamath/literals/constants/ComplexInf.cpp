#include "fintamath/literals/constants/ComplexInf.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> ComplexInf::call() const {
  return clone();
}

}
