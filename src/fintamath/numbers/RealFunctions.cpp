#include "fintamath/numbers/RealFunctions.hpp"

#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/numbers/NumberImpls.hpp"

namespace fintamath {
  Real sqrt(const Real &rhs) {
    if (rhs.round(FINTAMATH_ROUND_PRECISION) < 0) {
      throw UndefinedFunctionException("sqrt", {rhs.toString()});
    }

    return RealImpl(sqrt(rhs.getImpl()->v));
  }

  Real pow(const Real &lhs, const Real &rhs) {
    if (lhs.round(FINTAMATH_ROUND_PRECISION) == 0 && rhs.round(FINTAMATH_ROUND_PRECISION) == 0) {
      throw UndefinedBinaryOpearatorException("^", lhs.toString(), rhs.toString());
    }

    return RealImpl(pow(lhs.getImpl()->v, rhs.getImpl()->v));
  }

  Real exp(const Real &rhs) {
    return RealImpl(exp(rhs.getImpl()->v));
  }

  Real log(const Real &lhs, const Real &rhs) {
    try {
      return ln(rhs) / ln(lhs);
    } catch (const UndefinedException &) {
      throw UndefinedFunctionException("log", {rhs.toString(), lhs.toString()});
    }
  }

  Real ln(const Real &rhs) {
    return RealImpl(log(rhs.getImpl()->v));
  }

  Real lb(const Real &rhs) {
    return RealImpl(log2(rhs.getImpl()->v));
  }

  Real lg(const Real &rhs) {
    return RealImpl(log10(rhs.getImpl()->v));
  }

  Real sin(const Real &rhs) {
    return RealImpl(sin(rhs.getImpl()->v));
  }

  Real cos(const Real &rhs) {
    return RealImpl(cos(rhs.getImpl()->v));
  }

  Real tan(const Real &rhs) {
    try {
      return sin(rhs) / cos(rhs);
    } catch (const std::domain_error &) {
      throw UndefinedFunctionException("tan", {rhs.toString()});
    }
  }

  Real cot(const Real &rhs) {
    try {
      return cos(rhs) / sin(rhs);
    } catch (const std::domain_error &) {
      throw UndefinedFunctionException("cot", {rhs.toString()});
    }
  }

  Real asin(const Real &rhs) {
    try {
      return RealImpl(asin(rhs.getImpl()->v));
    } catch (const std::domain_error &) {
      throw UndefinedFunctionException("asin", {rhs.toString()});
    }
  }

  Real acos(const Real &rhs) {
    try {
      return RealImpl(acos(rhs.getImpl()->v));
    } catch (const std::domain_error &) {
      throw UndefinedFunctionException("acos", {rhs.toString()});
    }
  }

  Real atan(const Real &rhs) {
    return RealImpl(atan(rhs.getImpl()->v));
  }

  Real acot(const Real &rhs) {
    Real res = pi() / 2;

    if (rhs < 0) {
      res = -res;
    }

    return res - atan(rhs);
  }

  Real e() {
    return RealImpl(default_ops::get_constant_e<RealImpl::Backend::backend_type>());
  }

  Real pi() {
    return RealImpl(default_ops::get_constant_pi<RealImpl::Backend::backend_type>());
  }
}
