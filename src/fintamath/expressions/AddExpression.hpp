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

      MathObjectPtr toMathObject() const;

    };

    AddExpression() = default;

    explicit AddExpression(const TokenVector& tokens);

    explicit AddExpression(Polynom inAddPolynom);

    AddExpression(const AddExpression &rhs) noexcept;

    AddExpression(AddExpression &&rhs) noexcept;

    AddExpression(const IMathObject& rhs);

    AddExpression &operator=(const AddExpression &rhs) noexcept;

    AddExpression &operator=(AddExpression &&rhs) noexcept;

    std::string toString() const override;

    std::string getClassName() const override;

    ~AddExpression() override = default;

    void invert();

    const Polynom &getPolynom() const;

    void addElement(const Element &elem);

    MathObjectPtr simplify() const override;

    uint16_t getInfoPriority() override;

  private:

    void parse(const TokenVector & tokens);

    Polynom addPolynom;

    Polynom compressExpression() const;

    Polynom compressTree() const;

    static Polynom sumNumbers(const Polynom& numVect);

    static void sortPolynom(const Polynom& vect, Polynom& numVect, Polynom& mulVect, Polynom& literalVect, Polynom& funcVect, Polynom& powVect);

    struct ObjectMul;
    using Objects = std::vector<ObjectMul>;
    
    void simplifyPolynom();
    static void sortMulObjects(Objects& objs, Polynom& mulVect, Polynom& literalVect, Polynom& powVect);

    static void simplifyMul(Polynom& mulVect, Polynom& literalVect, Polynom& powVect);

  };
}