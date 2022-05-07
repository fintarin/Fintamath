#include "fintamath/functions/Function.hpp"

namespace fintamath {
  class Sqrt : public FunctionImpl<Sqrt> {
  public:
    explicit Sqrt() = default;

    std::string toString() const override;

    MathObjectPtr operator()(const MathObject &rhs) const;

  protected:
    bool equals(const Sqrt &rhs) const override;

    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}
