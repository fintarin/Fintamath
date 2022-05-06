#include "fintamath/functions/Operator.hpp"

namespace fintamath {
  class Sub: public OperatorImpl<Sub> {
  public:

    explicit Sub() = default;

    std::string toString() const override;

    int getPriority() const override;

    MathObjectPtr operator()(const MathObject &lhs, const MathObject &rhs) const;

  protected:
    bool equals(const Sub& rhs) const override;
    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;

  private:
    int priority = 1;
  };
}
