#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IUnaryExpression : public IExpression {
public:
  explicit IUnaryExpression(const IFunction &inFunc, ArgumentPtr rhs);

  std::string toString() const override;

  const std::shared_ptr<IFunction> &getFunction() const final;

  const ArgumentPtrVector &getChildren() const override;

  void setChildren(const ArgumentPtrVector &childVect) override;

  static MathObjectType getTypeStatic() {
    return MathObjectType::IUnaryExpression;
  }

protected:
  using SimplifyFunction = std::function<ArgumentPtr(const IFunction &, const ArgumentPtr &)>;

  using SimplifyFunctionVector = std::vector<SimplifyFunction>;

  virtual SimplifyFunctionVector getFunctionsForPreSimplify() const;

  virtual SimplifyFunctionVector getFunctionsForPostSimplify() const;

  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

private:
  ArgumentPtr useSimplifyFunctions(const SimplifyFunctionVector &simplFuncs) const;

protected:
  std::shared_ptr<IFunction> func;

  ArgumentPtr child;

private:
  mutable ArgumentPtrVector childrenCached = {{}};
};

template <typename Derived, bool isMultiFunction = false>
class IUnaryExpressionBaseCRTP : public IUnaryExpression {
#define I_EXPRESSION_BASE_CRTP IUnaryExpressionBaseCRTP<Derived, isMultiFunction>
#include "fintamath/expressions/IExpressionBaseCRTP.hpp"
#undef I_EXPRESSION_BASE_CRTP

public:
  explicit IUnaryExpressionBaseCRTP(const IFunction &inFunc, ArgumentPtr rhs)
      : IUnaryExpression(inFunc, std::move(rhs)) {}
};

template <typename Derived, bool isMultiFunction = false>
class IUnaryExpressionCRTP : public IUnaryExpressionBaseCRTP<Derived, isMultiFunction> {
#define I_EXPRESSION_CRTP IUnaryExpressionCRTP<Derived, isMultiFunction>
#include "fintamath/expressions/IExpressionCRTP.hpp"
#undef I_EXPRESSION_CRTP

public:
  explicit IUnaryExpressionCRTP(const IFunction &inFunc, ArgumentPtr rhs)
      : IUnaryExpressionBaseCRTP<Derived, isMultiFunction>(inFunc, std::move(rhs)) {}
};

}
