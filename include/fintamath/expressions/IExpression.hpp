#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/parser/Parser.hpp"
#include "fintamath/parser/Tokenizer.hpp"

namespace fintamath {

class IExpression : virtual public IMathObject {
public:
  virtual shared_ptr<IFunction> getFunction() const = 0;

  virtual ArgumentsPtrVector getChildren() const = 0;

  virtual ArgumentsPtrVector getVariables() const;

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IExpression, T>>>
  static void registerType() {
    Parser::registerType<T>(parserVector);
  }

  static unique_ptr<IExpression> parse(const string &str) {
    return Parser::parse(parserVector, str);
  }

protected:
  static void compressChild(ArgumentPtr &child);

  static void simplifyChild(ArgumentPtr &child);

  static void preSimplifyChild(ArgumentPtr &child);

  static void postSimplifyChild(ArgumentPtr &child);

  static ArgumentPtr callFunction(const IFunction &func, const ArgumentsPtrVector &argPtrs);

  virtual ArgumentPtr postSimplify() const;

  virtual ArgumentPtr preSimplify() const;

  virtual ArgumentPtr simplify() const = 0;

private:
  static void simplifyConstant(ArgumentPtr &child);

private:
  static Parser::Vector<unique_ptr<IExpression>, const string &> parserVector;
};

template <typename Derived>
class IExpressionCRTP : virtual public IMathObjectCRTP<Derived>, virtual public IExpression {
public:
  bool equals(const Derived &rhs) const override {
    ArgumentsPtrVector lhsChildren = getChildren();
    ArgumentsPtrVector rhsChildren = rhs.getChildren();

    if (lhsChildren.size() != rhsChildren.size()) {
      return false;
    }

    for (size_t i = 0; i < lhsChildren.size(); i++) {
      if (lhsChildren[i] != rhsChildren[i] || *lhsChildren[i] != *rhsChildren[i]) {
        return false;
      }
    }

    return true;
  }
};

}
