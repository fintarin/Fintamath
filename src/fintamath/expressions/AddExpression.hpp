#pragma once

#include <cstdint>

#include "fintamath/expressions/IExpression.hpp"

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

    Element(const MathObjectPtr &info, bool inverted = false);

    Element(Element &&rhs) = default;

    Element &operator=(const Element &rhs);

    Element &operator=(Element &&rhs) noexcept = default;

    Polynom getAddPolynom() const;

    MathObjectPtr toMathObject(bool isPrecise) const;

    void simplify(bool isPrecise);

    void setPrecision(uint8_t precision);
  };

  AddExpression() = default;

  explicit AddExpression(const TokenVector &tokens);

  explicit AddExpression(Polynom inAddPolynom);

  AddExpression(const IMathObject &rhs);

  std::string toString() const override;

  ~AddExpression() override = default;

  void invert();

  // TODO: implement iterator & remove this
  const Polynom &getPolynom() const;

  void addElement(const Element &elem);

  MathObjectPtr simplify() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  uint16_t getBaseOperatorPriority() const override;

  void setPrecision(uint8_t precision) override;

  std::vector<MathObjectPtr> getVariables() const override;

  MathObjectPtr getPowCoefficient(const MathObjectPtr &powValue) const;

  MathObjectPtr getPow() const;

private:
  void parse(const TokenVector &tokens);

  Polynom addPolynom;

  Polynom compressExpression() const;

  Polynom compressTree() const;

  Polynom sumNumbers(const Polynom &numVect);

  static void sortPolynom(const Polynom &vect, Polynom &numVect, Polynom &mulVect, Polynom &literalVect,
                          Polynom &funcVect, Polynom &powVect);

  struct ObjectMul;
  using Objects = std::vector<ObjectMul>;

  void simplifyPolynom();
  static void sortMulObjects(Objects &objs, Polynom &mulVect, Polynom &literalVect, Polynom &powVect);

  static void simplifyMul(Polynom &powVect, Polynom &addVect, Polynom &literalVect, Polynom &funcVect);
};

}