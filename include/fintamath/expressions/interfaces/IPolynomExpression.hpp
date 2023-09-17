#pragma once

#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"

#include <stack>

namespace fintamath {

class IPolynomExpression : public IExpression {
public:
  std::string toString() const override;

  std::shared_ptr<IFunction> getFunction() const final;

  ArgumentsPtrVector getChildren() const final;

  void setChildren(const ArgumentsPtrVector &childVect) final;

  virtual void addElement(const ArgumentPtr &element) = 0;

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::IPolynomExpression);
  }

protected:
  using SimplifyFunction = std::function<ArgumentPtr(const IFunction &, const ArgumentPtr &, const ArgumentPtr &)>;

  using SimplifyFunctionsVector = std::vector<SimplifyFunction>;

  using ExprTreePathStack = std::stack<std::pair<const std::shared_ptr<const IExpression>, size_t>>;

  struct ChildrenComparatorResult {
    int postfix = 0;
    int postfixUnary = 0;
    int prefixFirst = 0;
    int prefixLast = 0;
    int prefixVariables = 0;
    int size = 0;
  };

  virtual SimplifyFunctionsVector getFunctionsForPreSimplify() const;

  virtual SimplifyFunctionsVector getFunctionsForPostSimplify() const;

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

  ArgumentPtr preciseSimplify() const override;

  virtual bool isTermsOrderInversed() const;

  virtual bool isComparableOrderInversed() const;

private:
  void simplifyRec(bool isPostSimplify);

  void simplifyChildren(bool isPostSimplify);

  ArgumentPtr useSimplifyFunctions(const SimplifyFunctionsVector &simplFuncs, size_t lhsChildPos,
                                   size_t rhsChildPos) const;

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
  int comparatorExpressionAndNonExpression(const std::shared_ptr<const IExpression> &lhs, const ArgumentPtr &rhs) const;

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

  ChildrenComparatorResult comparatorChildren(const ArgumentsPtrVector &lhsChildren,
                                              const ArgumentsPtrVector &rhsChildren) const;

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

  static std::shared_ptr<const Variable> getNextVariable(ExprTreePathStack &stack);

  static size_t getPositionOfFirstChildWithVariable(const ArgumentsPtrVector &children);

  static bool unwrapUnary(ArgumentPtr &lhs);

protected:
  std::shared_ptr<IFunction> func;

  ArgumentsPtrVector children;
};

template <typename Derived, bool isMultiFunction = false>
class IPolynomExpressionBaseCRTP : public IPolynomExpression {
#define FINTAMATH_I_EXPRESSION_BASE_CRTP IPolynomExpressionBaseCRTP<Derived, isMultiFunction>
#include "fintamath/expressions/IExpressionBaseCRTP.hpp"
#undef FINTAMATH_I_EXPRESSION_BASE_CRTP
};

template <typename Derived, bool isMultiFunction = false>
class IPolynomExpressionCRTP : public IPolynomExpressionBaseCRTP<Derived, isMultiFunction> {
#define FINTAMATH_I_EXPRESSION_CRTP IPolynomExpressionCRTP<Derived, isMultiFunction>
#include "fintamath/expressions/IExpressionCRTP.hpp"
#undef FINTAMATH_I_EXPRESSION_CRTP

public:
  explicit IPolynomExpressionCRTP(const IFunction &inFunc, const ArgumentsPtrVector &args) {
    this->func = cast<IFunction>(inFunc.clone());

    for (const auto &child : args) {
      addElement(child);
    }
  }

  void addElement(const ArgumentPtr &element) final {
    ArgumentPtr elem = element;
    this->compressChild(elem);

    ArgumentsPtrVector elemPolynom;

    if (auto expr = cast<Derived>(elem)) {
      elemPolynom = expr->children;
    }

    if (!elemPolynom.empty()) {
      for (auto &child : elemPolynom) {
        this->children.emplace_back(child);
      }
    }
    else {
      this->children.emplace_back(elem);
    }
  }
};

}
