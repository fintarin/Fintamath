#pragma once

#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"

namespace fintamath {

class IOperator;

class CompExpression final : public IBinaryExpressionCRTP<CompExpression, true> {
public:
  CompExpression(const IOperator &inOper, ArgumentPtr inLhsChild, ArgumentPtr inRhsChild);

  std::string toString() const override;

  void markAsSolution();

  static MathObjectType getTypeStatic() {
    return MathObjectType::CompExpression;
  }

protected:
  ArgumentPtr preSimplify() const override;

  SimplifyFunctionVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

  static std::shared_ptr<IFunction> getOppositeFunction(const IFunction &function);

private:
  static ArgumentPtr constSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr divSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr negSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr rateSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr approxSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  bool isSolution = false;
};

}