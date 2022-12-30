#include "fintamath/functions/powers/Exp.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  std::string Exp::toString() const {
    return "exp";
  }

  Expression Exp::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return *exp(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
  }
}
