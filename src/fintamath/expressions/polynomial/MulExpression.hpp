#pragma once

#include <cstdint>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/IInvertable.hpp"
#include "fintamath/expressions/INegatable.hpp"
#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"

namespace fintamath {
class MulExpression : public IPolynomExpressionCRTP<MulExpression>, public INegatable, public IInvertable {
public:
  MulExpression() = default;

  explicit MulExpression(ArgumentsPtrVector &&inPolynomVect);

  std::string toString() const override;

  MathObjectPtr toMinimalObject() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  const IFunction *getFunction() const override;

  MathObjectPtr getPowCoefficient(const MathObjectPtr &powValue) const;

  MathObjectPtr getPow() const;

  void negate() override;

  void invert() override;

protected:
  IMathObject *simplify() override;

private:
  // TODO: Implement a new Expression and remove this
  struct ObjectPow;
  using Objects = std::vector<ObjectPow>;

  static std::string sumExprToString(const MathObjectPtr &obj);

  static ArgumentsPtrVector openPowMulExpression(const ArgumentsPtrVector &powVect);

  static ArgumentsPtrVector mulNumbers(const ArgumentsPtrVector &numVect);

  static void multiplicateBraces(const ArgumentsPtrVector &addVect, ArgumentsPtrVector &positive,
                                 ArgumentsPtrVector &negative);

  static ArgumentsPtrVector multiplicateTwoBraces(const ArgumentsPtrVector &lhs, const ArgumentsPtrVector &rhs);

  void simplifyPolynom();

  void simplifyDivisions();

  static void simplifyPow(ArgumentsPtrVector &powVect, ArgumentsPtrVector &addVect, ArgumentsPtrVector &literalVect,
                          ArgumentsPtrVector &funcVect);

  static void multiplicatePolynom(ArgumentsPtrVector &vect, ArgumentsPtrVector &positive, ArgumentsPtrVector &negative);

  static void sortPowObjects(Objects &objs, ArgumentsPtrVector &powVect, ArgumentsPtrVector &addVect,
                             ArgumentsPtrVector &literalVect, ArgumentsPtrVector &funcVect);

  static bool sortFunc(const MathObjectPtr &lhs, const MathObjectPtr &rhs);
};

}