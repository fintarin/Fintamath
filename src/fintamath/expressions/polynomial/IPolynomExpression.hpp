#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IPolynomExpression : virtual public IExpression {
public:
  shared_ptr<IFunction> getFunction() const final;

  ArgumentsPtrVector getChildren() const final;

  // void setPrecision(uint8_t precision) final;

  ArgumentsPtrVector getVariables() const final;

  ArgumentsPtrVector getPolynom() const;

  virtual void addElement(const ArgumentPtr &element) = 0;

protected:
  virtual ArgumentPtr preSimplify(size_t lhsChildNum, size_t rhsChildNum) const;

  virtual ArgumentPtr postSimplify(size_t lhsChildNum, size_t rhsChildNum) const;

  ArgumentPtr simplify() const final;

  ArgumentPtr coefficientsProcessing(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) const;

  virtual std::pair<ArgumentPtr, ArgumentPtr> getRateAndValue(const ArgumentPtr &rhsChild) const;

  virtual ArgumentPtr addRateToValue(const ArgumentsPtrVector &rate, const ArgumentPtr &value) const;

protected:
  // static void sortVector(ArgumentsPtrVector &vector, map<IOperator::Priority, ArgumentsPtrVector> &priorityMap,
  //                        ArgumentsPtrVector &functionVector, ArgumentsPtrVector &variableVector);

  // static void pushPolynomToPolynom(const ArgumentsPtrVector &from, ArgumentsPtrVector &to);

protected:
  shared_ptr<IFunction> func;

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

  void addElement(const ArgumentPtr &element) final {
    ArgumentPtr elem = element;
    compressChild(elem);

    ArgumentsPtrVector elemPolynom;

    if (auto expr = cast<Derived>(elem)) {
      elemPolynom = expr->children;
    }

    if (!elemPolynom.empty()) {
      for (auto &child : elemPolynom) {
        children.emplace_back(child);
      }
    }
    else {
      children.emplace_back(elem);
    }
  }
};

}
