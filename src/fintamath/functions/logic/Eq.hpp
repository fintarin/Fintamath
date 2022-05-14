#pragma once

#include "fintamath/functions/Operator.hpp"

namespace fintamath {
  class Eq : public OperatorImpl<Eq> {
  public:
    Eq() = default;

    int getPriority() const override;

    std::string toString() const override;

    MathObjectPtr operator()(const MathObject &lhs, const MathObject &rhs) const;

  protected:
    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;

  private:
    static constexpr int priority = 0;
  };
}
