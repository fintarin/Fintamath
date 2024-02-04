#include "fintamath/literals/constants/I.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> I::call() const {
  return std::make_unique<Complex>(Integer(0), Integer(1));
}

}
