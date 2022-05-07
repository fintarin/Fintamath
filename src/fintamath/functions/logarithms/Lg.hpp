#include "fintamath/functions/Function.hpp"

namespace fintamath {
  class Lg : public FunctionImpl<Lg> {
  public:
    explicit Lg() = default;

    std::string toString() const override;

    MathObjectPtr operator()(const MathObject &rhs) const;

  protected:
    bool equals(const Lg &rhs) const override;

    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}