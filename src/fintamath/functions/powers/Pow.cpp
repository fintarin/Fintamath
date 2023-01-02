#include "fintamath/functions/powers/Pow.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr naturalPow(const INumber &lhs, Integer rhs) {
  NumberPtr res = INumber::parse("1");
  NumberPtr tmpLhs = helpers::cast<INumber>(lhs.clone());

  while (rhs != 0) {
    if ((*(rhs.toString().end() - 1) - '0') % 2 == 0) {
      rhs /= 2;
      tmpLhs = (*tmpLhs) * (*tmpLhs);
    } else {
      --rhs;
      res = (*res) * (*tmpLhs);
    }
  }

  return res->simplify();
}

MathObjectPtr Pow::call(const ArgumentsVector &argsVect) const {
  const auto &lhs = argsVect.at(0).get().to<INumber>();
  const auto &rhs = argsVect.at(1).get().to<INumber>();

  if (rhs.is<Integer>() && rhs > Integer(0)) {
    return naturalPow(lhs, rhs.to<Integer>());
  }

  return pow(helpers::Converter::convert<Real>(lhs), helpers::Converter::convert<Real>(rhs)).simplify();
}

}
