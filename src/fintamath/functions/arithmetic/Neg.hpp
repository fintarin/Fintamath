#include "fintamath/functions/Operator.hpp"

namespace fintamath {
  class Neg : public OperatorImpl<Neg> {
  public:
    Neg() = default;

    std::string toString() const override;

    int getPriority() const override;

    MathObjectPtr operator()(const MathObject &rhs) const;

  protected:
    bool equals(const Neg &rhs) const override;

    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;

  private:
    int priority = 1;
  };
}