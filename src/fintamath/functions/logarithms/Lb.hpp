#include "fintamath/functions/Function.hpp"

namespace fintamath {
  class Lb: public FunctionImpl<Lb> {
  public:

    explicit Lb() = default;

    std::string toString() const override;

    MathObjectPtr operator()(const MathObject &rhs) const;

  protected:

    bool equals(const Lb& rhs) const override;

    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}