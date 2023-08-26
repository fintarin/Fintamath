#include "fintamath/literals/constants/True.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> True::call() const {
  return Boolean(true).clone();
}

}
