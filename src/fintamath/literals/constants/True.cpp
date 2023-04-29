#include "fintamath/literals/constants/True.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> True::call() const {
  return std::make_unique<Boolean>(true);
}

}
