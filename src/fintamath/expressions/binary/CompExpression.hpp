#pragma once

#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"

#include "fintamath/expressions/interfaces/ILogicNegatableExpression.hpp"

namespace fintamath {

class CompExpression : public IBinaryExpressionCRTP<CompExpression>, public ILogicNegatableExpression {
public:
  CompExpression(const IOperator &inOper, const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild);

  std::string toString() const override;

  void markAsSolution();

protected:
  ArgumentPtr logicNegate() const override;

  // TODO! remove
  ArgumentPtr preSimplify() const override;

  // TODO! remove
  ArgumentPtr postSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

  static std::map<std::string, std::shared_ptr<IFunction>, std::less<>> &getOppositeFunctionsMap();

  static std::map<std::string, std::shared_ptr<IFunction>, std::less<>> &getLogicOppositeFunctionsMap();

  static std::shared_ptr<IFunction> getOppositeFunction(const IFunction &function);

  static std::shared_ptr<IFunction> getLogicOppositeFunction(const IFunction &function);

private:
  bool isSolution = false;
};

}