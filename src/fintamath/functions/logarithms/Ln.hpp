#include "fintamath/functions/Function.hpp"

namespace fintamath {
  class Ln: public FunctionImpl<Ln> {
  public:

    explicit Ln() = default;

    std::string toString() const override;

    MathObjectPtr operator()(const MathObject &rhs) const;

  protected:

    bool equals(const Ln& rhs) const override;

    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}
