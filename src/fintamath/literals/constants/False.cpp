#include "fintamath/literals/constants/False.hpp"

namespace fintamath {

MathObjectPtr False::call() const {
  return std::make_unique<Boolean>(false);
}

}
