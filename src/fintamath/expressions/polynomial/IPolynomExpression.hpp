#pragma once

#include "fintamath/expressions/Expression.hpp" // TODO: remove
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include <type_traits>

namespace fintamath {

class IPolynomExpression : virtual public IExpression, public std::enable_shared_from_this<IPolynomExpression> {
public:
  IPolynomExpression(const IPolynomExpression &rhs);

  explicit IPolynomExpression(IPolynomExpression &&rhs) = default;

  IPolynomExpression &operator=(const IPolynomExpression &rhs);

  IPolynomExpression &operator=(IPolynomExpression &&rhs) noexcept = default;

  explicit IPolynomExpression(const IFunction &func, ArgumentsPtrVector children);

  std::shared_ptr<IFunction> getFunction() const final;

  // TODO: implement iterator & remove this
  const ArgumentsPtrVector &getArgumentsPtrVector() const;

  void setPrecision(uint8_t precision) final;

  ArgumentsPtrVector getVariables() const final;

  ArgumentsPtrVector getPolynom() const;

protected:
  std::shared_ptr<IMathObject> simplify() final;

  virtual std::shared_ptr<IMathObject> simplifyChildren(const std::shared_ptr<IMathObject> &lhsChild,
                                                        const std::shared_ptr<IMathObject> &rhsChild) = 0;

  void validate() const final;

protected:
  static void sortVector(ArgumentsPtrVector &vector, std::map<IOperator::Priority, ArgumentsPtrVector> &priorityMap,
                         ArgumentsPtrVector &functionVector, ArgumentsPtrVector &variableVector);

  static void pushPolynomToPolynom(const ArgumentsPtrVector &from, ArgumentsPtrVector &to);

protected:
  std::shared_ptr<IFunction> func;

  ArgumentsPtrVector children;

private:
  std::shared_ptr<IMathObject> simplifyRec();
};

template <typename Derived>
class IPolynomExpressionCRTP : virtual public IExpressionCRTP<Derived>, virtual public IPolynomExpression {
public:
  void addElement(const std::shared_ptr<IMathObject> &elem) {
    ArgumentsPtrVector elemPolynom;

    if (auto expr = cast<Derived>(elem)) {
      elemPolynom = expr->children;
    } else if (auto expr = cast<Expression>(elem)) {
      addElement(expr->getChild());
      return;
    }

    if (elemPolynom.empty()) {
      children.emplace_back(elem);
      return;
    }

    for (auto &child : elemPolynom) {
      children.emplace_back(child);
    }
  }

protected:
  void compress() final {
    for (auto &child : children) {
      if (auto expr = cast<Expression>(child)) {
        child = expr->getChild();
      }
    }
  }
};

}
