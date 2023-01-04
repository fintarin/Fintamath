#include "fintamath/literals/constants/True.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr True::call() const {
  return std::make_unique<Boolean>(true);
}

}
