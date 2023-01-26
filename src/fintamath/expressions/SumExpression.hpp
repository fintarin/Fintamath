#pragma once

#include <cstdint>

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class SumExpression : public IExpressionCRTP<SumExpression> {
public:
  // TODO: implement NegExpression and remove this
  struct SumElement {
    MathObjectPtr info;

    bool inverted = false;

    SumElement() = default;

    SumElement(const SumElement &rhs);

    SumElement(SumElement &&rhs) = default;

    SumElement &operator=(const SumElement &rhs);

    SumElement &operator=(SumElement &&rhs) noexcept = default;

    SumElement(const MathObjectPtr &info, bool inverted = false);

    MathObjectPtr toMathObject(bool isPrecise) const;

    void simplify(bool isPrecise);

    void setPrecision(uint8_t precision);
  };

  using PolynomVector = std::vector<SumElement>;

public:
  SumExpression() = default;

  SumExpression(const IMathObject &rhs);

  explicit SumExpression(PolynomVector inAddPolynom);

  std::string toString() const override;

  // TODO: implement iterator & remove this
  const PolynomVector &getPolynom() const;

  void addElement(const SumElement &elem);

  MathObjectPtr simplify() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  uint16_t getBaseOperatorPriority() const override;

  void setPrecision(uint8_t precision) override;

  std::vector<MathObjectPtr> getVariables() const override;

  MathObjectPtr getPowCoefficient(const MathObjectPtr &powValue) const;

  MathObjectPtr getPow() const;

private:
  // TODO: Implement a new Expression and remove this
  struct MulObject;
  using MulObjects = std::vector<MulObject>;

private:
  void compress();

  PolynomVector sumNumbers(const PolynomVector &numVect);

  static void sortPolynom(const PolynomVector &vect, PolynomVector &numVect, PolynomVector &mulVect,
                          PolynomVector &literalVect, PolynomVector &funcVect, PolynomVector &powVect);

  void simplifyPolynom();

  void simplifyNegations();

  static void sortMulObjects(MulObjects &objs, PolynomVector &mulVect, PolynomVector &literalVect,
                             PolynomVector &powVect);

  static void simplifyMul(PolynomVector &powVect, PolynomVector &addVect, PolynomVector &literalVect,
                          PolynomVector &funcVect);

private:
  PolynomVector addPolynom;
};

}