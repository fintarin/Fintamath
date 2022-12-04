#pragma once
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

  private:

    void parse(const TokenVector & tokens);

    std::vector<Element> mulPolynom;

    void tryCompressExpression();

    void tryCompressTree();
  };
}