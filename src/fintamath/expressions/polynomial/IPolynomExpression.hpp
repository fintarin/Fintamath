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

class IPolynomExpression : virtual public IExpression {
public:
  std::shared_ptr<IFunction> getFunction() const final;

  ArgumentsPtrVector getChildren() const final;

  // void setPrecision(uint8_t precision) final;

  ArgumentsPtrVector getVariables() const final;

  ArgumentsPtrVector getPolynom() const;

protected:
  virtual std::shared_ptr<IMathObject> preSimplify(size_t lhsChildNum, size_t rhsChildNum) const;

  virtual std::shared_ptr<IMathObject> postSimplify(size_t lhsChildNum, size_t rhsChildNum) const;

  void validate() const final;

  std::shared_ptr<IMathObject> simplify() final;

protected:
  // static void sortVector(ArgumentsPtrVector &vector, std::map<IOperator::Priority, ArgumentsPtrVector> &priorityMap,
  //                        ArgumentsPtrVector &functionVector, ArgumentsPtrVector &variableVector);

  // static void pushPolynomToPolynom(const ArgumentsPtrVector &from, ArgumentsPtrVector &to);

protected:
  std::shared_ptr<IFunction> func;

  ArgumentsPtrVector children;

private:
  void preSimplifyRec();

  void postSimplifyRec();
};

template <typename Derived>
class IPolynomExpressionCRTP : virtual public IExpressionCRTP<Derived>, virtual public IPolynomExpression {
public:
  explicit IPolynomExpressionCRTP(const IFunction &func, const ArgumentsPtrVector &children) {
    this->func = cast<IFunction>(func.clone());

    for (const auto &child : children) {
      addElement(child);
    }
  }

  void addElement(const std::shared_ptr<IMathObject> &element) {
    std::shared_ptr<IMathObject> elem = element;
    compressChild(elem);

    ArgumentsPtrVector elemPolynom;

    if (auto expr = cast<Derived>(elem)) {
      elemPolynom = expr->children;
    }

    if (elemPolynom.empty()) {
      children.emplace_back(elem);
      return;
    }

    for (auto &child : elemPolynom) {
      children.emplace_back(child);
    }
  }
};

}
