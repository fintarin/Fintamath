#pragma once

#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"

#include <stack>

namespace fintamath {

class IPolynomExpression : public IExpression {
public:
  explicit IPolynomExpression(const IFunction &inFunc, ArgumentPtrVector args);

  std::string toString() const override;

  const std::shared_ptr<IFunction> &getFunction() const final;

  const ArgumentPtrVector &getChildren() const final;

  void setChildren(const ArgumentPtrVector &childVect) final;

  static MathObjectType getTypeStatic() {
    return MathObjectType::IPolynomExpression;
  }

protected:
  using SimplifyFunction = std::function<ArgumentPtr(const IFunction &, const ArgumentPtr &, const ArgumentPtr &)>;

  using SimplifyFunctionVector = std::vector<SimplifyFunction>;

  using ExpressionTreePathStack = std::stack<std::pair<const std::shared_ptr<const IExpression>, size_t>>;

  struct ChildrenComparatorResult {
    int postfix = 0;
    int postfixUnary = 0;
    int prefixFirst = 0;
    int prefixLast = 0;
    int prefixVariables = 0;
    int size = 0;
  };

  virtual SimplifyFunctionVector getFunctionsForPreSimplify() const;

  virtual SimplifyFunctionVector getFunctionsForPostSimplify() const;

  virtual std::string childToString(const IOperator &oper, const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const;

  /**
   * @brief
   *
   * @param lhs
   * @param rhs
   * @return -1 if we should swap the arguments
   * @return  1 if we should not swap the arguments
   * @return  0 if this comparator fails
   */
  virtual int comparator(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const;

  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

  virtual bool isTermsOrderInversed() const;

  virtual bool isComparableOrderInversed() const;

private:
  void simplifyRec(bool isPostSimplify);

  void simplifyChildren(bool isPostSimplify);

  void compress();

  void sort();

  /**
   * @brief
   *
   * @param lhs
   * @param rhs
   * @return -1 if we should swap the arguments
   * @return  1 if we should not swap the arguments
   * @return  0 if this comparator fails
   */
  int comparatorNonExpressions(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const;

  /**
   * @brief
   *
   * @param lhs
   * @param rhs
   * @return -1 if we should swap the arguments
   * @return  1 if we should not swap the arguments
   * @return  0 if this comparator fails
   */
  int comparatorPolynoms(const std::shared_ptr<const IPolynomExpression> &lhs,
                         const std::shared_ptr<const IPolynomExpression> &rhs) const;

  /**
   * @brief
   *
   * @param lhs
   * @param rhs
   * @return -1 if we should swap the arguments
   * @return  1 if we should not swap the arguments
   * @return  0 if this comparator fails
   */
  int comparatorPolynomAndNonPolynom(const std::shared_ptr<const IPolynomExpression> &lhs,
                                     const ArgumentPtr &rhs) const;

  /**
   * @brief
   *
   * @param lhs
   * @param rhs
   * @return -1 if we should swap the arguments
   * @return  1 if we should not swap the arguments
   * @return  0 if this comparator fails
   */
  int comparatorExpressionAndNonExpression(const std::shared_ptr<const IExpression> &lhs,
                                           const ArgumentPtr &rhs) const;

  /**
   * @brief
   *
   * @param lhs
   * @param rhs
   * @return -1 if we should swap the arguments
   * @return  1 if we should not swap the arguments
   * @return  0 if this comparator fails
   */
  int comparatorExpressions(const std::shared_ptr<const IExpression> &lhs,
                            const std::shared_ptr<const IExpression> &rhs) const;

  ChildrenComparatorResult comparatorChildren(const ArgumentPtrVector &lhsChildren,
                                              const ArgumentPtrVector &rhsChildren) const;

  /**
   * @brief
   *
   * @param lhsExpr
   * @param rhsExpr
   * @return -1 if we should swap the arguments
   * @return  1 if we should not swap the arguments
   * @return  0 if this comparator fails
   */
  static int comparatorFunctions(const std::shared_ptr<const IFunction> &lhs,
                                 const std::shared_ptr<const IFunction> &rhs);

  int comparatorVariables(const ArgumentPtr &lhs, const ArgumentPtr &rhs, bool isTermsOrderInversed) const;

  static std::shared_ptr<const Variable> getNextVariable(ExpressionTreePathStack &stack);

  static size_t getPositionOfFirstChildWithVariable(const ArgumentPtrVector &children);

  static bool unwrapUnary(ArgumentPtr &lhs);

protected:
  std::shared_ptr<IFunction> func;

  ArgumentPtrVector children;
};

template <typename Derived, bool isMultiFunction = false>
class IPolynomExpressionBaseCRTP : public IPolynomExpression {
#define I_EXPRESSION_BASE_CRTP IPolynomExpressionBaseCRTP<Derived, isMultiFunction>
#include "fintamath/expressions/IExpressionBaseCRTP.hpp"
#undef I_EXPRESSION_BASE_CRTP

public:
  explicit IPolynomExpressionBaseCRTP(const IFunction &inFunc, ArgumentPtrVector args)
      : IPolynomExpression(inFunc, std::move(args)) {}
};

template <typename Derived, bool isMultiFunction = false>
class IPolynomExpressionCRTP : public IPolynomExpressionBaseCRTP<Derived, isMultiFunction> {
#define I_EXPRESSION_CRTP IPolynomExpressionCRTP<Derived, isMultiFunction>
#include "fintamath/expressions/IExpressionCRTP.hpp"
#undef I_EXPRESSION_CRTP

public:
  explicit IPolynomExpressionCRTP(const IFunction &inFunc, ArgumentPtrVector args)
      : IPolynomExpressionBaseCRTP<Derived, isMultiFunction>(inFunc, std::move(args)) {}
};

}
