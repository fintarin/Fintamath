#pragma once

#include <cstdint>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/interfaces/IInvertable.hpp"
#include "fintamath/expressions/interfaces/INegatable.hpp"
#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"

namespace fintamath {
class MulExpression : public IPolynomExpressionCRTP<MulExpression>, public INegatable, public IInvertable {
public:
  explicit MulExpression(const ArgumentsPtrVector &children);

  string toString() const override;

  // shared_ptr<IMathObject> getPowCoefficient(const shared_ptr<IMathObject> &powValue) const;

  // shared_ptr<IMathObject> getPow() const;

  // void setPow(const shared_ptr<IMathObject> &value);

  void negate() override;

  void invert() override;

protected:
  shared_ptr<IMathObject> postSimplify(size_t lhsChildNum, size_t rhsChildNum) const override;

private:
  // TODO: Implement a new Expression and remove this
  // struct ObjectPow;
  // using Objects = vector<ObjectPow>;

  // void simplifyNegations();

  // void simplifyPow();

  // void simplifyDivisions();

  // void simplifyPolynom();

  // static void simplifyPowCoefficients(map<IOperator::Priority, ArgumentsPtrVector> &priorityMap,
  //                                     ArgumentsPtrVector &functionVector, ArgumentsPtrVector &variableVector);

  // static void addValueToMaps(shared_ptr<IMathObject> &lhs, shared_ptr<IMathObject> &rhs,
  //                            map<string, shared_ptr<IMathObject>> &valuesMap,
  //                            map<string, ArgumentsPtrVector> &powMap);

  // static ArgumentsPtrVector coefficientProcessing(map<string, shared_ptr<IMathObject>> &valuesMap,
  //                                                 map<string, ArgumentsPtrVector> &powMap);

  // TODO: remove
  static string sumExprToString(const shared_ptr<IMathObject> &obj);

  // static void multiplicateBraces(const ArgumentsPtrVector &addVect, ArgumentsPtrVector &positive,
  //                                ArgumentsPtrVector &negative);

  // static ArgumentsPtrVector multiplicateTwoBraces(const ArgumentsPtrVector &lhs, const ArgumentsPtrVector &rhs);

  // static void simplifyPow(ArgumentsPtrVector &powVect, ArgumentsPtrVector &addVect, ArgumentsPtrVector &literalVect,
  //                         ArgumentsPtrVector &funcVect);

  // static void multiplicatePolynom(ArgumentsPtrVector &vect, ArgumentsPtrVector &positive, ArgumentsPtrVector
  // &negative);

  // static void sortPowObjects(Objects &objs, ArgumentsPtrVector &powVect, ArgumentsPtrVector &addVect,
  //                            ArgumentsPtrVector &literalVect, ArgumentsPtrVector &funcVect);

  // static bool sortFunc(const shared_ptr<IMathObject> &lhs, const shared_ptr<IMathObject> &rhs);
};

}