#pragma once

#include "fintamath/expressions/interfaces/IInvertable.hpp"
#include "fintamath/expressions/interfaces/INegatable.hpp"
#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"

namespace fintamath {
class MulExpression : public IPolynomExpressionCRTP<MulExpression>, public INegatable, public IInvertable {
public:
  explicit MulExpression(const ArgumentsPtrVector &children);

  string toString() const override;

  // ArgumentPtr getPowCoefficient(const ArgumentPtr &powValue) const;

  // ArgumentPtr getPow() const;

  // void setPow(const ArgumentPtr &value);

  ArgumentPtr negate() const override;

  ArgumentPtr invert() const override;

protected:
  FunctionsVector getSimplifyFunctions() const override;

private:
  static ArgumentPtr simplifyNumber(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyNegation(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyDivisions(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr multiplicateBraces(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr coefficientsProcessing(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static std::pair<ArgumentPtr, ArgumentPtr> getRateAndValue(const ArgumentPtr &rhsChild);

  static ArgumentPtr addRateToValue(const ArgumentsPtrVector &rate, const ArgumentPtr &value);

  // void simplifyNegations();

  // void simplifyPow();

  // void simplifyDivisions();

  // void simplifyPolynom();

  // static void simplifyPowCoefficients(map<IOperator::Priority, ArgumentsPtrVector> &priorityMap,
  //                                     ArgumentsPtrVector &functionVector, ArgumentsPtrVector &variableVector);

  // static void addValueToMaps(ArgumentPtr &lhs, ArgumentPtr &rhs,
  //                            map<string, ArgumentPtr> &valuesMap,
  //                            map<string, ArgumentsPtrVector> &powMap);

  // static ArgumentsPtrVector coefficientProcessing(map<string, ArgumentPtr> &valuesMap,
  //                                                 map<string, ArgumentsPtrVector> &powMap);

  // TODO: remove
  static string sumExprToString(const ArgumentPtr &obj);

  // static void multiplicateBraces(const ArgumentsPtrVector &addVect, ArgumentsPtrVector &positive,
  //                                ArgumentsPtrVector &negative);

  // static ArgumentsPtrVector multiplicateTwoBraces(const ArgumentsPtrVector &lhs, const ArgumentsPtrVector &rhs);

  // static void simplifyPow(ArgumentsPtrVector &powVect, ArgumentsPtrVector &addVect, ArgumentsPtrVector &literalVect,
  //                         ArgumentsPtrVector &funcVect);

  // static void multiplicatePolynom(ArgumentsPtrVector &vect, ArgumentsPtrVector &positive, ArgumentsPtrVector
  // &negative);

  // static void sortPowObjects(Objects &objs, ArgumentsPtrVector &powVect, ArgumentsPtrVector &addVect,
  //                            ArgumentsPtrVector &literalVect, ArgumentsPtrVector &funcVect);

  // static bool sortFunc(const ArgumentPtr &lhs, const ArgumentPtr &rhs);
};

}