#include "fintamath/literals/constants/E.hpp"

#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

unique_ptr<IMathObject> E::call() const {
  return make_unique<Real>(E_NUM);
}

}
