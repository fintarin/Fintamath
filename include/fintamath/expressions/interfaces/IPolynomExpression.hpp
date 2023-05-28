#pragma once

#include "fintamath/expressions/IExpression.hpp"
#include <stack>

namespace fintamath {

class IPolynomExpression : public IExpression {
public:
  std::string toString() const final;

  std::shared_ptr<IFunction> getFunction() const final;

  ArgumentsPtrVector getChildren() const final;

  void setChildren(const ArgumentsPtrVector &childVect) final;

  virtual void addElement(const ArgumentPtr &element) = 0;

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::IPolynomExpression);
  }

protected:
  using SimplifyFunction =
      std::function<ArgumentPtr(const IFunction &, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild)>;

  using SimplifyFunctionsVector = std::vector<SimplifyFunction>;

  using ExprTreePathStack = std::stack<std::pair<const std::shared_ptr<const IExpression>, size_t>>;

  virtual SimplifyFunctionsVector getFunctionsForSimplify() const;

  virtual SimplifyFunctionsVector getFunctionsForPreSimplify() const;

  virtual SimplifyFunctionsVector getFunctionsForPostSimplify() const;

  virtual std::string operatorChildToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const;

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

  ArgumentPtr simplify() const final;

  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

  virtual bool isTermsOrderInversed() const;

  virtual bool isComparableOrderInversed() const;

private:
  void preSimplifyRec();

  void postSimplifyRec();

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

  /**
   * @brief
   *
   * @param lhsChildren
   * @param rhsChildren
   * @return -1 if we should swap the arguments
   * @return  1 if we should not swap the arguments
   * @return  0 if this comparator fails
   */
  int comparatorChildren(const ArgumentsPtrVector &lhsChildren, const ArgumentsPtrVector &rhsChildren,
                         bool ignoreUnaryIfPossible) const;

  int comparatorFunctionChildren(const ArgumentsPtrVector &lhsChildren, const ArgumentsPtrVector &rhsChildren) const;

  int comparatorVariables(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const;
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

  // static ArgumentPtr findFirstPolynomChild(const ArgumentPtr &rhs);

  std::shared_ptr<const Variable> getNextVar(ExprTreePathStack &stack) const;

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
  explicit IPolynomExpressionCRTP(const IFunction &inFunc, const ArgumentsPtrVector &inChildren) {
    this->func = cast<IFunction>(inFunc.clone());

    for (const auto &child : inChildren) {
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
