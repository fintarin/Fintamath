#pragma once

#include "fintamath/expressions/IBinaryExpression.hpp"

namespace fintamath {

class CompExpression : public IBinaryExpressionCRTP<CompExpression> {
public:
  CompExpression(const IOperator &oper, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  string toString() const override;

  void markAsSolution();

  static void addOppositeFunctions(const shared_ptr<IFunction> &function, const shared_ptr<IFunction> &opposite);

  static shared_ptr<IFunction> getOppositeFunction(const shared_ptr<IFunction> &function);

protected:
  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

private:
  static map<string, shared_ptr<IFunction>, std::less<>> oppositeFunctionsMap;

  void convertToSolution();

private:
  bool isSolution = false;
};

}