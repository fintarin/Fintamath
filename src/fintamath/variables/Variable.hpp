#pragma once

#include <memory>
#include <vector>

#include "fintamath/expressions/Expression.hpp"

namespace fintamath {
  class Variable : public MathObject {
  public:
    explicit Variable(const std::string &strVariable);
    std::string toString() const override;

    std::unique_ptr<MathObject> clone() const override;

    bool equals(const MathObject &rhs) const override;

  private:
    std::string name;
  };

  namespace types {
    bool isVariable(const std::string &str);
  }
}