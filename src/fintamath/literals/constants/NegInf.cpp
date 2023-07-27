#include "fintamath/literals/constants/NegInf.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> NegInf::call() const {
  return clone();
}

}
