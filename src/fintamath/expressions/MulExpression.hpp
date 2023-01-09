#pragma once

#include <cstdint>

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class MulExpression : public IExpressionCRTP<MulExpression> {
public:
  struct Element;
  using Polynom = std::vector<Element>;

  struct Element {
    MathObjectPtr info;

    bool inverted = false;

  public:
    Element() = default;

    Element(const Element &rhs);

    Element(Element &&rhs) = default;

    Element(const MathObjectPtr &info, bool inverted = false);

    Element &operator=(const Element &rhs);

    Element &operator=(Element &&rhs) noexcept = default;

    Polynom getMulPolynom() const;

    MathObjectPtr toMathObject(bool isPrecise) const;

    void setPrecision(uint8_t precision);

    void simplify(bool isPrecise);
  };

  MulExpression() = default;

  explicit MulExpression(const TokenVector &tokens);

  explicit MulExpression(Polynom inMulPolynom);

  MulExpression(const IMathObject &rhs);

  std::string toString() const override;

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

  Polynom mulPolynom;

  Polynom compressExpression() const;

  Polynom compressTree() const;

  static std::string tryPutInBrackets(const MathObjectPtr &obj);

  static Polynom openPowMulExpression(const Polynom &powVect);

  static Polynom mulNumbers(const Polynom &numVect);

  static void multiplicateBraces(const Polynom &addVect, Polynom &positive, Polynom &negative);

  static Polynom multiplicateTwoBraces(const Polynom &lhs, const Polynom &rhs);

  static void sortPolynom(const Polynom &vect, Polynom &numVect, Polynom &addVect, Polynom &literalVect,
                          Polynom &funcVect, Polynom &powVect);

  void simplifyPolynom();

  static void simplifyPow(Polynom &powVect, Polynom &addVect, Polynom &literalVect, Polynom &funcVect);

  static void multiplicatePolynom(Polynom &vect, Polynom &positive, Polynom &negative);

  struct ObjectPow;

  using Objects = std::vector<ObjectPow>;

  static void sortPowObjects(Objects &objs, Polynom &powVect, Polynom &addVect, Polynom &literalVect,
                             Polynom &funcVect);
};

}