#include "fintamath/literals/constants/I.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> I::call() const {
  return std::make_unique<Complex>(Integer(0), Integer(1));
}

}
