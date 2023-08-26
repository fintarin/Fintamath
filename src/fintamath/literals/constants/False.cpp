#include "fintamath/literals/constants/False.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> False::call() const {
  return Boolean(false).clone();
}

}
