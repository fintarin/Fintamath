#pragma once

#include <cstdint>

#include "fintamath/expressions/PolynomExpression.hpp"

namespace fintamath {

// TODO: try to remove this and use Expression instead
struct MulElement : public PolynomElement {
  MulElement() = default;

  MulElement(MathObjectPtr &&info, bool inverted = false);

  MathObjectPtr toMathObject(bool isPrecise) const;

  void simplify(bool isPrecise);
};

//-----------------------------------------------------------------------------------------------------//

class MulExpression : public PolynomExpressionCRTP<MulExpression, MulElement> {
public:
  MulExpression() = default; // TODO: remove this

  explicit MulExpression(PolynomVector inPolynomVect);

  MulExpression(const IMathObject &rhs);

  std::string toString() const override;

  MathObjectPtr toMinimalObject() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  const IFunction *getFunction() const override;

  MathObjectPtr getPowCoefficient(const MathObjectPtr &powValue) const;

  MathObjectPtr getPow() const;

private:
  // TODO: Implement a new Expression and remove this
  struct ObjectPow;
  using Objects = std::vector<ObjectPow>;

private:
  static std::string tryPutInBrackets(const MathObjectPtr &obj);

  static PolynomVector openPowMulExpression(const PolynomVector &powVect);

  static PolynomVector mulNumbers(const PolynomVector &numVect);

  static void multiplicateBraces(const PolynomVector &addVect, PolynomVector &positive, PolynomVector &negative);

  static PolynomVector multiplicateTwoBraces(const PolynomVector &lhs, const PolynomVector &rhs);

  void simplifyPolynom();

  void simplifyDivisions();

  static void simplifyPow(PolynomVector &powVect, PolynomVector &addVect, PolynomVector &literalVect,
                          PolynomVector &funcVect);

  static void multiplicatePolynom(PolynomVector &vect, PolynomVector &positive, PolynomVector &negative);

  static void sortPowObjects(Objects &objs, PolynomVector &powVect, PolynomVector &addVect, PolynomVector &literalVect,
                             PolynomVector &funcVect);
};

}