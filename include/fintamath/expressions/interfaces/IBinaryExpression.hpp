#pragma once

#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "fintamath/core/MathObjectType.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class IBinaryExpression : public IExpression {
public:
  explicit IBinaryExpression(const IFunction &inFunc, ArgumentPtr lhs, ArgumentPtr rhs);

  std::string toString() const override;

  const std::shared_ptr<IFunction> &getFunction() const final;

  const ArgumentPtrVector &getChildren() const final;

  void setChildren(const ArgumentPtrVector &childVect) final;

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::IBinaryExpression, "IBinaryExpression"};
  }

protected:
  using SimplifyFunction = std::function<ArgumentPtr(const IFunction &, const ArgumentPtr &, const ArgumentPtr &)>;

  using SimplifyFunctionVector = std::vector<SimplifyFunction>;

  virtual SimplifyFunctionVector getFunctionsForPreSimplify() const;

  virtual SimplifyFunctionVector getFunctionsForPostSimplify() const;

  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

private:
  ArgumentPtr simplifyRec(bool isPostSimplify) const;

protected:
  std::shared_ptr<IFunction> func;

  ArgumentPtr lhsChild;

  ArgumentPtr rhsChild;

private:
  mutable ArgumentPtrVector childrenCached = {{}, {}};
};

template <typename Derived>
class IBinaryExpressionBaseCRTP : public IBinaryExpression {
#define I_EXPRESSION_BASE_CRTP IBinaryExpressionBaseCRTP<Derived>
#include "fintamath/expressions/IExpressionBaseCRTP.hpp"
#undef I_EXPRESSION_BASE_CRTP

public:
  explicit IBinaryExpressionBaseCRTP(const IFunction &inFunc, ArgumentPtr lhs, ArgumentPtr rhs)
      : IBinaryExpression(inFunc, std::move(lhs), std::move(rhs)) {}
};

template <typename Derived>
class IBinaryExpressionCRTP : public IBinaryExpressionBaseCRTP<Derived> {
#define I_EXPRESSION_CRTP IBinaryExpressionCRTP<Derived>
#include "fintamath/expressions/IExpressionCRTP.hpp"
#undef I_EXPRESSION_CRTP

public:
  explicit IBinaryExpressionCRTP(const IFunction &inFunc, ArgumentPtr lhs, ArgumentPtr rhs)
      : IBinaryExpressionBaseCRTP<Derived>(inFunc, std::move(lhs), std::move(rhs)) {}
};

}
