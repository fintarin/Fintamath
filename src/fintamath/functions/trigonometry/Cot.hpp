#include "fintamath/functions/Function.hpp"

namespace fintamath {
  class Cot : public FunctionImpl<Cot> {
  public:
    Cot() = default;

    std::string toString() const override;

    MathObjectPtr operator()(const MathObject &rhs) const;

  protected:
    bool equals(const Cot &rhs) const override;

    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}