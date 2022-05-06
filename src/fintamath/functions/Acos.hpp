#include "Function.hpp"

namespace fintamath {
  class Acos: public FunctionImpl<Acos> {
  public:

    explicit Acos() = default;

    std::string toString() const override;

    MathObjectPtr operator()(const MathObject &rhs) const;

  protected:

    bool equals(const Acos& rhs) const override;

    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}