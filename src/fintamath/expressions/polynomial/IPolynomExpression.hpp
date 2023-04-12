#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IPolynomExpression : virtual public IExpression {
public:
  shared_ptr<IFunction> getFunction() const final;

  ArgumentsPtrVector getChildren() const final;

  string toString() const final;

  ArgumentsPtrVector getVariables() const final;

  ArgumentsPtrVector getPolynom() const;

  virtual void addElement(const ArgumentPtr &element) = 0;

protected:
  using FunctionsVector =
      std::vector<std::function<ArgumentPtr(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild)>>;

  virtual ArgumentPtr preSimplify(size_t lhsChildNum, size_t rhsChildNum) const;

  virtual ArgumentPtr postSimplify(size_t lhsChildNum, size_t rhsChildNum) const;

  ArgumentPtr simplify() const final;

  virtual FunctionsVector getSimplifyFunctions() const;

  virtual string childToString(const ArgumentPtr &child, bool isFirst = false) const;

  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

  virtual bool comparator(const ArgumentPtr &left, const ArgumentPtr &right) const;

  virtual bool operatorComparator(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const;

  virtual bool literalComparator(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const;

  virtual bool powComparator(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const;

  virtual bool functionComparator(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const;

  virtual void postSortProcessing();

protected:
  shared_ptr<IFunction> func;

  ArgumentsPtrVector children;

private:
  void preSimplifyRec();

  void postSimplifyRec();

  void globalSimplifyRec();

  void sort();
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
