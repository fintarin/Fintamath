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

  MathObjectPtr simplify(bool isPrecise) const override;

  const IFunction *getFunction() const override;

  MathObjectPtr getPowCoefficient(const MathObjectPtr &powValue) const;

  MathObjectPtr getPow() const;

  void setPow(const MathObjectPtr &value);

  void negate() override;

  void invert() override;

protected:
  IMathObject *simplify() override;

private:
  // TODO: Implement a new Expression and remove this
  struct ObjectPow;
  using Objects = std::vector<ObjectPow>;

  void simplifyNegations();

  void simplifyDivisions();

  void simplifyPolynom();

  static void simplifyPowCoefficients(std::map<IOperator::Priority, ArgumentsPtrVector> &priorityMap,
                                      ArgumentsPtrVector &functionVector, ArgumentsPtrVector &variableVector);

  static void addValueToMaps(MathObjectPtr &lhs, MathObjectPtr &rhs, std::map<std::string, MathObjectPtr> &valuesMap,
                             std::map<std::string, ArgumentsPtrVector> &powMap);

  static ArgumentsPtrVector coefficientProcessing(std::map<std::string, MathObjectPtr> &valuesMap,
                                                  std::map<std::string, ArgumentsPtrVector> &powMap);

  static std::string sumExprToString(const MathObjectPtr &obj);

  static NumberPtr mulNumbers(const ArgumentsPtrVector &numVect);

  static void multiplicateBraces(const ArgumentsPtrVector &addVect, ArgumentsPtrVector &positive,
                                 ArgumentsPtrVector &negative);

  static ArgumentsPtrVector multiplicateTwoBraces(const ArgumentsPtrVector &lhs, const ArgumentsPtrVector &rhs);

  static void simplifyPow(ArgumentsPtrVector &powVect, ArgumentsPtrVector &addVect, ArgumentsPtrVector &literalVect,
                          ArgumentsPtrVector &funcVect);

  static void multiplicatePolynom(ArgumentsPtrVector &vect, ArgumentsPtrVector &positive, ArgumentsPtrVector &negative);

  static void sortPowObjects(Objects &objs, ArgumentsPtrVector &powVect, ArgumentsPtrVector &addVect,
                             ArgumentsPtrVector &literalVect, ArgumentsPtrVector &funcVect);

  static bool sortFunc(const MathObjectPtr &lhs, const MathObjectPtr &rhs);
};

}