#include "fintamath/literals/constants/True.hpp"

namespace fintamath {

unique_ptr<IMathObject> True::call() const {
  return make_unique<Boolean>(true);
}

}
