#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/Parser.hpp"
#include "fintamath/core/Tokenizer.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

namespace detail {

struct Term final {
  Token name;

  std::unique_ptr<IMathObject> value;

public:
  Term() = default;

  Term(std::string inName, std::unique_ptr<IMathObject> inValue)
      : name(std::move(inName)),
        value(std::move(inValue)) {
  }
};

struct FunctionTerm final {
  Term term;

  std::optional<IOperator::Priority> priority;

public:
  FunctionTerm() = default;

  FunctionTerm(Term inTerm, const std::optional<IOperator::Priority> inPriority)
      : term(std::move(inTerm)),
        priority(inPriority) {
  }
};

using TermVector = std::vector<Term>;

using FunctionTermStack = std::stack<FunctionTerm>;

using OperandStack = std::stack<std::unique_ptr<IMathObject>>;

}

class Expression : public IExpressionCRTP<Expression> {
  FINTAMATH_CLASS_BODY(Expression, IExpression)

  using ExpressionConstructor = std::function<std::unique_ptr<IMathObject>(ArgumentPtrVector &&)>;

  using ExpressionMaker = std::unordered_map<MathObjectClass, ExpressionConstructor>;

public:
  Expression();

  explicit Expression(const std::string &str);

  explicit Expression(const ArgumentPtr &obj);

  Expression(const IMathObject &obj);

  Expression(int64_t val);

  std::string toString() const override;

  const std::shared_ptr<IFunction> &getFunction() const override;

  const ArgumentPtrVector &getChildren() const override;

  void setChildren(const ArgumentPtrVector &childVect) override;

  void setVariables(const std::vector<std::pair<Variable, ArgumentPtr>> &varsToVals) override;

  void setVariable(const Variable &var, const Expression &val);

  template <typename Function>
  static void registerExpressionConstructor(ExpressionConstructor constructor);

protected:
  ArgumentPtr simplify() const override;

private:
  void simplifyMutable() const;

  void updateStringMutable() const;

  static detail::TermVector tokensToTerms(detail::TokenVector &tokens);

  static detail::OperandStack termsToOperands(detail::TermVector &terms);

  static std::unique_ptr<IMathObject> operandsToObject(detail::OperandStack &operands);

  static std::unique_ptr<IFunction> parseFunction(const std::string &str, size_t argNum);

  static std::unique_ptr<IOperator> parseOperator(const std::string &str, IOperator::Priority priority);

  static detail::Term parseTerm(const std::string &str);

  static void moveFunctionTermsToOperands(detail::OperandStack &operands, detail::FunctionTermStack &functions, const IOperator *nextOper);

  static void insertMultiplications(detail::TermVector &terms);

  static void fixOperatorTypes(detail::TermVector &terms);

  static void collapseFactorials(detail::TermVector &terms);

  static bool canNextTermBeBinaryOperator(const detail::Term &term);

  static bool canPrevTermBeBinaryOperator(const detail::Term &term);

  static bool isBinaryOperator(const IMathObject *val);

  static bool isPrefixOperator(const IMathObject *val);

  static bool isPostfixOperator(const IMathObject *val);

  static bool isNonOperatorFunction(const IMathObject *val);

  static void validateFunctionArgs(const IFunction &func, const ArgumentPtrVector &args);

  static bool doesArgMatch(const MathObjectClass &expectedType, const ArgumentPtr &arg);

  static ArgumentPtrVector unwrapComma(const ArgumentPtr &child);

  static ArgumentPtr compress(const ArgumentPtr &child);

  friend std::unique_ptr<IMathObject> detail::makeExpr(const IFunction &func, ArgumentPtrVector args);

  friend std::unique_ptr<IMathObject> parseExpr(const std::string &str);

  friend Expression approximate(const Expression &rhs, unsigned precision);

  static ExpressionMaker &getExpressionMaker();

private:
  mutable ArgumentPtr child;

  mutable ArgumentPtrVector childrenCached = {{}};

  mutable std::string stringCached;

  mutable bool isSimplified = false;
};

template <typename Function>
void Expression::registerExpressionConstructor(ExpressionConstructor constructor) {
  getExpressionMaker()[Function::getClassStatic()] = [maker = std::move(constructor)](ArgumentPtrVector &&args) {
    static const size_t funcArgSize = Function{}.getArgumentClasses().size();

    std::unique_ptr<IMathObject> res;

    if constexpr (Function::isVariadicStatic()) {
      res = maker(std::move(args));
    }
    else {
      if (funcArgSize == args.size()) {
        res = maker(std::move(args));
      }
    }

    return res;
  };
}

}
