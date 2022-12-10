#pragma once
#include "fintamath/core/Defines.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/helpers/Converter.hpp"

namespace fintamath {
  class AddExpression : public IExpressionCRTP<AddExpression> {
  public:
    struct Element;

    using Polynom = std::vector<Element>;

    struct Element {
      MathObjectPtr info;
      bool inverted = false;

      Element() = default;

      Element(const Element &rhs);

      Element(MathObjectPtr info, bool inverted = false);

      Element(Element &&rhs) = default;

      Element &operator=(const Element &rhs);

      Element &operator=(Element &&rhs) noexcept = default;

      Polynom getAddPolynom() const;

    };

    AddExpression() = default;

    explicit AddExpression(const TokenVector& tokens);

    explicit AddExpression(Polynom inAddPolynom);

    AddExpression(const AddExpression &rhs) noexcept;

    AddExpression(AddExpression &&rhs) noexcept;

    AddExpression &operator=(const AddExpression &rhs) noexcept;

    AddExpression &operator=(AddExpression &&rhs) noexcept;

    std::string toString() const override;

    std::string getClassName() const override;

    ~AddExpression() override = default;

    void invert();

    const Polynom &getPolynom() const;

    void addElement(const Element &elem);

    MathObjectPtr simplify() const override;

  private:

    void parse(const TokenVector & tokens);

    Polynom addPolynom;

    MathObjectPtr tryCompressExpression() const;

    MathObjectPtr tryCompressTree() const;

    static Polynom sumNumbers(const Polynom& numVect);
    
    void sort();
  };
}