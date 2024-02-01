#include "fintamath/functions/logarithms/Log.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Log::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = cast<INumber>(argVect.front().get());
  const auto &rhs = cast<INumber>(argVect.back().get());

  if (lhs == Integer(1)) {
    if (rhs == Integer(1)) {
      return Undefined{}.clone();
    }

    return ComplexInf{}.clone();
  }

  if (lhs == Integer(0)) {
    if (rhs == Integer(0)) {
      return Undefined{}.clone();
    }

    return Integer(0).clone();
  }

  if (rhs == Integer(0)) {
    if (lhs > Integer(1)) {
      return NegInf{}.clone();
    }

    return Inf{}.clone();
  }

  if (rhs == Integer(1)) {
    return Integer(0).clone();
  }

  if (lhs == rhs && lhs.isPrecise()) {
    return Integer(1).clone();
  }

  if (lhs < Integer(0) || rhs < Integer(0)) {
    // TODO: complex log
    return {};
  }

  if (lhs < Integer(1)) {
    auto newLhs = Rational(1) / lhs;

    if (rhs < Integer(1)) {
      auto newRhs = Rational(1) / rhs;
      return multiLogSimplify(*newLhs, *newRhs);
    }

    if (auto res = multiLogSimplify(*newLhs, rhs)) {
      return negExpr(std::move(res))->toMinimalObject();
    }
  }

  if (rhs < Integer(1)) {
    auto newRhs = Rational(1) / rhs;
    if (auto res = multiLogSimplify(lhs, *newRhs)) {
      return negExpr(std::move(res))->toMinimalObject();
    }
  }

  return multiLogSimplify(lhs, rhs);
}

std::unique_ptr<IMathObject> Log::multiLogSimplify(const INumber &lhs, const INumber &rhs) {
  static const auto multiLog = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &, const INumber &)> outMultiPow;

    outMultiPow.add<Integer, Integer>([](const Integer &inLhs, const Integer &inRhs) {
      return logSimplify(inLhs, inRhs);
    });

    outMultiPow.add<Rational, Rational>([](const Rational &inLhs, const Rational &inRhs) {
      return logSimplify(inLhs, inRhs);
    });

    outMultiPow.add<Real, Real>([](const Real &inLhs, const Real &inRhs) {
      return logSimplify(inLhs, inRhs);
    });

    return outMultiPow;
  }();

  if (const auto rhsConv = convert(lhs, rhs)) {
    return multiLog(lhs, *rhsConv);
  }

  const auto lhsConv = convert(rhs, lhs);
  return multiLog(*lhsConv, rhs);
}

std::unique_ptr<IMathObject> Log::logSimplify(const Integer &lhs, const Integer &rhs) {
  return logSimplify(Rational(lhs), Rational(rhs));
}

std::unique_ptr<IMathObject> Log::logSimplify(const Rational &lhs, const Rational &rhs) {
  const bool isResInverted = lhs > rhs;
  const Rational divider = isResInverted ? rhs : lhs;
  Rational remainder = isResInverted ? lhs : rhs;
  Rational res = 0;

  while (remainder > divider) {
    res += 1;
    remainder /= divider;
  }

  if (remainder == divider) {
    res += 1;

    if (isResInverted) {
      return (Rational(1) / res).toMinimalObject();
    }

    return res.toMinimalObject();
  }

  return logSimplify(Real(lhs), Real(rhs));
}

std::unique_ptr<IMathObject> Log::logSimplify(const Real &lhs, const Real &rhs) {
  return log(lhs, rhs).clone();
}

}
