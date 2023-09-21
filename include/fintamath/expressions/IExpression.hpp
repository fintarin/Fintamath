#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/parser/Parser.hpp"
#include "fintamath/parser/Tokenizer.hpp"

namespace fintamath {

class IExpression : public IArithmetic {
public:
  virtual std::shared_ptr<IFunction> getFunction() const = 0;

  virtual ArgumentsPtrVector getChildren() const = 0;

  virtual void setChildren(const ArgumentsPtrVector &childVect) = 0;

  std::vector<Variable> getVariables() const;

  virtual void setVariables(const std::vector<std::pair<Variable, ArgumentPtr>> &varsToVals);

  std::unique_ptr<IMathObject> toMinimalObject() const final;

  virtual std::shared_ptr<IFunction> getOutputFunction() const;

  template <std::derived_from<IExpression> T>
  static void registerType() {
    Parser::registerType<T>(getParser());
  }

  static std::unique_ptr<IExpression> parse(const std::string &str) {
    return Parser::parse(getParser(), str);
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::IExpression;
  }

protected:
  virtual ArgumentPtr simplify() const;

  virtual ArgumentPtr preSimplify() const;

  virtual ArgumentPtr postSimplify() const;

  virtual ArgumentPtr preciseSimplify() const = 0;

  static void compressChild(ArgumentPtr &child);

  static void simplifyChild(ArgumentPtr &child);

  static void preSimplifyChild(ArgumentPtr &child);

  static void postSimplifyChild(ArgumentPtr &child);

  static void preciseSimplifyChild(ArgumentPtr &child);

  static void constSimplifyChild(ArgumentPtr &child);

  static ArgumentPtr callFunction(const IFunction &func, const ArgumentsPtrVector &argPtrs);

private:
  static Parser::Vector<std::unique_ptr<IExpression>, const std::string &> &getParser();
};

template <typename Derived, bool isMultiFunction = false>
class IExpressionBaseCRTP : public IExpression {
#define I_EXPRESSION_BASE_CRTP IExpressionBaseCRTP<Derived, isMultiFunction>
#include "fintamath/expressions/IExpressionBaseCRTP.hpp"
#undef I_EXPRESSION_BASE_CRTP
};

template <typename Derived, bool isMultiFunction = false>
class IExpressionCRTP : public IExpressionBaseCRTP<Derived, isMultiFunction> {
#define I_EXPRESSION_CRTP IExpressionCRTP<Derived, isMultiFunction>
#include "fintamath/expressions/IExpressionCRTP.hpp"
#undef I_EXPRESSION_CRTP
};

}
