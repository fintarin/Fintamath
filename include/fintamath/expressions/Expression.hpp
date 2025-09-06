#pragma once

#include <optional>
#include <stack>
#include <variant>

#include "fintamath/core/ClassBody.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/Tokenizer.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Expression : public IMathObject {
  FINTAMATH_CLASS_BODY(Expression, IMathObject)

public:
  using Argument = IFunction::Argument;
  using Arguments = IFunction::Arguments;

  struct FunctionTerm {
    std::reference_wrapper<const IFunction::FunctionMakers> functionMakers;
    std::optional<IFunction::OperatorPriority> operatorPriority;
  };

  using Term = std::variant<Argument, FunctionTerm>;

  struct TokenToFunctionTerm {
    detail::Token token;
    std::optional<FunctionTerm> term;
  };

  struct TokenToTerm {
    detail::Token token;
    std::optional<Term> term;
  };

  using TokenToTermVector = std::vector<TokenToTerm>;
  using FunctionTermStack = std::stack<std::optional<FunctionTerm>>;
  using TermStack = std::stack<Term>;

public:
  Expression();

  Expression(Argument inArg);

  Expression(const std::string &str);

  Expression(const IMathObject &obj);

  Expression(IMathObject &&obj);

  Expression(int64_t val);

  std::string toString() const noexcept override;

private:
  static TokenToTermVector parseTokensToTerms(detail::TokenVector &tokens);

  static TermStack parseTermsRPN(TokenToTermVector &tokensToTerms);

  static Argument parseExpression(TermStack &termsRPN);

  static std::optional<Term> parseTerm(const detail::Token &token);

  static std::optional<IFunction::OperatorPriority> getOperatorPriority(const IFunction::FunctionMakers &functionMakers);

  static void moveFunctionTerms(TermStack &outTermStack, FunctionTermStack &functionTermStack, const FunctionTerm *nextFunctionTerm);

  static Argument parseFunction(TermStack &argTermsRPN, const FunctionTerm &funcTerm);

  static Argument parseOperator(TermStack &argTermsRPN, const FunctionTerm &funcTerm);

  static Arguments unwrappComma(Argument arg);

  private:
  Argument arg;
};

}
