#include "Function.hpp"

namespace fintamath {
  class Exp: public FunctionImpl<Exp> {
  public:

    explicit Exp() = default;

    std::string toString() const override;

    MathObjectPtr operator()(const MathObject &rhs) const;

  protected:

    bool equals(const Exp& rhs) const override;

    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}