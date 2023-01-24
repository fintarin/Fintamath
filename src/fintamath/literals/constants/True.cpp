#include "fintamath/literals/constants/True.hpp"

namespace fintamath {

MathObjectPtr True::call() const {
  return std::make_unique<Boolean>(true);
}

}
