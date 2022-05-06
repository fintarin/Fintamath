#include "Function.hpp"

namespace fintamath {
  class Atan: public FunctionImpl<Atan> {
  public:

    explicit Atan() = default;

    std::string toString() const override;

    MathObjectPtr operator()(const MathObject &rhs) const;

  protected:

    bool equals(const Atan& rhs) const override;

    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override;
  };
}