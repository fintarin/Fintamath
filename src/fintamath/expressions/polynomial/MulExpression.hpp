#pragma once

#include <cstdint>

#include "fintamath/expressions/IInvertable.hpp"
#include "fintamath/expressions/INegatable.hpp"
#include "fintamath/expressions/IPolynomExpression.hpp"

namespace fintamath {
class MulExpression : public IPolynomExpressionCRTP<MulExpression>, public INegatable, public IInvertable {
public:
  MulExpression() = default;

  explicit MulExpression(PolynomVector inPolynomVect);

  MulExpression(const IMathObject &rhs);

  std::string toString() const override;

  MathObjectPtr toMinimalObject() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  const IFunction *getFunction() const override;

  MathObjectPtr getPowCoefficient(const MathObjectPtr &powValue) const;

  MathObjectPtr getPow() const;

  void negate() override;

  void invert() override;

private:
  // TODO: Implement a new Expression and remove this
  struct ObjectPow;
  using Objects = std::vector<ObjectPow>;

private:
  static std::string sumExprToString(const MathObjectPtr &obj);

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

  static bool sortFunc(const MathObjectPtr &lhs, const MathObjectPtr &rhs);
};

}