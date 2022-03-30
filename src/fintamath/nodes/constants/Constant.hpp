#pragma once

#include <memory>

#include "fintamath/nodes/Node.hpp"
#include "fintamath/nodes/numbers/Rational.hpp"

namespace fintamath {
  class Constant : public Node {
  public:
    explicit Constant(const std::string &strConst);

    Rational toRational(int64_t precision) const;
    std::string toString() const override;

    std::unique_ptr<Object> clone() const override;

    bool equals(const Object &rhs) const override;

  private:
    std::string name;
  };

  namespace types {
    bool isConstant(const std::string_view &str);
  }
}
