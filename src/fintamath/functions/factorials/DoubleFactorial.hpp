#include "fintamath/functions/Function.hpp"

namespace fintamath {
  class DoubleFactorial : public FunctionImpl<DoubleFactorial> {
  public:
    explicit DoubleFactorial() = default;

    std::string toString() const override;

    MathObjectPtr operator()(const MathObject &rhs) const;

  protected:
    bool equals(const DoubleFactorial &rhs) const override;

    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}