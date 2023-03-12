#pragma once

#include <cstdint>

#include "fintamath/expressions/INegatable.hpp"
#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"
#include "fintamath/meta/Converter.hpp"

namespace fintamath {
class SumExpression : public IPolynomExpressionCRTP<SumExpression>, public INegatable {
public:
  explicit SumExpression(ArgumentsPtrVector children);

  std::string toString() const override;

  std::unique_ptr<IMathObject> simplify(bool isPrecise) const override;

  std::shared_ptr<IMathObject> getPowCoefficient(const std::shared_ptr<IMathObject> &powValue) const;

  std::shared_ptr<IMathObject> getPow() const;

  void negate() override;

  void multiplicate(const std::shared_ptr<IMathObject> &value);

protected:
  std::shared_ptr<IMathObject> simplify() override;

  std::shared_ptr<IMathObject> simplifyChildren(const std::shared_ptr<IMathObject> &lhsChild,
                                                const std::shared_ptr<IMathObject> &rhsChild) override;

private:
  // TODO: Implement a new Expression and remove this
  struct MulObject;
  using MulObjects = std::vector<MulObject>;

  static ArgumentsPtrVector sumNumbers(const ArgumentsPtrVector &numVect);

  bool static sortFunc(const std::shared_ptr<IMathObject> &lhs, const std::shared_ptr<IMathObject> &rhs);

  void simplifyPolynom();

  void simplifyNegations();

  static void sortMulObjects(MulObjects &objs, ArgumentsPtrVector &mulVect, ArgumentsPtrVector &literalVect,
                             ArgumentsPtrVector &powVect);

  static void simplifyMul(ArgumentsPtrVector &powVect, ArgumentsPtrVector &addVect, ArgumentsPtrVector &literalVect,
                          ArgumentsPtrVector &funcVect);
};

}