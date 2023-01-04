#pragma once

#include <memory>
#include <vector>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/NumberFunctions.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

template <typename... Args>
Expression add(const Args &...args) {
  return (Expression(args) + ...);
}

template <typename... Args>
Expression mul(const Args &...args) {
  return (Expression(args) * ...);
}

inline Expression sub(const Expression &lhs, const Expression &rhs) {
  return lhs - rhs;
}

inline Expression div(const Expression &lhs, const Expression &rhs) {
  return lhs / rhs;
}

Expression eqv(const Expression &lhs, const Expression &rhs);

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

Expression e();

Expression pi();

}
