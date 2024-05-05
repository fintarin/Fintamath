#pragma once

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

Expression operator+(const Expression &lhs, const Expression &rhs);

Expression operator+(const Expression &rhs);

Expression operator-(const Expression &lhs, const Expression &rhs);

Expression operator-(const Expression &rhs);

Expression operator*(const Expression &lhs, const Expression &rhs);

Expression operator/(const Expression &lhs, const Expression &rhs);

Expression mod(const Expression &lhs, const Expression &rhs);

Expression eqv(const Expression &lhs, const Expression &rhs);

Expression neqv(const Expression &lhs, const Expression &rhs);

Expression less(const Expression &lhs, const Expression &rhs);

Expression more(const Expression &lhs, const Expression &rhs);

Expression lessEqv(const Expression &lhs, const Expression &rhs);

Expression moreEqv(const Expression &lhs, const Expression &rhs);

Expression floor(const Expression &rhs);

Expression ceil(const Expression &rhs);

Expression abs(const Expression &rhs);

Expression factorial(const Expression &rhs);

Expression sqrt(const Expression &rhs);

Expression pow(const Expression &lhs, const Expression &rhs);

Expression exp(const Expression &rhs);

Expression log(const Expression &lhs, const Expression &rhs);

Expression ln(const Expression &rhs);

Expression lb(const Expression &rhs);

Expression lg(const Expression &rhs);

Expression sin(const Expression &rhs);

Expression cos(const Expression &rhs);

Expression tan(const Expression &rhs);

Expression cot(const Expression &rhs);

Expression asin(const Expression &rhs);

Expression acos(const Expression &rhs);

Expression atan(const Expression &rhs);

Expression acot(const Expression &rhs);

Expression sinh(const Expression &rhs);

Expression cosh(const Expression &rhs);

Expression tanh(const Expression &rhs);

Expression coth(const Expression &rhs);

Expression asinh(const Expression &rhs);

Expression acosh(const Expression &rhs);

Expression atanh(const Expression &rhs);

Expression acoth(const Expression &rhs);

Expression derivative(const Expression &lhs, const Expression &rhs);

Expression notL(const Expression &rhs);

Expression andL(const Expression &lhs, const Expression &rhs);

Expression orL(const Expression &lhs, const Expression &rhs);

Expression e();

Expression pi();

Expression inf();

Expression negInf();

Expression complexInf();

}
