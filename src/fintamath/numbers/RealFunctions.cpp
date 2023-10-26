#include "fintamath/numbers/RealFunctions.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"

using boost::multiprecision::cpp_dec_float_100;
using boost::multiprecision::cpp_int;

namespace fintamath {

const Real maxTrigArgument = pow(10, FINTAMATH_PRECISION);

Integer floor(const Real &rhs) {
  cpp_dec_float_100 res = boost::multiprecision::floor(rhs.getBackend());
  return res.convert_to<cpp_int>();
}

Integer ceil(const Real &rhs) {
  cpp_dec_float_100 res = boost::multiprecision::ceil(rhs.getBackend());
  return res.convert_to<cpp_int>();
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
  if (lhs == 0 && rhs == 0) {
    throw UndefinedBinaryOperatorException("^", lhs.toString(), rhs.toString());
  }

  cpp_dec_float_100 res = pow(lhs.getBackend(), rhs.getBackend());

  if (!res.backend().isfinite()) {
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
  static const Real zeroValue = 0;

  cpp_dec_float_100 res = sin(rhs.getBackend());

  if (res == zeroValue && abs(rhs) >= maxTrigArgument) {
    throw UndefinedFunctionException("sin", {rhs.toString()});
  }

  return res;
}

Real cos(const Real &rhs) {
  static const Real zeroValue = 1;

  cpp_dec_float_100 res = cos(rhs.getBackend());

  if (res == zeroValue && abs(rhs) >= maxTrigArgument) {
    throw UndefinedFunctionException("cos", {rhs.toString()});
  }

  return res;
}

Real tan(const Real &rhs) {
  static const Real zeroValue = 0;

  cpp_dec_float_100 res = tan(rhs.getBackend());

  if (res == zeroValue && abs(rhs) >= maxTrigArgument) {
    throw UndefinedFunctionException("tan", {rhs.toString()});
  }

  return res;
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
  cpp_dec_float_100 res = asin(rhs.getBackend());

  if (!res.backend().isfinite()) {
    throw UndefinedFunctionException("asin", {rhs.toString()});
  }

  return {res};
}

Real acos(const Real &rhs) {
  cpp_dec_float_100 res = acos(rhs.getBackend());

  if (!res.backend().isfinite()) {
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
  cpp_dec_float_100 res = sinh(rhs.getBackend());

  if (!res.backend().isfinite()) {
    throw UndefinedFunctionException("sinh", {rhs.toString()});
  }

  return res;
}

Real cosh(const Real &rhs) {
  cpp_dec_float_100 res = cosh(rhs.getBackend());

  if (!res.backend().isfinite()) {
    throw UndefinedFunctionException("cosh", {rhs.toString()});
  }

  return res;
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

Real sech(const Real &rhs) {
  return 1 / cosh(rhs);
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
  return boost::math::asinh(rhs.getBackend());
}

Real acosh(const Real &rhs) {
  try {
    return boost::math::acosh(rhs.getBackend());
  }
  catch (const std::domain_error &) {
    throw UndefinedFunctionException("acosh", {rhs.toString()});
  }
}

Real atanh(const Real &rhs) {
  try {
    return boost::math::atanh(rhs.getBackend());
  }
  catch (const std::domain_error &) {
    throw UndefinedFunctionException("atanh", {rhs.toString()});
  }
  catch (const std::overflow_error &) {
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

Real getE() {
  using boost::multiprecision::default_ops::get_constant_e;
  return {cpp_dec_float_100(get_constant_e<cpp_dec_float_100::backend_type>())};
}

Real getPi() {
  using boost::multiprecision::default_ops::get_constant_pi;
  return {cpp_dec_float_100(get_constant_pi<cpp_dec_float_100::backend_type>())};
}

Real tgamma(const Real &rhs) {
  try {
    return boost::math::tgamma(rhs.getBackend());
  }
  catch (const std::domain_error &) {
    throw UndefinedFunctionException("tgamma", {rhs.toString()});
  }
  catch (const std::overflow_error &) {
    throw UndefinedFunctionException("tgamma", {rhs.toString()});
  }
}

}
