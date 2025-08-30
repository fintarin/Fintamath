#include "fintamath/numbers/RealFunctions.hpp"

#include <stdexcept>

#include <fmt/core.h>

#include <boost/math/policies/error_handling.hpp>
#include <boost/multiprecision/detail/default_ops.hpp>
#include <boost/multiprecision/mpfr.hpp>

#include "fintamath/core/Cache.hpp"
#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

using namespace detail;

namespace {

constexpr std::string_view backendIsInfException = "Undefined backend inf";
constexpr std::string_view backendIsNegInfException = "Undefined backend -inf";
constexpr std::string_view backendIsNanException = "Undefined backend nan";

bool isOverflow(const Real &rhs) {
  static Cache<unsigned, Real::Backend> cache([](const unsigned precision) {
    static const Real::Backend powBase = 10;
    return pow(powBase, precision);
  });

  return abs(rhs) > cache[Real::getPrecisionStatic()];
}

bool isUnderflow(const Real &rhs) {
  static Cache<unsigned, Real::Backend> cache([](const unsigned precision) {
    static const Real::Backend powBase = 10;
    return 1 / pow(powBase, precision);
  });

  return !rhs.isZero() && abs(rhs) < cache[Real::getPrecisionStatic()];
}

bool isLogUnderflow(const Real &rhs) {
  static Cache<unsigned, Real::Backend> cache([](const unsigned precision) {
    return 1 / pow(precision, getE().getBackend());
  });

  return !rhs.isZero() && abs(rhs) < cache[Real::getPrecisionStatic()];
}

std::string getExceptionMessage(const std::string_view message) {
  if (message == backendIsInfException || message == backendIsNegInfException) {
    return "result overflow";
  }

  if (message == backendIsNanException) {
    return "argument out of range";
  }

  return std::string(message);
}

const Real &trigResultChecked(const Real &rhs) {
  if (isUnderflow(rhs)) {
    throw UndefinedException("result underflow");
  }

  if (isOverflow(rhs)) {
    throw UndefinedException("result overflow");
  }

  return rhs;
}

const Real &hyperbResultChecked(const Real &rhs) {
  if (isUnderflow(rhs)) {
    throw UndefinedException("result underflow");
  }

  return rhs;
}

const Real &tgammaResultChecked(const Real &rhs) {
  if (rhs.isZero()) {
    throw UndefinedException("result overflow");
  }

  return rhs;
}

}

