#include "fintamath/functions/Function.hpp"

namespace fintamath {
  class Asin: public FunctionImpl<Asin> {
  public:

    explicit Asin() = default;

    std::string toString() const override;

    MathObjectPtr operator()(const MathObject &rhs) const;

  protected:

    bool equals(const Asin& rhs) const override;

    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}
