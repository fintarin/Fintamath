#include "fintamath/numbers/RealFunctions.hpp"

#include "fintamath/exceptions/UndefinedBinaryOperatorException.hpp"
#include "fintamath/exceptions/UndefinedFunctionException.hpp"

using namespace boost::multiprecision;

namespace fintamath {

Real abs(const Real &rhs) {
  return rhs < 0 ? -rhs : rhs;
}

Real sqrt(const Real &rhs) {
  if (rhs < 0) {
    throw UndefinedFunctionException("sqrt", {rhs.toString()});
  }

  return Real(sqrt(rhs.getBackend()));
}

Real pow(const Real &lhs, const Real &rhs) {
  if (lhs.isNearZero() && rhs.isNearZero()) {
    throw UndefinedBinaryOperatorException("^", lhs.toString(), rhs.toString());
  }
  if (lhs < 0 && !is<Integer>(rhs.toMinimalObject())) { // TODO: do not use toMinimalObject
    throw UndefinedBinaryOperatorException("^", lhs.toString(), rhs.toString());
  }

  cpp_dec_float_100 res(pow(lhs.getBackend(), rhs.getBackend()));

  if (res.backend().isinf() || res.backend().isnan()) {
    throw UndefinedBinaryOperatorException("^", lhs.toString(), rhs.toString());
  }

  return Real(res);
}

Real exp(const Real &rhs) {
  return Real(exp(rhs.getBackend()));
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

  return Real(log(rhs.getBackend()));
}

Real lb(const Real &rhs) {
  if (rhs <= 0) {
    throw UndefinedFunctionException("lb", {rhs.toString()});
  }

  return Real(log2(rhs.getBackend()));
}

Real lg(const Real &rhs) {
  if (rhs <= 0) {
    throw UndefinedFunctionException("lg", {rhs.toString()});
  }

  return Real(log10(rhs.getBackend()));
}

Real sin(const Real &rhs) {
  Real res(sin(rhs.getBackend()));

  if (res.isNearZero()) {
    return 0;
  }

  return res;
}

Real cos(const Real &rhs) {
  Real res(cos(rhs.getBackend()));

  if (res.isNearZero()) {
    return 0;
  }

  return res;
}

Real tan(const Real &rhs) {
  try {
    return sin(rhs) / cos(rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("tan", {rhs.toString()});
  }
}

Real cot(const Real &rhs) {
  try {
    return cos(rhs) / sin(rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("cot", {rhs.toString()});
  }
}

Real asin(const Real &rhs) {
  cpp_dec_float_100 res = asin(rhs.getBackend());

  if (res.backend().isnan()) {
    throw UndefinedFunctionException("asin", {rhs.toString()});
  }

  return Real(res);
}

Real acos(const Real &rhs) {
  cpp_dec_float_100 res(acos(rhs.getBackend()));

  if (res.backend().isnan()) {
    throw UndefinedFunctionException("acos", {rhs.toString()});
  }

  return Real(res);
}

Real atan(const Real &rhs) {
  return Real(atan(rhs.getBackend()));
}

Real acot(const Real &rhs) {
  Real res = getPi() / 2;

  if (rhs < 0) {
    res = -res;
  }

  return res - atan(rhs);
}

Real sinh(const Real &rhs) {
  return Real(sinh(rhs.getBackend()));
}

Real cosh(const Real &rhs) {
  return Real(cosh(rhs.getBackend()));
}

Real tanh(const Real &rhs) {
  return Real(tanh(rhs.getBackend()));
}

Real coth(const Real &rhs) {
  try {
    return 1 / tanh(rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("coth", {rhs.toString()});
  }
}

Real asinh(const Real &rhs) {
  return ln(sqrt(rhs * rhs + 1) + rhs);
}

Real acosh(const Real &rhs) {
  try {
    return ln(rhs + sqrt(rhs - 1) * sqrt(rhs + 1));
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("acoth", {rhs.toString()});
  }
}

Real atanh(const Real &rhs) {
  try {
    return (ln(1 + rhs) - ln(1 - rhs)) / 2;
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("acoth", {rhs.toString()});
  }
}

Real acoth(const Real &rhs) {
  try {
    return (ln(1 + 1 / rhs) - ln(1 - 1 / rhs)) / 2;
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("acoth", {rhs.toString()});
  }
}

Real getE() {
  return Real(cpp_dec_float_100(default_ops::get_constant_e<cpp_dec_float_100::backend_type>()));
}

Real getPi() {
  return Real(cpp_dec_float_100(default_ops::get_constant_pi<cpp_dec_float_100::backend_type>()));
}

}
