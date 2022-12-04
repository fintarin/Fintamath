#include "fintamath/core/Defines.hpp"
#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {
  class AddExpression : public IExpressionCRTP<AddExpression> {
  private:
    struct Element {
      ExpressionPtr info;
      bool inverted = false;

      Element() = default;

      Element(const Element &rhs);

      Element(Element &&rhs) = default;

      Element &operator=(const Element &rhs);

      Element &operator=(Element &&rhs) noexcept = default;
    };

  public:
    AddExpression() = default;

    explicit AddExpression(const TokenVector& tokens);

    AddExpression(const AddExpression &rhs) noexcept;

    AddExpression(AddExpression &&rhs) noexcept;

    AddExpression(const std::string& str) noexcept;

    std::string toString() const override;

    std::string getClassName() const override;

    ~AddExpression() override = default;

  private:
    void parse(const TokenVector & tokens);
    std::vector<Element> addPolynom;
  };
}