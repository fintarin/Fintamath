#include "fintamath/functions/Function.hpp"

namespace fintamath {
  class Lb : public FunctionImpl<Lb> {
  public:
    Lb() = default;

    std::string toString() const override;

    MathObjectPtr operator()(const MathObject &rhs) const;

  protected:
    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}
