#include "fintamath/operators/Operator.hpp"

namespace fintamath {
  class Mul: public OperatorImpl<Mul> {
  public:

    explicit Mul() = default;

    std::string toString() const override;

    int getPriority() const override;

    MathObjectPtr operator()(const MathObject &lhs, const MathObject &rhs) const;

  protected:
    bool equals(const Mul& rhs) const override;
    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;

  private:
    int priority = 2;
  };
}
