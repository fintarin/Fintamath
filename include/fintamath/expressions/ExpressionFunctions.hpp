#pragma once

#include "fintamath/expressions/Expression.hpp"

namespace fintamath {

Expression simplify(const Expression &rhs);

Expression solve(const Expression &rhs);

Expression approximate(const Expression &rhs);

Expression pow(const Expression &lhs, const Expression &rhs);

Expression sin(const Expression &rhs);

}
