#include "fintamath/functions/Operator.hpp"

namespace fintamath {
  class Mul : public OperatorImpl<Mul> {
  public:
    Mul() = default;

    std::string toString() const override;

    int getPriority() const override;

    MathObjectPtr operator()(const MathObject &lhs, const MathObject &rhs) const;

  protected:
    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;

  private:
    int priority = 2;
  };
}
