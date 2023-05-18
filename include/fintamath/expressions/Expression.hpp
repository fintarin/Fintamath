#pragma once

#include "fintamath/core/CoreConstants.hpp"
#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

struct Term {
  Token name;

  ArgumentsPtrVector values;

public:
  Term() = default;

  Term(std::string inName, ArgumentsPtrVector inValues) : name(std::move(inName)), values(std::move(inValues)) {
  }
};

using TermVector = std::vector<std::shared_ptr<Term>>;

class Expression : public IExpressionCRTP<Expression> {
public:
  Expression();

  explicit Expression(const std::string &str);

  explicit Expression(const ArgumentPtr &obj);

  Expression(const IMathObject &obj);

  Expression(int64_t val);

  std::string toString() const override;

  Expression precise(uint8_t precision = FINTAMATH_PRECISION) const;

  std::shared_ptr<IFunction> getFunction() const override;

  ArgumentsPtrVector getChildren() const override;

  void setChildren(const ArgumentsPtrVector &childVect) override;

  void setValuesOfVariables(const std::vector<Variable> &vars, const ArgumentsPtrVector &vals) override;

  static void registerTermsMaker(Parser::Function<std::shared_ptr<Term>, const Token &> &&maker) {
    Parser::add<Token>(getTermMakers(), std::move(maker));
  }

  template <typename Function, bool isPolynomial = false, typename Maker>
  static void registerFunctionExpressionMaker(Maker &&maker) {
    Parser::Function<std::shared_ptr<IExpression>, const ArgumentsPtrVector &> constructor =
        [maker = std::forward<Maker>(maker)](const ArgumentsPtrVector &args) -> std::shared_ptr<IExpression> {
      static const IFunction::Type type = Function().getFunctionType();
      std::shared_ptr<IExpression> res;

      if constexpr (IsFunctionTypeAny<Function>::value) {
        res = maker(args);
      }
      else if constexpr (isPolynomial) {
        if (uint16_t(type) <= args.size()) {
          res = maker(args);
        }
      }
      else {
        if (size_t(type) == args.size()) {
          res = maker(args);
        }
      }

      return res;
    };

    Parser::add<Function>(getExpressionMakers(), std::move(constructor));
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Expression);
  }

protected:
  Expression &add(const Expression &rhs) override;

  Expression &substract(const Expression &rhs) override;

  Expression &multiply(const Expression &rhs) override;

  Expression &divide(const Expression &rhs) override;

  Expression &negate() override;

  ArgumentPtr simplify() const override;

private:
  explicit Expression(const TermVector &terms);

  explicit Expression(const TermVector &terms, size_t start, size_t end);

  bool parseBinaryOperator(const TermVector &terms, size_t start, size_t end);

  bool parsePrefixOperator(const TermVector &terms, size_t start, size_t end);

  bool parsePostfixOperator(const TermVector &terms, size_t start, size_t end);

  bool parseFunction(const TermVector &terms, size_t start, size_t end);

  bool parseBrackets(const TermVector &terms, size_t start, size_t end);

  bool parseFiniteTerm(const TermVector &terms, size_t start, size_t end);

  static ArgumentsPtrVector parseFunctionArgs(const TermVector &terms, size_t start, size_t end);

  static TermVector tokensToTerms(const TokenVector &tokens);

  static void insertDelimiters(TermVector &terms);

  static bool skipBrackets(const TermVector &terms, size_t &openBracketIndex);

  static void cutBrackets(const TermVector &terms, size_t &start, size_t &end);

  static std::string termsToString(const TermVector &terms);

  static bool isBinaryOperator(const ArgumentPtr &val);

  static bool isPrefixOperator(const ArgumentPtr &val);

  static bool isPostfixOperator(const ArgumentPtr &val);

  static bool isNonOperatorFunction(const ArgumentPtr &val);

  static void validateChild(const ArgumentPtr &inChild);

  static void validateFunctionArgs(const std::shared_ptr<IFunction> &func, const ArgumentsPtrVector &args);

  static ArgumentPtr preciseRec(const ArgumentPtr &arg, uint8_t precision, bool shouldSimplify);

  static ArgumentPtr preciseExpressionRec(const std::shared_ptr<const IExpression> &expr, uint8_t precision,
                                          bool shouldSimplify);

  friend std::unique_ptr<IMathObject> makeExprChecked(const IFunction &func, const ArgumentsRefVector &args);

  friend std::shared_ptr<IExpression> makeExpr(const IFunction &func, const ArgumentsPtrVector &args);

  static Parser::Vector<std::shared_ptr<Term>, const Token &> &getTermMakers();

  static Parser::Map<std::shared_ptr<IExpression>, const ArgumentsPtrVector &> &getExpressionMakers();

  template <typename Predicate>
  static ArgumentPtr getTermValueIf(const Term &term, Predicate &&predicate) {
    for (const auto &val : term.values) {
      if (predicate(val)) {
        return val;
      }
    }

    return {};
  }

private:
  ArgumentPtr child;
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

}
