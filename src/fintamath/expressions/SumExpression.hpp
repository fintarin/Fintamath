#pragma once

#include <cstdint>

#include "fintamath/expressions/PolynomExpression.hpp"

namespace fintamath {

// TODO: try to remove this and use Expression instead
struct SumElement : public PolynomElement {
  SumElement() = default;

  SumElement(const MathObjectPtr &info, bool inverted = false);

  SumElement(MathObjectPtr &&info, bool inverted = false);

  MathObjectPtr toMathObject(bool isPrecise) const;

  void simplify(bool isPrecise);
};

//-----------------------------------------------------------------------------------------------------//

class SumExpression : public PolynomExpressionCRTP<SumExpression, SumElement> {
public:
  SumExpression() = default;

  SumExpression(const IMathObject &rhs);

  explicit SumExpression(PolynomVector inPolynomVect);

  std::string toString() const override;

  MathObjectPtr simplify() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  const IFunction *getFunction() const override;

  MathObjectPtr getPowCoefficient(const MathObjectPtr &powValue) const;

  MathObjectPtr getPow() const;

private:
  // TODO: Implement a new Expression and remove this
  struct MulObject;
  using MulObjects = std::vector<MulObject>;

private:
  static PolynomVector sumNumbers(const PolynomVector &numVect);

  void simplifyPolynom();

  void simplifyNegations();

  static void sortMulObjects(MulObjects &objs, PolynomVector &mulVect, PolynomVector &literalVect,
                             PolynomVector &powVect);

  static void simplifyMul(PolynomVector &powVect, PolynomVector &addVect, PolynomVector &literalVect,
                          PolynomVector &funcVect);
};

}