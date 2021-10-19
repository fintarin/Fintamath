#ifndef NAMESPACEFUNCTIONS_HPP
#define NAMESPACEFUNCTIONS_HPP

#include "numbers/Fraction.hpp"

namespace functions {
Fraction getE(size_t);
Fraction getPi(size_t);

Fraction abs(const Fraction &);

Fraction sqrt(const Fraction &, size_t);
Fraction pow(const Fraction &, const Fraction &, size_t);
Fraction exp(const Fraction &, size_t);

Fraction log(const Fraction &, const Fraction &, size_t);
Fraction ln(const Fraction &, size_t);
Fraction lb(const Fraction &, size_t);
Fraction lg(const Fraction &, size_t);

Fraction sin(const Fraction &, size_t);
Fraction cos(const Fraction &, size_t);
Fraction tan(const Fraction &, size_t);
Fraction cot(const Fraction &, size_t);

Fraction asin(const Fraction &, size_t);
Fraction acos(const Fraction &, size_t);
Fraction atan(const Fraction &, size_t);
Fraction acot(const Fraction &, size_t);

Fraction factorial(const Fraction &);
Fraction doubleFactorial(const Fraction &);
} // namespace functions

#endif // NAMESPACEFUNCTIONS_HPP