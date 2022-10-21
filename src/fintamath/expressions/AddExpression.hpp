#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {
  class AddExpression : public IExpressionCRTP<AddExpression> {
  private:
    struct Element {
      MathObjectPtr info;
      bool inverted = false;
    };

  public:
    std::string toString() const override;

  private:
    std::vector<Element> addPolynom;
  };
}