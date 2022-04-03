#pragma once

#include <memory>
#include <vector>

#include "fintamath/expressions/Expression.hpp"

namespace fintamath {
  class Variable : public MathObject<Variable> {
  public:
    explicit Variable(const std::string &str);

    std::string toString() const override;

    std::unique_ptr<MathObjectBase> clone() const override;

    bool equals(const Variable &rhs) const override;

  private:
    std::string name;
  };

  namespace types {
    bool isVariable(const std::string &str);
  }
}