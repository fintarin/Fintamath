#include "fintamath/literals/constants/False.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr False::call() const {
  return std::make_unique<Boolean>(false);
}

}
