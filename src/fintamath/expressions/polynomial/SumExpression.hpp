#pragma once

#include "fintamath/expressions/interfaces/INegatable.hpp"
#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"

namespace fintamath {
class SumExpression : public IPolynomExpressionCRTP<SumExpression>, public INegatable {
public:
  explicit SumExpression(const ArgumentsPtrVector &children);

  string toString() const override;

  // ArgumentPtr getPowCoefficient(const ArgumentPtr &powValue) const;

  // ArgumentPtr getPow() const;

  ArgumentPtr negate() const override;

  // void multiplicate(const ArgumentPtr &value);

protected:
  ArgumentPtr postSimplify(size_t lhsChildNum, size_t rhsChildNum) const override;

  FunctionsVector getSimplifyFunctions() const override;

private:
  static ArgumentPtr simplifyNumber(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyNegation(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr coefficientsProcessing(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static std::pair<ArgumentPtr, ArgumentPtr> getRateAndValue(const ArgumentPtr &rhsChild);

  static ArgumentPtr addRateToValue(const ArgumentsPtrVector &rate, const ArgumentPtr &value);

  // bool static sortFunc(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  // void simplifyPolynom();

  // void simplifyNegations();

  // static void sortMulObjects(MulObjects &objs, ArgumentsPtrVector &mulVect, ArgumentsPtrVector &literalVect,
  //                            ArgumentsPtrVector &powVect);

  // static void simplifyMul(ArgumentsPtrVector &powVect, ArgumentsPtrVector &addVect, ArgumentsPtrVector &literalVect,
  //                         ArgumentsPtrVector &funcVect);
};

}