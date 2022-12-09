#include "fintamath/functions/powers/Pow.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  Pow::Pow() : IOperatorCRTP(IOperator::Priority::Exponentiation) {
  }

  std::string Pow::toString() const {
    return "^";
  }

  std::string Pow::getClassName() const {
    return "Pow";
  }

  MathObjectPtr Pow::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return pow(helpers::Converter::convert<Real>(argsVect.at(0)), helpers::Converter::convert<Real>(argsVect.at(1)))
        .simplify();
  }
}
