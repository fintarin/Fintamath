#pragma once
#include "fintamath/core/Defines.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/helpers/Converter.hpp"

namespace fintamath {
  class AddExpression : public IExpressionCRTP<AddExpression> {
  private:

    friend class Expression;
    
    friend class MulExpression;
    struct Element {
      MathObjectPtr info;
      bool inverted = false;

      Element() = default;

      Element(const Element &rhs);

      Element(MathObjectPtr info, bool inverted = false);

      Element(Element &&rhs) = default;

      Element &operator=(const Element &rhs);

      Element &operator=(Element &&rhs) noexcept = default;

      std::vector<Element> getAddPolynom() const;

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

    void invert();

    void addElement(MathObjectPtr elem, bool inverted);

    MathObjectPtr simplify() const override;

  private:

    void parse(const TokenVector & tokens);

    std::vector<Element> addPolynom;

    MathObjectPtr tryCompressExpression() const;

    MathObjectPtr tryCompressTree() const;

    void sumNumbers();
    
  };
}