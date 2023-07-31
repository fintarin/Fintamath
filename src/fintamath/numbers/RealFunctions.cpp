#include "fintamath/numbers/RealFunctions.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"

using namespace boost::multiprecision;

namespace fintamath {

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

  return {res};
}

Real exp(const Real &rhs) {
  return {exp(rhs.getBackend())};
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

  return {log(rhs.getBackend())};
}

Real lb(const Real &rhs) {
  if (rhs <= 0) {
    throw UndefinedFunctionException("lb", {rhs.toString()});
  }

  return {log2(rhs.getBackend())};
}

Real lg(const Real &rhs) {
  if (rhs <= 0) {
    throw UndefinedFunctionException("lg", {rhs.toString()});
  }

  return {log10(rhs.getBackend())};
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

  return {res};
}

Real acos(const Real &rhs) {
  cpp_dec_float_100 res(acos(rhs.getBackend()));

  if (res.backend().isnan()) {
    throw UndefinedFunctionException("acos", {rhs.toString()});
  }

  return {res};
}

Real atan(const Real &rhs) {
  return {atan(rhs.getBackend())};
}

Real acot(const Real &rhs) {
  try {
    return atan(1 / rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("acot", {rhs.toString()});
  }
}

Real sinh(const Real &rhs) {
  return {sinh(rhs.getBackend())};
}

Real cosh(const Real &rhs) {
  return {cosh(rhs.getBackend())};
}

Real tanh(const Real &rhs) {
  return {tanh(rhs.getBackend())};
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
  return boost::math::asinh(rhs.getBackend());
}

Real acosh(const Real &rhs) {
  try {
    return boost::math::acosh(rhs.getBackend());
  }
  catch (const std::domain_error &) {
    throw UndefinedFunctionException("acoth", {rhs.toString()});
  }
}

Real atanh(const Real &rhs) {
  try {
    return boost::math::atanh(rhs.getBackend());
  }
  catch (const std::domain_error &) {
    throw UndefinedFunctionException("acoth", {rhs.toString()});
  }
  catch (const std::overflow_error &) {
    throw UndefinedFunctionException("acoth", {rhs.toString()});
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

Real getE() {
  return {cpp_dec_float_100(default_ops::get_constant_e<cpp_dec_float_100::backend_type>())};
}

Real getPi() {
  return {cpp_dec_float_100(default_ops::get_constant_pi<cpp_dec_float_100::backend_type>())};
}

}
