#pragma once

#include <cstdint>

#include "fintamath/expressions/INegatable.hpp"
#include "fintamath/expressions/IPolynomExpression.hpp"

namespace fintamath {
class SumExpression : public IPolynomExpressionCRTP<SumExpression>, public INegatable {
public:
  SumExpression() = default; // TODO: remove this

  SumExpression(const IMathObject &rhs);

  explicit SumExpression(PolynomVector inPolynomVect);

  std::string toString() const override;

  MathObjectPtr toMinimalObject() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  const IFunction *getFunction() const override;

  MathObjectPtr getPowCoefficient(const MathObjectPtr &powValue) const;

  MathObjectPtr getPow() const;

  void negate() override;

private:
  // TODO: Implement a new Expression and remove this
  struct MulObject;
  using MulObjects = std::vector<MulObject>;

  static PolynomVector sumNumbers(const PolynomVector &numVect);

  bool static sortFunc(const MathObjectPtr &lhs, const MathObjectPtr &rhs);

  void simplifyPolynom();

  void simplifyNegations();

  static void sortMulObjects(MulObjects &objs, PolynomVector &mulVect, PolynomVector &literalVect,
                             PolynomVector &powVect);

  static void simplifyMul(PolynomVector &powVect, PolynomVector &addVect, PolynomVector &literalVect,
                          PolynomVector &funcVect);
};

}