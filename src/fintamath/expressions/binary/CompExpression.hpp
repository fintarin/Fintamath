#pragma once

#include "fintamath/expressions/binary/IBinaryExpression.hpp"

namespace fintamath {

class CompExpression : public IBinaryExpressionCRTP<CompExpression> {
public:
  CompExpression(const IOperator &oper, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  string toString() const override;

  void markAsSolution();

  static void setOppositeToFunction(const shared_ptr<IFunction> &function, const shared_ptr<IFunction> &opposite);

protected:
  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

  void copyProperties(const CompExpression &rhs) override;

private:
  bool isSolution = false;

  static map<string, shared_ptr<IFunction>, std::less<>> functionOpposMap;

  static shared_ptr<IFunction> getOpposite(const shared_ptr<IFunction> &function);

  void convertToSolution();
};

}