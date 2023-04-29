#include "fintamath/literals/constants/E.hpp"

#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> E::call() const {
  return std::make_unique<Real>(E_NUM);
}

}
