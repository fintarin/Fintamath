#include "fintamath/literals/constants/ComplexInf.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> ComplexInf::call() const {
  return clone();
}

}
