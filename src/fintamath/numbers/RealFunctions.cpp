#include "fintamath/numbers/RealFunctions.hpp"

#include <stdexcept>

#include <boost/math/policies/error_handling.hpp>
#include <boost/multiprecision/detail/default_ops.hpp>
#include <boost/multiprecision/mpfr.hpp>

#include "fintamath/core/Cache.hpp"
#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

using namespace detail;

bool isOverflow(const Real &rhs) {
  static Cache<unsigned, Real::Backend> cache([](const unsigned precision) {
    static const Real::Backend powBase = 10;
    return pow(powBase, precision);
  });

  return abs(rhs) > cache[Real::getPrecision()];
}

bool isUnderflow(const Real &rhs) {
  static Cache<unsigned, Real::Backend> cache([](const unsigned precision) {
    static const Real::Backend powBase = 10;
    return 1 / pow(powBase, precision);
  });

  return rhs != 0 && abs(rhs) < cache[Real::getPrecision()];
}

bool isLogUnderflow(const Real &rhs) {
  static Cache<unsigned, Real::Backend> cache([](const unsigned precision) {
    return 1 / pow(precision, getE().getBackend());
  });

  return rhs != 0 && abs(rhs) < cache[Real::getPrecision()];
}

const Real &trigResultChecked(const Real &rhs) {
  if (isUnderflow(rhs) || isOverflow(rhs)) {
    throw UndefinedException("");
  }

  return rhs;
}

const Real &hyperbResultChecked(const Real &rhs) {
  if (isUnderflow(rhs)) {
    throw UndefinedException("");
  }

  return rhs;
}

const Real &tgammaResultChecked(const Real &rhs) {
  if (rhs == 0) {
    throw UndefinedException("");
  }

  return rhs;
}

Integer floor(const Real &rhs) {
  if (isOverflow(rhs)) {
    throw UndefinedFunctionException("floor", {rhs.toString()});
  }

  const Real::Backend res = boost::multiprecision::floor(rhs.getBackend());
  return res.convert_to<Integer::Backend>();
}

Integer ceil(const Real &rhs) {
  if (isOverflow(rhs)) {
    throw UndefinedFunctionException("ceil", {rhs.toString()});
  }

  const Real::Backend res = boost::multiprecision::ceil(rhs.getBackend());
  return res.convert_to<Integer::Backend>();
}

Real abs(const Real &rhs) {
  return rhs < 0 ? -rhs : rhs;
}

Real sqrt(const Real &rhs) {
  if (rhs < 0) {
    throw UndefinedFunctionException("sqrt", {rhs.toString()});
  }

  return {sqrt(rhs.getBackend())};
}

Real pow(const Real &lhs, const Real &rhs) {
  if (abs(lhs) == 0 && abs(rhs) == 0) {
    throw UndefinedBinaryOperatorException("^", lhs.toString(), rhs.toString());
  }

  try {
    if (lhs == Real("-0")) {
      // Use (-1)^rhs to validate (-0)^rhs
      Real(pow(-1, rhs.getBackend()));
    }

    return {pow(lhs.getBackend(), rhs.getBackend())};
  }
  catch (const UndefinedException &) {
    throw UndefinedBinaryOperatorException("^", lhs.toString(), rhs.toString());
  }
}

Real exp(const Real &rhs) {
  try {
    return {exp(rhs.getBackend())};
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("exp", {rhs.toString()});
  }
}

