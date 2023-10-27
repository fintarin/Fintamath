#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

std::unique_ptr<IArithmetic> Integer::multiplyAbstract(const IArithmetic &rhs) const {
  if (*this == 0) {
    return cast<IArithmetic>(Integer(0).clone());
  }

  return IIntegerCRTP<Integer>::multiplyAbstract(rhs);
}

std::unique_ptr<IArithmetic> Integer::divideAbstract(const IArithmetic &rhs) const {
  if (*this == 0 && rhs != Integer(0) && rhs != Real(0)) {
    return cast<IArithmetic>(Integer(0).clone());
  }

  if (const auto *intRhs = cast<Integer>(&rhs)) {
    if (*this % *intRhs != 0) {
      return cast<IArithmetic>(Rational(*this, *intRhs).clone());
    }
  }

  return IIntegerCRTP<Integer>::divideAbstract(rhs);
}

//-------------------------------------------------------------------------------------//

std::unique_ptr<IArithmetic> Rational::multiplyAbstract(const IArithmetic &rhs) const {
  if (*this == 0) {
    return cast<IArithmetic>(Integer(0).clone());
  }

  return INumberCRTP<Rational>::multiplyAbstract(rhs);
}

std::unique_ptr<IArithmetic> Rational::divideAbstract(const IArithmetic &rhs) const {
  if (*this == 0 && rhs != Integer(0) && rhs != Real(0)) {
    return cast<IArithmetic>(Integer(0).clone());
  }

  return INumberCRTP<Rational>::divideAbstract(rhs);
}

//-------------------------------------------------------------------------------------//

bool Real::equalsAbstract(const IMathObject &rhs) const {
  if (const auto *rhsNum = cast<INumber>(&rhs); rhsNum && rhsNum->isPrecise()) {
    return false;
  }

  return INumberCRTP<Real>::equalsAbstract(rhs);
}

std::strong_ordering Real::compareAbstract(const IComparable &rhs) const {
  auto res = INumberCRTP<Real>::compareAbstract(rhs);

  if (res == std::strong_ordering::equal) {
    if (const auto *rhsNum = cast<INumber>(&rhs); rhsNum && rhsNum->isPrecise()) {
      return sign() != 0 ? sign() <=> 0 : std::strong_ordering::greater;
    }
  }

  return res;
}

std::unique_ptr<IArithmetic> Real::multiplyAbstract(const IArithmetic &rhs) const {
  if (const auto *rhsNum = cast<INumber>(&rhs); rhsNum && *rhsNum == Integer(0)) {
    return cast<IArithmetic>(Integer(0).clone());
  }

  return INumberCRTP<Real>::multiplyAbstract(rhs);
}

}
