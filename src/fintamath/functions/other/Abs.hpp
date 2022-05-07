#include "fintamath/functions/Function.hpp"

namespace fintamath {
  class Abs : public FunctionImpl<Abs> {
  public:
    explicit Abs() = default;

    std::string toString() const override;

    MathObjectPtr operator()(const MathObject &rhs) const;

  protected:
    bool equals(const Abs &rhs) const override;

    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}