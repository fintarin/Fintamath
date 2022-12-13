#pragma once
#include "fintamath/expressions/AddExpression.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/helpers/Converter.hpp"

namespace fintamath {
  class MulExpression : public IExpressionCRTP<MulExpression> {
  public:
    struct Element;

    using Polynom = std::vector<Element>;

    struct Element {
      MathObjectPtr info;
      bool inverted = false;

      Element() = default;

      Element(const Element &rhs);

      Element(Element &&rhs) = default;

      Element(MathObjectPtr info, bool inverted = false);

      Element &operator=(const Element &rhs);

      Element &operator=(Element &&rhs) noexcept = default;

      Polynom getMulPolynom() const;
    };

    MulExpression() = default;

    explicit MulExpression(const TokenVector &tokens);

    explicit MulExpression(Polynom inMulPolynom);

    MulExpression(const MulExpression &rhs) noexcept;

    MulExpression(MulExpression &&rhs) noexcept;

    MulExpression &operator=(const MulExpression &rhs) noexcept;

    MulExpression &operator=(MulExpression &&rhs) noexcept;

    ~MulExpression() override = default;

    std::string toString() const override;

    std::string getClassName() const override;

    const Polynom &getPolynom() const;

    void addElement(const Element &elem);

    MathObjectPtr simplify() const override;

  private:

    void parse(const TokenVector &tokens);

    MulExpression simplifyResultToMulExpression() const;

    Polynom mulPolynom;

    MathObjectPtr compressExpression() const;

    MathObjectPtr compressTree() const;

    static std::string tryPutInBrackets(const MathObjectPtr &obj);\

    static Polynom openPowMulExpression(const Polynom& powVect);

    static Polynom mulNumbers(const Polynom& numVect);

    static Polynom multiplicateBraces(const Polynom& addVect);

    static Polynom multiplicateTwoBraces(const Polynom& lhs, const Polynom& rhs);

    static Polynom divideBraceByObj(const Polynom& lhs, const Polynom& rhs);

    void simplifyPolynom();

    void simplifyPow(Polynom& powVect, Polynom& addVect, Polynom& literalVect);

    struct ObjectPow;

    using Objects = std::vector<ObjectPow>;

    void sortPowObjects(const Objects& objs, Polynom& powVect, Polynom& addVect, Polynom& literalVect);

  };
}