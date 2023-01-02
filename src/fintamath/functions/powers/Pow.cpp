#include "fintamath/functions/powers/Pow.hpp"

#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
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
  auto lhs = helpers::cast<INumber>(argsVect.at(0).get().simplify());
  auto rhs = helpers::cast<INumber>(argsVect.at(1).get().simplify());

  if (rhs->is<Integer>() && lhs->isPrecise()) {
    Integer intRhs = rhs->to<Integer>();

    if (intRhs == 0 && lhs->to<INumber>() == Integer(0)) {
      throw UndefinedBinaryOpearatorException("^", lhs->toString(), rhs->toString());
    }

    if (intRhs < 0) {
      return naturalPow(*(Integer(1) / *lhs), -intRhs);
    }

    return naturalPow(*lhs, intRhs);
  }

  return pow(helpers::Converter::convert<Real>(*lhs), helpers::Converter::convert<Real>(*rhs)).simplify();
}

}
