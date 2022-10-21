#include "fintamath/expressions/IExpression.hpp"

#include "fintamath/core/Defines.hpp"

namespace fintamath {
  class MulExpression : public IExpressionCRTP<MulExpression> {
  private:
    struct Element {
      MathObjectPtr info;
      bool inverted = false;
    };

  public:
    std::string toString() const override;

  private:
    std::vector<Element> mulPolynom;
  };
}