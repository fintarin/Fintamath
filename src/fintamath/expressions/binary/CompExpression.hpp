#pragma once

#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"

namespace fintamath {

class CompExpression : public IBinaryExpressionCRTP<CompExpression, true> {
public:
  CompExpression(const IOperator &inOper, const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild);

  std::string toString() const override;

  void markAsSolution();

  static MathObjectType getTypeStatic() {
    return MathObjectType::CompExpression;
  }

protected:
  // TODO!!! reimplement
  // ArgumentPtr logicNegate() const override;

  ArgumentPtr preSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

  static std::map<std::string, std::shared_ptr<IFunction>, std::less<>> &getOppositeFunctionsMap();

  static std::map<std::string, std::shared_ptr<IFunction>, std::less<>> &getLogicOppositeFunctionsMap();

  static std::shared_ptr<IFunction> getOppositeFunction(const IFunction &function);

  static std::shared_ptr<IFunction> getLogicOppositeFunction(const IFunction &function);

private:
  static ArgumentPtr coeffSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  bool isSolution = false;
};

}