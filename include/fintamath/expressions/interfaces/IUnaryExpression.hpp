#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IUnaryExpression : public IExpression {
public:
  std::string toString() const override;

  std::shared_ptr<IFunction> getFunction() const final;

  ArgumentPtrVector getChildren() const override;

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

  ArgumentPtr preciseSimplify() const override;

private:
  ArgumentPtr useSimplifyFunctions(const SimplifyFunctionVector &simplFuncs) const;

protected:
  std::shared_ptr<IFunction> func;

  ArgumentPtr child;
};

template <typename Derived, bool isMultiFunction = false>
class IUnaryExpressionBaseCRTP : public IUnaryExpression {
#define I_EXPRESSION_BASE_CRTP IUnaryExpressionBaseCRTP<Derived, isMultiFunction>
#include "fintamath/expressions/IExpressionBaseCRTP.hpp"
#undef I_EXPRESSION_BASE_CRTP
};

template <typename Derived, bool isMultiFunction = false>
class IUnaryExpressionCRTP : public IUnaryExpressionBaseCRTP<Derived, isMultiFunction> {
#define I_EXPRESSION_CRTP IUnaryExpressionCRTP<Derived, isMultiFunction>
#include "fintamath/expressions/IExpressionCRTP.hpp"
#undef I_EXPRESSION_CRTP

public:
  explicit IUnaryExpressionCRTP(const IFunction &inFunc, const ArgumentPtr &arg) {
    this->func = cast<IFunction>(inFunc.clone());

    this->child = arg;
    this->compressChild(this->child);
  }
};

}
