#ifndef NAMESPACEFUNCTIONS_HPP
#define NAMESPACEFUNCTIONS_HPP

#include "numbers/Rational.hpp"

namespace functions {
Rational getE(size_t);
Rational getPi(size_t);

Rational abs(const Rational &);

Rational sqrt(const Rational &, size_t);
Rational pow(const Rational &, const Rational &, size_t);
Rational exp(const Rational &, size_t);

Rational log(const Rational &, const Rational &, size_t);
Rational ln(const Rational &, size_t);
Rational lb(const Rational &, size_t);
Rational lg(const Rational &, size_t);

Rational sin(const Rational &, size_t);
Rational cos(const Rational &, size_t);
Rational tan(const Rational &, size_t);
Rational cot(const Rational &, size_t);

Rational asin(const Rational &, size_t);
Rational acos(const Rational &, size_t);
Rational atan(const Rational &, size_t);
Rational acot(const Rational &, size_t);

Rational factorial(const Rational &);
Rational doubleFactorial(const Rational &);
} // namespace functions

#endif // NAMESPACEFUNCTIONS_HPP