#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/core/Parser.hpp"
#include "fintamath/core/Tokenizer.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

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

using TermVector = std::vector<std::unique_ptr<Term>>;
using OperandStack = std::stack<std::unique_ptr<IMathObject>>;

class Expression final : public IExpressionCRTP<Expression> {
  using TermParser = Parser<std::unique_ptr<Term>>;
  using ExpressionParser = Parser<std::unique_ptr<IMathObject>, ArgumentPtrVector &&>;
  using ExpressionMaker = std::function<std::unique_ptr<IMathObject>(ArgumentPtrVector &&)>;

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

  static void registerTermParser(TermParser::Constructor constructor) {
    getTermParser().registerConstructor(std::move(constructor));
  }

  template <typename Function, bool isPolynomial = false>
  static void registerFunctionExpressionMaker(ExpressionMaker maker);

  static MathObjectType getTypeStatic() {
    return MathObjectType::Expression;
  }

protected:
  Expression &add(const Expression &rhs) override;

  Expression &substract(const Expression &rhs) override;

  Expression &multiply(const Expression &rhs) override;

  Expression &divide(const Expression &rhs) override;

  Expression &negate() override;

  ArgumentPtr simplify() const override;

private:
  void simplifyMutable() const;

  void updateStringMutable() const;

  static TermVector tokensToTerms(const TokenVector &tokens);

  static OperandStack termsToOperands(TermVector &terms);

  static std::unique_ptr<IMathObject> operandsToObject(OperandStack &operands);

  static ArgumentPtrVector unwrapComma(const ArgumentPtr &child);

  static void insertMultiplications(TermVector &terms);

  static void fixOperatorTypes(TermVector &terms);

  static void collapseFactorials(TermVector &terms);

  static bool canNextTermBeBinaryOperator(const Term &term);

  static bool canPrevTermBeBinaryOperator(const Term &term);

  static bool isBinaryOperator(const IMathObject *val);

  static bool isPrefixOperator(const IMathObject *val);

  static bool isPostfixOperator(const IMathObject *val);

  static bool isNonOperatorFunction(const IMathObject *val);

  static void validateFunctionArgs(const IFunction &func, const ArgumentPtrVector &args);

  static bool doesArgMatch(const MathObjectType &expectedType, const ArgumentPtr &arg);

  static ArgumentPtr compress(const ArgumentPtr &child);

  friend std::unique_ptr<IMathObject> makeExpr(const IFunction &func, ArgumentPtrVector args);

  friend std::unique_ptr<IMathObject> parseFintamath(const std::string &str);

  friend Expression approximate(const Expression &rhs, unsigned precision);

  static TermParser &getTermParser();

  static ExpressionParser &getExpressionParser();

private:
  mutable ArgumentPtr child;

  mutable ArgumentPtrVector childrenCached = {{}};

  mutable std::string stringCached;

  mutable bool isSimplified = false;
};

Expression operator+(const Variable &lhs, const Variable &rhs);

Expression operator+(const Expression &lhs, const Variable &rhs);

Expression operator+(const Variable &lhs, const Expression &rhs);

Expression operator-(const Variable &lhs, const Variable &rhs);

Expression operator-(const Expression &lhs, const Variable &rhs);

Expression operator-(const Variable &lhs, const Expression &rhs);

Expression operator*(const Variable &lhs, const Variable &rhs);

Expression operator*(const Expression &lhs, const Variable &rhs);

Expression operator*(const Variable &lhs, const Expression &rhs);

Expression operator/(const Variable &lhs, const Variable &rhs);

Expression operator/(const Expression &lhs, const Variable &rhs);

Expression operator/(const Variable &lhs, const Expression &rhs);

template <typename Function, bool isPolynomial>
void Expression::registerFunctionExpressionMaker(ExpressionMaker maker) {
  ExpressionParser::TypeConstructor constructor = [maker = std::move(maker)](ArgumentPtrVector &&args) {
    static const IFunction::Type type = Function{}.getFunctionType();
    std::unique_ptr<IMathObject> res;

    if constexpr (IsFunctionTypeAny<Function>::value) {
      res = maker(std::move(args));
    }
    else if constexpr (isPolynomial) {
      if (static_cast<size_t>(type) <= args.size()) {
        res = maker(std::move(args));
      }
    }
    else {
      if (static_cast<size_t>(type) == args.size()) {
        res = maker(std::move(args));
      }
    }

    return res;
  };

  getExpressionParser().registerType<Function>(std::move(constructor));
}

}
