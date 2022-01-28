#ifndef ELEMENTARYFUNCTION_HPP
#define ELEMENTARYFUNCTION_HPP

#include "fintamath/math_objects/nodes/terms/numbers/Rational.hpp"
#include "fintamath/math_objects/relations/functions/Function.hpp"

#include <cstdint>
#include <string>

class ElementaryFunction : public Function {
public:
  explicit ElementaryFunction(const std::string &strFunc);

  Rational solve(const Rational &rhs, int64_t precision) const;
  Rational solve(const Rational &lhs, const Rational &rhs, int64_t precision) const;

  std::string getTypeName() const override;
  std::string toString() const override;

private:
  std::string name;
};

namespace types {
bool isFunction(const std::string &str);
bool isBinaryFunction(const std::string &str);
} // namespace types

#endif // ELEMENTARYFUNCTION_HPP
