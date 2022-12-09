#include "fintamath/numbers/RealFunctions.hpp"

#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/numbers/NumberImpls.hpp"

namespace fintamath {
  Real sqrt(const Real &rhs) {
    try {
      return RealImpl(sqrt(rhs.getImpl()->v));
    } catch (const std::domain_error &) {
      throw UndefinedFunctionException("sqrt", {rhs.toString()});
    }
  }

  Real pow(const Real &lhs, const Real &rhs) {
    try {
      return RealImpl(pow(lhs.getImpl()->v, rhs.getImpl()->v));
    } catch (const std::domain_error &) {
      throw UndefinedBinaryOpearatorException("^", lhs.toString(), rhs.toString());
    }
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
    try {
      return RealImpl(log(rhs.getImpl()->v));
    } catch (const std::domain_error &) {
      throw UndefinedFunctionException("ln", {rhs.toString()});
    }
  }

  Real lb(const Real &rhs) {
    try {
      return RealImpl(log2(rhs.getImpl()->v));
    } catch (const std::domain_error &) {
      throw UndefinedFunctionException("lb", {rhs.toString()});
    }
  }

  Real lg(const Real &rhs) {
    try {
      return RealImpl(log10(rhs.getImpl()->v));
    } catch (const std::domain_error &) {
      throw UndefinedFunctionException("lg", {rhs.toString()});
    }
  }

  Real sin(const Real &rhs) {
    return RealImpl(sin(rhs.getImpl()->v));
  }

  Real cos(const Real &rhs) {
    return RealImpl(cos(rhs.getImpl()->v));
  }

  Real tan(const Real &rhs) {
    try {
      return RealImpl(tan(rhs.getImpl()->v));
    } catch (const std::domain_error &) {
      throw UndefinedFunctionException("tan", {rhs.toString()});
    }
  }

  Real cot(const Real &rhs) {
    try {
      return RealImpl(1 / tan(rhs.getImpl()->v));
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
