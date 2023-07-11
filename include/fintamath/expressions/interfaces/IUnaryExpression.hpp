#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IUnaryExpression : public IExpression {
public:
  std::string toString() const override;

  std::shared_ptr<IFunction> getFunction() const final;

  ArgumentsPtrVector getChildren() const override;

  void setChildren(const ArgumentsPtrVector &childVect) override;

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::IUnaryExpression);
  }

protected:
  using SimplifyFunction = std::function<ArgumentPtr(const IFunction &, const ArgumentPtr &)>;

  using SimplifyFunctionsVector = std::vector<SimplifyFunction>;

  virtual SimplifyFunctionsVector getFunctionsForPreSimplify() const;

  virtual SimplifyFunctionsVector getFunctionsForPostSimplify() const;

  ArgumentPtr simplify() const final;

  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

  ArgumentPtr preciseSimplify() const override;

private:
  ArgumentPtr useSimplifyFunctions(const SimplifyFunctionsVector &simplFuncs) const;

protected:
  std::shared_ptr<IFunction> func;

  ArgumentPtr child;
};

template <typename Derived, bool isMultiFunction = false>
class IUnaryExpressionBaseCRTP : public IUnaryExpression {
#define FINTAMATH_I_EXPRESSION_BASE_CRTP IUnaryExpressionBaseCRTP<Derived, isMultiFunction>
#include "fintamath/expressions/IExpressionBaseCRTP.hpp"
#undef FINTAMATH_I_EXPRESSION_BASE_CRTP
};

template <typename Derived, bool isMultiFunction = false>
class IUnaryExpressionCRTP : public IUnaryExpressionBaseCRTP<Derived, isMultiFunction> {
#define FINTAMATH_I_EXPRESSION_CRTP IUnaryExpressionCRTP<Derived, isMultiFunction>
#include "fintamath/expressions/IExpressionCRTP.hpp"
#undef FINTAMATH_I_EXPRESSION_CRTP

public:
  explicit IUnaryExpressionCRTP(const IFunction &inFunc, const ArgumentPtr &inChild) {
    this->func = cast<IFunction>(inFunc.clone());

    this->child = inChild;
    this->compressChild(this->child);
  }
};

}
