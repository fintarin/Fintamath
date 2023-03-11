#pragma once

#include <cstdint>

#include "fintamath/expressions/INegatable.hpp"
#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"
#include "fintamath/meta/Converter.hpp"

namespace fintamath {
class SumExpression : public IPolynomExpressionCRTP<SumExpression>, public INegatable {
public:
  SumExpression() = default; // TODO: remove this

  explicit SumExpression(ArgumentsPtrVector &&inPolynomVect);

  std::string toString() const override;

  std::unique_ptr<IMathObject> simplify(bool isPrecise) const override;

  const IFunction *getFunction() const override;

  std::unique_ptr<IMathObject> getPowCoefficient(const std::unique_ptr<IMathObject> &powValue) const;

  std::unique_ptr<IMathObject> getPow() const;

  void negate() override;

  void multiplicate(const std::unique_ptr<IMathObject> &value);

protected:
  IMathObject *simplify() override;

private:
  // TODO: Implement a new Expression and remove this
  struct MulObject;
  using MulObjects = std::vector<MulObject>;

  static ArgumentsPtrVector sumNumbers(const ArgumentsPtrVector &numVect);

  bool static sortFunc(const std::unique_ptr<IMathObject> &lhs, const std::unique_ptr<IMathObject> &rhs);

  void simplifyPolynom();

  void simplifyNegations();

  static void sortMulObjects(MulObjects &objs, ArgumentsPtrVector &mulVect, ArgumentsPtrVector &literalVect,
                             ArgumentsPtrVector &powVect);

  static void simplifyMul(ArgumentsPtrVector &powVect, ArgumentsPtrVector &addVect, ArgumentsPtrVector &literalVect,
                          ArgumentsPtrVector &funcVect);
};

}