Integer floor(const Real &rhs) {
  try {
    if (isOverflow(rhs)) {
      throw UndefinedException("argument overflow");
    }

    if (rhs.isNegZero()) {
      return -1;
    }

    const Real::Backend res = boost::multiprecision::floor(rhs.getBackend());
    return res.convert_to<Integer::Backend>();
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "floor({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Integer ceil(const Real &rhs) {
  try {
    if (isOverflow(rhs)) {
      throw UndefinedException("argument overflow");
    }

    const Real::Backend res = boost::multiprecision::ceil(rhs.getBackend());
    return res.convert_to<Integer::Backend>();
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "ceil({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real abs(const Real &rhs) {
  return rhs < 0 ? -rhs : rhs;
}

Real sqrt(const Real &rhs) {
  try {
    if (rhs < 0) {
      throw UndefinedException("expected argument >= 0");
    }

    return {sqrt(rhs.getBackend())};
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "sqrt({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real pow(const Real &lhs, const Real &rhs) {
  try {
    if (lhs.isZero() && rhs.isZero()) {
      throw UndefinedException("zero to the power of zero");
    }

    if (lhs.isNegZero()) {
      return Real(0) * pow(Real(-1), rhs);
    }

    return {pow(lhs.getBackend(), rhs.getBackend())};
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "pow({}, {}) is undefined ({})",
      lhs.toString(),
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real exp(const Real &rhs) {
  try {
    return {exp(rhs.getBackend())};
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "exp({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real log(const Real &lhs, const Real &rhs) {
  try {
    Real divLhs = ln(rhs);
    Real divRhs = ln(lhs);
    return divLhs / divRhs;
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "log({}, {}) is undefined ({})",
      lhs.toString(),
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real ln(const Real &rhs) {
  try {
    if (rhs <= 0) {
      throw UndefinedException("expected argument > 0");
    }

    Real res = {log(rhs.getBackend())};

    if (isLogUnderflow(res)) {
      throw UndefinedException("underflow");
    }

    return res;
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "ln({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real lb(const Real &rhs) {
  try {
    static const Real divisor = ln(2);
    return ln(rhs) / divisor;
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "lb({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real lg(const Real &rhs) {
  try {
    static const Real divisor = ln(10);
    return ln(rhs) / divisor;
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "lg({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real sin(const Real &rhs) {
  try {
    if (isOverflow(rhs)) {
      throw UndefinedException("argument overflow");
    }

    return trigResultChecked({sin(rhs.getBackend())});
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "sin({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real cos(const Real &rhs) {
  try {
    if (isOverflow(rhs)) {
      throw UndefinedException("argument overflow");
    }

    return trigResultChecked({cos(rhs.getBackend())});
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "cos({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real tan(const Real &rhs) {
  try {
    if (isOverflow(rhs)) {
      throw UndefinedException("argument overflow");
    }

    return trigResultChecked({tan(rhs.getBackend())});
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "tan({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real cot(const Real &rhs) {
  try {
    return 1 / tan(rhs);
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "cot({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real sec(const Real &rhs) {
  try {
    return 1 / cos(rhs);
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "sec({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real csc(const Real &rhs) {
  try {
    return 1 / sin(rhs);
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "csc({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real asin(const Real &rhs) {
  try {
    return trigResultChecked({asin(rhs.getBackend())});
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "asin({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real acos(const Real &rhs) {
  try {
    return trigResultChecked({acos(rhs.getBackend())});
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "acos({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real atan(const Real &rhs) {
  try {
    return trigResultChecked({atan(rhs.getBackend())});
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "atan({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real acot(const Real &rhs) {
  try {
    return atan(1 / rhs);
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "acot({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real asec(const Real &rhs) {
  try {
    return acos(1 / rhs);
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "asec({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real acsc(const Real &rhs) {
  try {
    return asin(1 / rhs);
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "acsc({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real sinh(const Real &rhs) {
  try {
    return hyperbResultChecked({sinh(rhs.getBackend())});
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "sinh({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real cosh(const Real &rhs) {
  try {
    return hyperbResultChecked({cosh(rhs.getBackend())});
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "cosh({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real tanh(const Real &rhs) {
  try {
    return hyperbResultChecked({tanh(rhs.getBackend())});
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "tanh({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real coth(const Real &rhs) {
  try {
    return 1 / tanh(rhs);
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "coth({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real sech(const Real &rhs) {
  try {
    return 1 / cosh(rhs);
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "sech({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real csch(const Real &rhs) {
  try {
    return 1 / sinh(rhs);
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "csch({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real asinh(const Real &rhs) {
  try {
    return hyperbResultChecked(boost::math::asinh(rhs.getBackend()));
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "asinh({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real acosh(const Real &rhs) {
  try {
    try {
      return boost::math::acosh(rhs.getBackend());
    }
    catch (const boost::math::evaluation_error &) {
      throw UndefinedException("argument out of range");
    }
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "acosh({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real atanh(const Real &rhs) {
  try {
    try {
      return hyperbResultChecked(boost::math::atanh(rhs.getBackend()));
    }
    catch (const std::overflow_error &) {
      throw UndefinedException("result overflow");
    }
    catch (const boost::math::evaluation_error &) {
      throw UndefinedException("argument out of range");
    }
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "atanh({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real acoth(const Real &rhs) {
  try {
    return atanh(1 / rhs);
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "acoth({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real asech(const Real &rhs) {
  try {
    return acosh(1 / rhs);
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "asech({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real acsch(const Real &rhs) {
  try {
    return asinh(1 / rhs);
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "acsch({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

Real tgamma(const Real &rhs) {
  try {
    try {
      return tgammaResultChecked(boost::math::tgamma(rhs.getBackend()));
    }
    catch (const std::overflow_error &) {
      throw UndefinedException("result overflow");
    }
    catch (const boost::math::evaluation_error &) {
      throw UndefinedException("argument out of range");
    }
  }
  catch (const UndefinedException &exc) {
    throw UndefinedException(fmt::format(
      "tgamma({}) is undefined ({})",
      rhs.toString(),
      getExceptionMessage(exc.what())
    ));
  }
}

const Real &getE() {
  static Cache<unsigned, Real> cache([](const unsigned precision) {
    Real::Backend::backend_type res;
    boost::multiprecision::default_ops::calc_e(res, precision);
    return Real(res);
  });

  return cache[Real::getCalculationPrecisionStatic()];
}

const Real &getPi() {
  static Cache<unsigned, Real> cache([](const unsigned precision) {
    Real::Backend::backend_type res;
    boost::multiprecision::default_ops::calc_pi(res, precision);
    return Real(res);
  });

  return cache[Real::getCalculationPrecisionStatic()];
}

}
