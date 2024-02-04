#include "fintamath/literals/constants/False.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> False::call() const {
  return Boolean(false).clone();
}

}