Real log(const Real &lhs, const Real &rhs) {
  try {
    return ln(rhs) / ln(lhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("log", {lhs.toString(), rhs.toString()});
  }
}

Real ln(const Real &rhs) {
  if (rhs <= 0) {
    throw UndefinedFunctionException("ln", {rhs.toString()});
  }

  Real res = {log(rhs.getBackend())};

  if (isLogUnderflow(res)) {
    throw UndefinedFunctionException("ln", {rhs.toString()});
  }

  return res;
}

Real lb(const Real &rhs) {
  try {
    static const Real logBase = 2;
    return log(logBase, rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("lb", {rhs.toString()});
  }
}

Real lg(const Real &rhs) {
  try {
    static const Real logBase = 10;
    return log(logBase, rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("lg", {rhs.toString()});
  }
}

Real sin(const Real &rhs) {
  if (isOverflow(rhs)) {
    throw UndefinedFunctionException("sin", {rhs.toString()});
  }

  try {
    return trigResultChecked({sin(rhs.getBackend())});
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("sin", {rhs.toString()});
  }
}

Real cos(const Real &rhs) {
  if (isOverflow(rhs)) {
    throw UndefinedFunctionException("cos", {rhs.toString()});
  }

  try {
    return trigResultChecked({cos(rhs.getBackend())});
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("cos", {rhs.toString()});
  }
}

Real tan(const Real &rhs) {
  if (isOverflow(rhs)) {
    throw UndefinedFunctionException("tan", {rhs.toString()});
  }

  try {
    return trigResultChecked({tan(rhs.getBackend())});
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("tan", {rhs.toString()});
  }
}

Real cot(const Real &rhs) {
  try {
    return 1 / tan(rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("cot", {rhs.toString()});
  }
}

Real sec(const Real &rhs) {
  try {
    return 1 / cos(rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("sec", {rhs.toString()});
  }
}

Real csc(const Real &rhs) {
  try {
    return 1 / sin(rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("csc", {rhs.toString()});
  }
}

Real asin(const Real &rhs) {
  try {
    return trigResultChecked({asin(rhs.getBackend())});
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("asin", {rhs.toString()});
  }
}

Real acos(const Real &rhs) {
  try {
    return trigResultChecked({acos(rhs.getBackend())});
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("acos", {rhs.toString()});
  }
}

Real atan(const Real &rhs) {
  try {
    return trigResultChecked({atan(rhs.getBackend())});
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("atan", {rhs.toString()});
  }
}

Real acot(const Real &rhs) {
  try {
    return atan(1 / rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("acot", {rhs.toString()});
  }
}

Real asec(const Real &rhs) {
  try {
    return acos(1 / rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("asec", {rhs.toString()});
  }
}

Real acsc(const Real &rhs) {
  try {
    return asin(1 / rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("acsc", {rhs.toString()});
  }
}

Real sinh(const Real &rhs) {
  try {
    return hyperbResultChecked({sinh(rhs.getBackend())});
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("sinh", {rhs.toString()});
  }
}

Real cosh(const Real &rhs) {
  try {
    return hyperbResultChecked({cosh(rhs.getBackend())});
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("cosh", {rhs.toString()});
  }
}

Real tanh(const Real &rhs) {
  try {
    return hyperbResultChecked({tanh(rhs.getBackend())});
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("tanh", {rhs.toString()});
  }
}

Real coth(const Real &rhs) {
  try {
    return 1 / tanh(rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("coth", {rhs.toString()});
  }
}

Real sech(const Real &rhs) {
  try {
    return 1 / cosh(rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("sech", {rhs.toString()});
  }
}

Real csch(const Real &rhs) {
  try {
    return 1 / sinh(rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("csch", {rhs.toString()});
  }
}

Real asinh(const Real &rhs) {
  try {
    return hyperbResultChecked(boost::math::asinh(rhs.getBackend()));
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("asinh", {rhs.toString()});
  }
}

Real acosh(const Real &rhs) {
  try {
    return boost::math::acosh(rhs.getBackend());
  }
  catch (const boost::math::evaluation_error &) {
    throw UndefinedFunctionException("acosh", {rhs.toString()});
  }
}

Real atanh(const Real &rhs) {
  try {
    return hyperbResultChecked(boost::math::atanh(rhs.getBackend()));
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("atanh", {rhs.toString()});
  }
  catch (const std::overflow_error &) {
    throw UndefinedFunctionException("atanh", {rhs.toString()});
  }
  catch (const boost::math::evaluation_error &) {
    throw UndefinedFunctionException("atanh", {rhs.toString()});
  }
}

Real acoth(const Real &rhs) {
  try {
    return atanh(1 / rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("acoth", {rhs.toString()});
  }
}

Real asech(const Real &rhs) {
  try {
    return acosh(1 / rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("asech", {rhs.toString()});
  }
}

Real acsch(const Real &rhs) {
  try {
    return asinh(1 / rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("acsch", {rhs.toString()});
  }
}

Real tgamma(const Real &rhs) {
  try {
    return tgammaResultChecked(boost::math::tgamma(rhs.getBackend()));
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("tgamma", {rhs.toString()});
  }
  catch (const std::overflow_error &) {
    throw UndefinedFunctionException("tgamma", {rhs.toString()});
  }
  catch (const boost::math::evaluation_error &) {
    throw UndefinedFunctionException("tgamma", {rhs.toString()});
  }
}

const Real &getE() {
  static Cache<unsigned, Real> cache([](const unsigned precision) {
    Real::Backend::backend_type res;
    boost::multiprecision::default_ops::calc_e(res, precision);
    return Real(res);
  });

  return cache[Real::getCalculationPrecision()];
}

const Real &getPi() {
  static Cache<unsigned, Real> cache([](const unsigned precision) {
    Real::Backend::backend_type res;
    boost::multiprecision::default_ops::calc_pi(res, precision);
    return Real(res);
  });

  return cache[Real::getCalculationPrecision()];
}

}
