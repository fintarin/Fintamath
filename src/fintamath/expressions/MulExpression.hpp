#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {
  class MulExpression : public IExpressionCRTP<MulExpression> {
  private:
    struct Element {
      MathObjectPtr info;
      bool inverted = false;

      Element() = default;

      Element(const Element &rhs);

      Element(Element &&rhs) = default;

      Element &operator=(const Element &rhs);

      Element &operator=(Element &&rhs) noexcept = default;
    };

  public:
    std::string toString() const override;

    std::string getClassName() const override;

  private:
    std::vector<Element> mulPolynom;
  };
}