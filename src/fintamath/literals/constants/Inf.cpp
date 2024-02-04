#include "fintamath/literals/constants/Inf.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Inf::call() const {
  return clone();
}

}
