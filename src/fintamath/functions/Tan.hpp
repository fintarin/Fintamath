#include "Function.hpp"

namespace fintamath {
  class Tan: public FunctionImpl<Tan> {
  public:

    explicit Tan() = default;

    std::string toString() const override;

    MathObjectPtr operator()(const MathObject &rhs) const;

  protected:

    bool equals(const Tan& rhs) const override;

    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}
