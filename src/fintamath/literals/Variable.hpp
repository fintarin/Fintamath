#pragma once

#include <memory>
#include <vector>

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  class Variable : public MathObjectImpl<Variable> {
  public:
    explicit Variable(const std::string &str);

    std::string toString() const override;

    bool equals(const Variable &rhs) const override;

  private:
    void parse(const std::string &str);

    std::string name;
  };
}