#pragma once

#include <cstdint>

#include "fintamath/expressions/interfaces/INegatable.hpp"
#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"
#include "fintamath/meta/Converter.hpp"

namespace fintamath {
class SumExpression : public IPolynomExpressionCRTP<SumExpression>, public INegatable {
public:
  explicit SumExpression(const ArgumentsPtrVector &children);

  string toString() const override;

  // shared_ptr<IMathObject> getPowCoefficient(const shared_ptr<IMathObject> &powValue) const;

  // shared_ptr<IMathObject> getPow() const;

  void negate() override;

  // void multiplicate(const shared_ptr<IMathObject> &value);

protected:
  shared_ptr<IMathObject> postSimplify(size_t lhsChildNum, size_t rhsChildNum) const override;

private:
  // TODO: Implement a new Expression and remove this
  // struct MulObject;
  // using MulObjects = vector<MulObject>;

  // bool static sortFunc(const shared_ptr<IMathObject> &lhs, const shared_ptr<IMathObject> &rhs);

  // void simplifyPolynom();

  // void simplifyNegations();

  // static void sortMulObjects(MulObjects &objs, ArgumentsPtrVector &mulVect, ArgumentsPtrVector &literalVect,
  //                            ArgumentsPtrVector &powVect);

  // static void simplifyMul(ArgumentsPtrVector &powVect, ArgumentsPtrVector &addVect, ArgumentsPtrVector &literalVect,
  //                         ArgumentsPtrVector &funcVect);
};

}