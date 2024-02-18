#pragma once

#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class IUnaryExpression : public IExpression {
public:
  explicit IUnaryExpression(const IFunction &inFunc, ArgumentPtr rhs);

  std::string toString() const override;

  const std::shared_ptr<IFunction> &getFunction() const final;

  const ArgumentPtrVector &getChildren() const override;

  void setChildren(const ArgumentPtrVector &childVect) override;

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::IUnaryExpression, "IUnaryExpression"};
  }

protected:
  using SimplifyFunction = std::function<ArgumentPtr(const IFunction &, const ArgumentPtr &)>;

  using SimplifyFunctionVector = std::vector<SimplifyFunction>;

  virtual SimplifyFunctionVector getFunctionsForPreSimplify() const;

  virtual SimplifyFunctionVector getFunctionsForPostSimplify() const;

  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

protected:
  std::shared_ptr<IFunction> func;

  ArgumentPtr child;

private:
  ArgumentPtr simplifyRec(bool isPostSimplify) const;

private:
  mutable ArgumentPtrVector childrenCached = {{}};
};

template <typename Derived>
class IUnaryExpressionBaseCRTP : public IUnaryExpression {
#define I_EXPRESSION_BASE_CRTP IUnaryExpressionBaseCRTP<Derived>
#include "fintamath/expressions/IExpressionBaseCRTP.hpp"
#undef I_EXPRESSION_BASE_CRTP

public:
  explicit IUnaryExpressionBaseCRTP(const IFunction &inFunc, ArgumentPtr rhs)
      : IUnaryExpression(inFunc, std::move(rhs)) {}
};

template <typename Derived>
class IUnaryExpressionCRTP : public IUnaryExpressionBaseCRTP<Derived> {
#define I_EXPRESSION_CRTP IUnaryExpressionCRTP<Derived>
#include "fintamath/expressions/IExpressionCRTP.hpp"
#undef I_EXPRESSION_CRTP

public:
  explicit IUnaryExpressionCRTP(const IFunction &inFunc, ArgumentPtr rhs)
      : IUnaryExpressionBaseCRTP<Derived>(inFunc, std::move(rhs)) {}
};

}
