#include "fintamath/literals/constants/False.hpp"

namespace fintamath {

unique_ptr<IMathObject> False::call() const {
  return make_unique<Boolean>(false);
}

}
