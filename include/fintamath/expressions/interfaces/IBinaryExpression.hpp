#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IBinaryExpression : public IExpression {
public:
  explicit IBinaryExpression(const IFunction &inFunc, ArgumentPtr lhs, ArgumentPtr rhs);

  std::string toString() const override;

  const std::shared_ptr<IFunction> &getFunction() const final;

  const ArgumentPtrVector &getChildren() const final;

  void setChildren(const ArgumentPtrVector &childVect) final;

  static MathObjectType getTypeStatic() {
    return MathObjectType::IBinaryExpression;
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

template <typename Derived, bool isMultiFunction = false>
class IBinaryExpressionBaseCRTP : public IBinaryExpression {
#define I_EXPRESSION_BASE_CRTP IBinaryExpressionBaseCRTP<Derived, isMultiFunction>
#include "fintamath/expressions/IExpressionBaseCRTP.hpp"
#undef I_EXPRESSION_BASE_CRTP

public:
  explicit IBinaryExpressionBaseCRTP(const IFunction &inFunc, ArgumentPtr lhs, ArgumentPtr rhs)
      : IBinaryExpression(inFunc, std::move(lhs), std::move(rhs)) {}
};

template <typename Derived, bool isMultiFunction = false>
class IBinaryExpressionCRTP : public IBinaryExpressionBaseCRTP<Derived, isMultiFunction> {
#define I_EXPRESSION_CRTP IBinaryExpressionCRTP<Derived, isMultiFunction>
#include "fintamath/expressions/IExpressionCRTP.hpp"
#undef I_EXPRESSION_CRTP

public:
  explicit IBinaryExpressionCRTP(const IFunction &inFunc, ArgumentPtr lhs, ArgumentPtr rhs)
      : IBinaryExpressionBaseCRTP<Derived, isMultiFunction>(inFunc, std::move(lhs), std::move(rhs)) {}
};

}
