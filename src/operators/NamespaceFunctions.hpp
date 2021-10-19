#ifndef NAMESPACEFUNCTIONS_HPP
#define NAMESPACEFUNCTIONS_HPP

#include "../numbers/Fraction.hpp"

namespace functions {
Fraction getE(const size_t);
Fraction getPi(const size_t);

Fraction abs(const Fraction &);

Fraction sqrt(const Fraction &, const size_t);
Fraction pow(const Fraction &, const Fraction &, const size_t);
Fraction exp(const Fraction &, const size_t);

Fraction log(const Fraction &, const Fraction &, const size_t);
Fraction ln(const Fraction &, const size_t);
Fraction lb(const Fraction &, const size_t);
Fraction lg(const Fraction &, const size_t);

Fraction sin(const Fraction &, const size_t);
Fraction cos(const Fraction &, const size_t);
Fraction tan(const Fraction &, const size_t);
Fraction cot(const Fraction &, const size_t);

Fraction asin(const Fraction &, const size_t);
Fraction acos(const Fraction &, const size_t);
Fraction atan(const Fraction &, const size_t);
Fraction acot(const Fraction &, const size_t);

Fraction factorial(const Fraction &);
Fraction doubleFactorial(const Fraction &);
} // namespace functions

#endif // NAMESPACEFUNCTIONS_HPP