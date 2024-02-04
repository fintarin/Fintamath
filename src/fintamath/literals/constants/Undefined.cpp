#include "fintamath/literals/constants/Undefined.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Undefined::call() const {
  return clone();
}

}
