#include "fintamath/functions/comparison/Eqv.hpp"

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {
  Eqv::Eqv() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  std::string Eqv::toString() const {
    return "=";
  }

  std::string Eqv::getClassName() const {
    return "Eqv";
  }

  MathObjectPtr Eqv::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    // TODO make Expression here if false
    return std::make_unique<Boolean>(argsVect.at(0).get() == argsVect.at(1).get());
  }
}
