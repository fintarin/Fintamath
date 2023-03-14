#include "fintamath/literals/constants/Pi.hpp"

#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

unique_ptr<IMathObject> Pi::call() const {
  return make_unique<Real>(PI_NUM);
}

}
