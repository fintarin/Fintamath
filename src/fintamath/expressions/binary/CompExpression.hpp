#pragma once

#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"

#include "fintamath/expressions/interfaces/ILogicNegatableExpression.hpp"

namespace fintamath {

class CompExpression : public IBinaryExpressionCRTP<CompExpression>, public ILogicNegatableExpression {
public:
  CompExpression(const IOperator &inOper, const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild);

  std::string toString() const override;

  void markAsSolution();

  static void addOppositeFunctions(const std::shared_ptr<IFunction> &function,
                                   const std::shared_ptr<IFunction> &opposite);

  static std::shared_ptr<IFunction> getOppositeFunction(const std::shared_ptr<IFunction> &function);

  static void addLogicOppositeFunctions(const std::shared_ptr<IFunction> &function,
                                        const std::shared_ptr<IFunction> &opposite);

  static std::shared_ptr<IFunction> getLogicOppositeFunction(const std::shared_ptr<IFunction> &function);

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

private:
  bool isSolution = false;
};

}