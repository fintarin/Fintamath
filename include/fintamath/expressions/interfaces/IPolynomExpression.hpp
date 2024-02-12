#pragma once

#include <compare>
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

class IOperator;

class IPolynomExpression : public IExpression {
public:
  explicit IPolynomExpression(const IFunction &inFunc, ArgumentPtrVector args);

  std::string toString() const override;

  const std::shared_ptr<IFunction> &getFunction() const final;

  const ArgumentPtrVector &getChildren() const final;

  void setChildren(const ArgumentPtrVector &childVect) final;

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::IPolynomExpression;
  }

protected:
  using SimplifyFunction = std::function<ArgumentPtr(const IFunction &, const ArgumentPtr &, const ArgumentPtr &)>;

  using SimplifyFunctionVector = std::vector<SimplifyFunction>;

  virtual SimplifyFunctionVector getFunctionsForPreSimplify() const;

  virtual SimplifyFunctionVector getFunctionsForPostSimplify() const;

  virtual std::string childToString(const IOperator &oper, const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const;

  virtual std::strong_ordering compare(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const;

  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

  virtual bool isConstantGreaterThanVariable() const;

  virtual bool isComparableOrderInversed() const;

private:
  void simplifyRec(bool isPostSimplify);

  void simplifyChildren(bool isPostSimplify);

  void compress();

  void sort();

protected:
  std::shared_ptr<IFunction> func;

  ArgumentPtrVector children;
};

template <typename Derived>
class IPolynomExpressionBaseCRTP : public IPolynomExpression {
#define I_EXPRESSION_BASE_CRTP IPolynomExpressionBaseCRTP<Derived>
#include "fintamath/expressions/IExpressionBaseCRTP.hpp"
#undef I_EXPRESSION_BASE_CRTP

public:
  explicit IPolynomExpressionBaseCRTP(const IFunction &inFunc, ArgumentPtrVector args)
      : IPolynomExpression(inFunc, std::move(args)) {}
};

template <typename Derived>
class IPolynomExpressionCRTP : public IPolynomExpressionBaseCRTP<Derived> {
#define I_EXPRESSION_CRTP IPolynomExpressionCRTP<Derived>
#include "fintamath/expressions/IExpressionCRTP.hpp"
#undef I_EXPRESSION_CRTP

public:
  explicit IPolynomExpressionCRTP(const IFunction &inFunc, ArgumentPtrVector args)
      : IPolynomExpressionBaseCRTP<Derived>(inFunc, std::move(args)) {}
};

}
