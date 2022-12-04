#include "fintamath/core/Defines.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/helpers/Converter.hpp"

namespace fintamath {
  class AddExpression : public IExpressionCRTP<AddExpression> {
  private:
    struct Element {
      MathObjectPtr info;
      bool inverted = false;

      Element() = default;

      Element(const Element &rhs);

      Element(MathObjectPtr info, bool inverted = false);

      Element(Element &&rhs) = default;

      Element &operator=(const Element &rhs);

      Element &operator=(Element &&rhs) noexcept = default;
    };

  public:
    AddExpression() = default;

    explicit AddExpression(const TokenVector& tokens);

    AddExpression(const AddExpression &rhs) noexcept;

    AddExpression(AddExpression &&rhs) noexcept;

    AddExpression &operator=(const AddExpression &rhs) noexcept;

    AddExpression &operator=(AddExpression &&rhs) noexcept;

    std::string toString() const override;

    std::string getClassName() const override;

    ~AddExpression() override = default;

  private:

    void parse(const TokenVector & tokens);

    std::vector<Element> addPolynom;
    
  };
}