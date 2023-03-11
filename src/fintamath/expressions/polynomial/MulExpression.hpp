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

  std::unique_ptr<IMathObject> simplify(bool isPrecise) const override;

  const IFunction *getFunction() const override;

  std::unique_ptr<IMathObject> getPowCoefficient(const std::unique_ptr<IMathObject> &powValue) const;

  std::unique_ptr<IMathObject> getPow() const;

  void setPow(const std::unique_ptr<IMathObject> &value);

  void negate() override;

  void invert() override;

protected:
  IMathObject *simplify() override;

private:
  // TODO: Implement a new Expression and remove this
  struct ObjectPow;
  using Objects = std::vector<ObjectPow>;

  void simplifyNegations();

  void simplifyPow();

  void simplifyDivisions();

  void simplifyPolynom();

  static void simplifyPowCoefficients(std::map<IOperator::Priority, ArgumentsPtrVector> &priorityMap,
                                      ArgumentsPtrVector &functionVector, ArgumentsPtrVector &variableVector);

  static void addValueToMaps(std::unique_ptr<IMathObject> &lhs, std::unique_ptr<IMathObject> &rhs,
                             std::map<std::string, std::unique_ptr<IMathObject>> &valuesMap,
                             std::map<std::string, ArgumentsPtrVector> &powMap);

  static ArgumentsPtrVector coefficientProcessing(std::map<std::string, std::unique_ptr<IMathObject>> &valuesMap,
                                                  std::map<std::string, ArgumentsPtrVector> &powMap);

  static std::string sumExprToString(const std::unique_ptr<IMathObject> &obj);

  static std::unique_ptr<INumber> mulNumbers(const ArgumentsPtrVector &numVect);

  static void multiplicateBraces(const ArgumentsPtrVector &addVect, ArgumentsPtrVector &positive,
                                 ArgumentsPtrVector &negative);

  static ArgumentsPtrVector multiplicateTwoBraces(const ArgumentsPtrVector &lhs, const ArgumentsPtrVector &rhs);

  static void simplifyPow(ArgumentsPtrVector &powVect, ArgumentsPtrVector &addVect, ArgumentsPtrVector &literalVect,
                          ArgumentsPtrVector &funcVect);

  static void multiplicatePolynom(ArgumentsPtrVector &vect, ArgumentsPtrVector &positive, ArgumentsPtrVector &negative);

  static void sortPowObjects(Objects &objs, ArgumentsPtrVector &powVect, ArgumentsPtrVector &addVect,
                             ArgumentsPtrVector &literalVect, ArgumentsPtrVector &funcVect);

  static bool sortFunc(const std::unique_ptr<IMathObject> &lhs, const std::unique_ptr<IMathObject> &rhs);
};

}