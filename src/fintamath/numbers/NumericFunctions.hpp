#pragma once

#include "fintamath/numbers/Rational.hpp"

namespace fintamath {
  Rational getE(int64_t precision);

  Rational getPi(int64_t precision);

  Rational abs(const Rational &rhs);

  Rational sqrt(const Rational &rhs, int64_t precision);

  Rational pow(const Rational &lhs, const Rational &rhs, int64_t precision);

  Rational exp(const Rational &rhs, int64_t precision);

  Rational log(const Rational &lhs, const Rational &rhs, int64_t precision);

  Rational ln(const Rational &rhs, int64_t precision);

  Rational lb(const Rational &rhs, int64_t precision);

  Rational lg(const Rational &rhs, int64_t precision);

  Rational sin(const Rational &rhs, int64_t precision);

  Rational cos(const Rational &rhs, int64_t precision);

  Rational tan(const Rational &rhs, int64_t precision);

  Rational cot(const Rational &rhs, int64_t precision);

  Rational asin(const Rational &rhs, int64_t precision);

  Rational acos(const Rational &rhs, int64_t precision);

  Rational atan(const Rational &rhs, int64_t precision);

  Rational acot(const Rational &rhs, int64_t precision);

  Rational factorial(const Rational &rhs);

  Rational doubleFactorial(const Rational &rhs);
}
