#pragma once

#include "fintamath/nodes/numbers/Rational.hpp"
#include "fintamath/relations/Relation.hpp"

#include <string>

namespace fintamath {
  class Function : public Relation {
  public:
    explicit Function(const std::string &strFunc);

    Rational solve(const Rational &rhs, int64_t precision) const;
    Rational solve(const Rational &lhs, const Rational &rhs, int64_t precision) const;

    std::string toString() const override;
    std::unique_ptr<Object> clone() const override;
    bool equals(const Object &rhs) const override;

  private:
    std::string name;
  };

  namespace types {
    bool isFunction(const std::string &str);
    bool isBinaryFunction(const std::string_view &str);
  }
}
