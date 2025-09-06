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
  Expression();

  Expression(SharedRef<IMathObject> inArg);

  Expression(const std::string &str);

  Expression(const IMathObject &obj);

  Expression(IMathObject &&obj);

  Expression(int64_t val);

  std::string toString() const noexcept override;

  SharedPtr<IMathObject> unwrapp() const noexcept override;

protected:
  bool equals(const SharedRef<IMathObject> &lhs, const SharedRef<IMathObject> &rhs) const noexcept override;

private:
  using Arguments = IFunction::Arguments;

  struct FunctionTerm {
    std::reference_wrapper<const IFunction::FunctionMakers> functionMakers;
    std::optional<OperatorPriority> operatorPriority;
  };

  using Term = std::variant<SharedRef<IMathObject>, FunctionTerm>;

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

private:
  static TokenToTermVector parseTokensToTerms(detail::Tokens &tokens);

  static TermStack parseTermsRPN(TokenToTermVector &tokensToTerms);

  static SharedRef<IMathObject> parseExpression(TermStack &termsRPN);

  static SharedRef<IMathObject> parseExpression(const std::string &str);

  static std::optional<Term> parseTerm(const detail::Token &token);

  static std::optional<OperatorPriority> getOperatorPriority(const IFunction::FunctionMakers &functionMakers);

  static void moveFunctionTerms(TermStack &outTermStack, FunctionTermStack &functionTermStack, const FunctionTerm *nextFunctionTerm);

  static SharedRef<IMathObject> parseFunction(TermStack &argTermsRPN, const FunctionTerm &funcTerm);

  static SharedRef<IMathObject> parseOperator(TermStack &argTermsRPN, const FunctionTerm &funcTerm);

  static Arguments unwrappComma(SharedRef<IMathObject> arg);

private:
  SharedRef<IMathObject> arg;
};

}
