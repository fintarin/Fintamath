#pragma once
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/helpers/Converter.hpp"

namespace fintamath {
  class MulExpression : public IExpressionCRTP<MulExpression> {
  private:

    friend class Expression;

    friend class AddExpression;
    struct Element {
      MathObjectPtr info;
      bool inverted = false;

      Element() = default;

      Element(const Element &rhs);

      Element(Element &&rhs) = default;

      Element(MathObjectPtr info, bool inverted = false);

      Element &operator=(const Element &rhs);

      Element &operator=(Element &&rhs) noexcept = default;

      std::vector<Element> getMulPolynom() const;
    };

  public:

    MulExpression() = default;

    explicit MulExpression(const TokenVector& tokens);
    
    MulExpression(const MulExpression &rhs) noexcept;

    MulExpression(MulExpression &&rhs) noexcept;

    MulExpression &operator=(const MulExpression &rhs) noexcept;

    MulExpression &operator=(MulExpression &&rhs) noexcept;

    std::string toString() const override;

    std::string getClassName() const override;

    ~MulExpression() override = default;

    void addElement(MathObjectPtr elem, bool inverted);

    MathObjectPtr simplify() const override;

  private:

    void parse(const TokenVector & tokens);

    std::vector<Element> mulPolynom;

    MathObjectPtr tryCompressExpression() const;

    MathObjectPtr tryCompressTree() const;

    static std::string tryPutInBrackets(const MathObjectPtr& obj);

    void mulNumbers();

  };
}