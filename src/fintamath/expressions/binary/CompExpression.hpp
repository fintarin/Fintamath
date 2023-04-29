#pragma once

#include "fintamath/expressions/IBinaryExpression.hpp"

namespace fintamath {

class CompExpression : public IBinaryExpressionCRTP<CompExpression> {
public:
  CompExpression(const IOperator &inOper, const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild);

  std::string toString() const override;

  void markAsSolution();

  static void addOppositeFunctions(const std::shared_ptr<IFunction> &function,
                                   const std::shared_ptr<IFunction> &opposite);

  static std::shared_ptr<IFunction> getOppositeFunction(const std::shared_ptr<IFunction> &function);

protected:
  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

private:
  static std::map<std::string, std::shared_ptr<IFunction>, std::less<>> oppositeFunctionsMap;

  void convertToSolution();

private:
  bool isSolution = false;
};

}