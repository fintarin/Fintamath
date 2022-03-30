#ifndef ELEMENTARYFUNCTION_HPP
#define ELEMENTARYFUNCTION_HPP

#include "fintamath/math_objects/nodes/numbers/Rational.hpp"
#include "fintamath/math_objects/relations/Relation.hpp"

#include <string>

class Function : public Relation {
public:
  explicit Function(const std::string &strFunc);

  Rational solve(const Rational &rhs, int64_t precision) const;
  Rational solve(const Rational &lhs, const Rational &rhs, int64_t precision) const;

  std::string toString() const override;

private:
  std::string name;
};

namespace types {
bool isFunction(const std::string &str);
bool isBinaryFunction(const std::string_view &str);
} // namespace types

#endif // ELEMENTARYFUNCTION_HPP
