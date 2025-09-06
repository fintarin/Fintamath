#include "fintamath/expressions/Expression.hpp"

#include <cassert>

#include <fmt/core.h>

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/Overload.hpp"
#include "fintamath/core/Tokenizer.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/functions/other/Comma.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/variables/Variable.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Expression)

Expression::Expression() {
  static const Argument zero = makeShared<Integer>(0);
  *this = Expression(zero);
}

Expression::Expression(Argument inArg) : arg(std::move(inArg)) {
  assert(arg);

  if (Argument minimalArg = arg->unwrapp()) {
    arg = minimalArg;
  }
}

Expression::Expression(const IMathObject &obj) : Expression(obj.clone()) {
}

Expression::Expression(IMathObject &&obj) : Expression(std::move(obj).clone()) {
}

Expression::Expression(const int64_t val) : Expression(Integer(val)) {
}

Expression::Expression(const std::string &str) {
  try {
    detail::Tokens tokens = detail::Tokenizer::tokenize(str);
    TokenToTermVector tokensToTerms = Expression::parseTokensToTerms(tokens);
    TermStack termsRPN = Expression::parseTermsRPN(tokensToTerms);
    *this = parseExpression(termsRPN);
  }
  catch (const InvalidInputException &exc) {
    std::string message = exc.what();
    message[0] = static_cast<char>(std::tolower(message[0]));

    throw InvalidInputException(fmt::format(
      R"(Unable to parse an expression from "{}" ({}))",
      str,
      message
    ));
  }
}

std::string Expression::toString() const noexcept {
  return arg->toString();
}

Shared<IMathObject> Expression::unwrapp() const noexcept {
  return arg;
}

bool Expression::equals(const Shared<IMathObject> & /*lhs*/, const Shared<IMathObject> &rhs) const noexcept {
  if (const auto rhsExpr = cast<Expression>(rhs)) {
    return fintamath::equals(arg, rhsExpr->arg);
  }

  return fintamath::equals(arg, rhs);
}

Expression::TokenToTermVector Expression::parseTokensToTerms(detail::Tokens &tokens) {
  if (tokens.empty()) {
    throw InvalidInputException("empty input");
  }

  TokenToTermVector tokensToTerms(tokens.size());

  for (size_t i = 0; i < tokensToTerms.size(); i++) {
    auto &token = tokens[i];
    std::optional<Term> term = parseTerm(token);
    tokensToTerms[i] = {
      .token = std::move(token),
      .term = std::move(term)
    };
  }

  // fixOperatorTypes(tokensToTerms);
  // insertMultiplications(tokensToTerms);
  // collapseFactorials(tokensToTerms);

  return tokensToTerms;
}

// Use the shunting yard algorithm
// https://en.m.wikipedia.org/wiki/Shunting_yard_algorithm
Expression::TermStack Expression::parseTermsRPN(TokenToTermVector &tokensToTerms) {
  TermStack outTermStack;
  FunctionTermStack funcTermStack;

  for (auto &[token, term] : tokensToTerms) {
    if (!term) {
      if (token.type == detail::TokenType::RoundBracketOpen) {
        funcTermStack.emplace();
      }
      else if (token.type == detail::TokenType::RoundBracketClose) {
        moveFunctionTerms(outTermStack, funcTermStack, {});

        if (funcTermStack.empty()) {
          throw InvalidInputException("bracket mismatch");
        }

        funcTermStack.pop();
      }
      else {
        throw InvalidInputException(fmt::format(R"(invalid term "{}")", token.name));
      }

      continue;
    }

    std::visit(
      detail::Overload{
        [&](Argument &argTerm) {
          outTermStack.emplace(std::move(argTerm));
        },
        [&](FunctionTerm &funcTerm) {
          if (funcTerm.operatorPriority) {
            moveFunctionTerms(outTermStack, funcTermStack, &funcTerm);
          }

          funcTermStack.emplace(std::move(funcTerm));
        },
      },
      *term
    );
  }

  moveFunctionTerms(outTermStack, funcTermStack, {});

  if (!funcTermStack.empty()) {
    throw InvalidInputException("bracket mismatch");
  }

  return outTermStack;
}

Expression::Argument Expression::parseExpression(TermStack &termsRPN) {
  if (termsRPN.empty()) {
    throw InvalidInputException("incomplete expression inside brackets");
  }

  Term term = std::move(termsRPN.top());
  termsRPN.pop();

  Argument outArg = std::visit(
    detail::Overload{
      [&](Argument &argTerm) {
        return std::move(argTerm);
      },
      [&](FunctionTerm &funcTerm) {
        if (funcTerm.operatorPriority) {
          return parseOperator(termsRPN, funcTerm);
        }

        return parseFunction(termsRPN, funcTerm);
      },
    },
    term
  );

  return outArg;
}

std::optional<Expression::Term> Expression::parseTerm(const detail::Token &token) {
  switch (token.type) {
    case detail::TokenType::Variable: {
      return makeShared<Variable>(token.name);
    }
    case detail::TokenType::Integer: {
      return makeShared<Integer>(token.name);
    }
    case detail::TokenType::Decimal: {
      return makeShared<Rational>(token.name);
    }
    case detail::TokenType::Registered: {
      if (const IFunction::FunctionMakers *functionMakers = IFunction::parseFunctionMakers(token.name)) {
        return FunctionTerm{
          .functionMakers = *functionMakers,
          .operatorPriority = getOperatorPriority(*functionMakers),
        };
      }
      if (Shared<IConstant> constant = IConstant::parseConstant(token.name)) {
        return constant;
      }
      throw InvalidInputException(fmt::format(R"(invalid term {})", token.name));
    }
    default: {
      return {};
    }
  }
}

std::optional<OperatorPriority> Expression::getOperatorPriority(const IFunction::FunctionMakers &functionMakers) {
  std::optional<OperatorPriority> outPriority;

  for (const auto &maker : functionMakers) {
    const IFunction::Declaration &decl = maker.getDeclaration();
    if (decl.operatorPriority && (!outPriority || *outPriority < decl.operatorPriority)) {
      outPriority = decl.operatorPriority;
    }
  }

  return outPriority;
}

void Expression::moveFunctionTerms(TermStack &outTermStack, FunctionTermStack &functionTermStack, const FunctionTerm *nextFunctionTerm) {
  if (nextFunctionTerm && nextFunctionTerm->operatorPriority == OperatorPriority::PrefixUnary) {
    return;
  }

  while (!functionTermStack.empty() &&
         functionTermStack.top() &&
         (!nextFunctionTerm ||
          !functionTermStack.top()->operatorPriority ||
          *functionTermStack.top()->operatorPriority <= nextFunctionTerm->operatorPriority)) {

    outTermStack.emplace(std::move(*functionTermStack.top()));
    functionTermStack.pop();
  }
}

// void Expression::insertMultiplications(TermVector &terms) {
//   static const ArgumentPtr mul = MulOper{}.clone();

//   for (size_t i = 1; i < terms.size(); i++) {
//     if (canNextTermBeBinaryOperator(terms[i - 1]) &&
//         canPrevTermBeBinaryOperator(terms[i])) {

//       Term term(mul->toString(), mul->clone());
//       terms.insert(terms.begin() + static_cast<ptrdiff_t>(i), std::move(term));
//       i++;
//     }
//   }
// }

// void Expression::fixOperatorTypes(TermVector &terms) {
//   if (auto &term = terms.front();
//       is<IOperator>(term.value) &&
//       !isPrefixOperator(term.value.get())) {

//     term.value = findOperator(term.name, IOperator::Priority::PrefixUnary);

//     if (!term.value) {
//       throw InvalidInputException(fmt::format(
//         R"(incomplite expression with operator "{}")",
//         term.name
//       ));
//     }
//   }

//   if (auto &term = terms.back();
//       is<IOperator>(term.value) &&
//       !isPostfixOperator(term.value.get())) {

//     term.value = findOperator(term.name, IOperator::Priority::PostfixUnary);

//     if (!term.value) {
//       throw InvalidInputException(fmt::format(
//         R"(incomplite expression with operator "{}")",
//         term.name
//       ));
//     }
//   }

//   if (terms.size() < 3) {
//     return;
//   }

//   for (size_t i = 1; i + 1 < terms.size(); i++) {
//     auto &term = terms[i];
//     const auto &termPrev = terms[i - 1];

//     if (is<IOperator>(term.value) &&
//         !isPrefixOperator(term.value.get()) &&
//         !canNextTermBeBinaryOperator(termPrev)) {

//       term.value = findOperator(term.name, IOperator::Priority::PrefixUnary);

//       if (!term.value) {
//         throw InvalidInputException(fmt::format(
//           R"(incomplite expression with operator "{}")",
//           term.name
//         ));
//       }
//     }
//   }

//   for (size_t i = terms.size() - 2; i > 0; i--) {
//     auto &term = terms[i];
//     const auto &termNext = terms[i + 1];

//     if (is<IOperator>(term.value) &&
//         !isPostfixOperator(term.value.get()) &&
//         !canPrevTermBeBinaryOperator(termNext)) {

//       term.value = findOperator(term.name, IOperator::Priority::PostfixUnary);

//       if (!term.value) {
//         throw InvalidInputException(fmt::format(
//           R"(incomplite expression with operator "{}")",
//           term.name
//         ));
//       }
//     }
//   }
// }

// void Expression::collapseFactorials(TermVector &terms) {
//   for (size_t i = 1; i + 1 < terms.size(); i++) {
//     auto &term = terms[i];
//     const auto &termNext = terms[i + 1];

//     if (is<Factorial>(term.value) && is<Factorial>(termNext.value)) {
//       const auto &oldFactorial = cast<Factorial>(*term.value);
//       term.value = Factorial(oldFactorial.getOrder() + 1).clone();

//       terms.erase(terms.begin() + static_cast<ptrdiff_t>(i) + 1);
//       i--;
//     }
//   }
// }

// bool Expression::canNextTermBeBinaryOperator(const Term &term) {
//   return !(isPrefixOperator(term.value.get()) || isBinaryOperator(term.value.get()) || isNonOperatorFunction(term.value.get()) || term.name == "(" || term.name == ",");
// }

// bool Expression::canPrevTermBeBinaryOperator(const Term &term) {
//   return !(isPostfixOperator(term.value.get()) || isBinaryOperator(term.value.get()) || term.name == ")" || term.name == ",");
// }

// bool Expression::isBinaryOperator(const IMathObject *val) {
//   const auto *oper = cast<IOperator>(val);
//   return oper && oper->getArgumentClasses().size() == 2;
// }

// bool Expression::isPrefixOperator(const IMathObject *val) {
//   const auto *oper = cast<IOperator>(val);
//   return oper && oper->getPriority() == IOperator::Priority::PrefixUnary;
// }

// bool Expression::isPostfixOperator(const IMathObject *val) {
//   const auto *oper = cast<IOperator>(val);
//   return oper && oper->getPriority() == IOperator::Priority::PostfixUnary;
// }

// bool Expression::isNonOperatorFunction(const IMathObject *val) {
//   return is<IFunction>(val) && !is<IOperator>(val);
// }

Expression::Argument Expression::parseOperator(TermStack &argTermsRPN, const FunctionTerm &funcTerm) {
  size_t expectedArgsSize = 0;
  for (const auto &maker : funcTerm.functionMakers.get()) {
    const IFunction::Declaration &makerDecl = maker.getDeclaration();
    if (makerDecl.operatorPriority != funcTerm.operatorPriority) {
      continue;
    }

    if (expectedArgsSize > 0) {
      throw InvalidInputException("Ambiguous operator"); // TODO
    }

    expectedArgsSize = makerDecl.argumentClasses.size();
  }

  Arguments args;
  while (!argTermsRPN.empty() && args.size() != expectedArgsSize) {
    args.emplace_back(parseExpression(argTermsRPN));
  }
  std::ranges::reverse(args);

  Shared<IFunction> outOper;
  for (const auto &maker : funcTerm.functionMakers.get()) {
    if (!maker.doArgumentsMatch(args)) {
      continue;
    }

    if (outOper) {
      throw InvalidInputException("Ambiguous operator"); // TODO
    }

    outOper = maker.make(std::move(args));
  }

  if (!outOper) {
    throw InvalidInputException("Operator args are invalid"); // TODO
  }

  return outOper;
}

Expression::Argument Expression::parseFunction(TermStack &argTermsRPN, const FunctionTerm &funcTerm) {
  Arguments args = unwrappComma(parseExpression(argTermsRPN));

  Shared<IFunction> outFunc;
  for (const auto &maker : funcTerm.functionMakers.get()) {
    if (!maker.doArgumentsMatch(args)) {
      continue;
    }

    if (outFunc) {
      throw InvalidInputException("Ambiguous function"); // TODO
    }

    outFunc = maker.make(std::move(args));
  }

  if (!outFunc) {
    throw InvalidInputException("Function args are invalid"); // TODO
  }

  return outFunc;
}

Expression::Arguments Expression::unwrappComma(Argument inArg) {
  if (const auto argFunc = cast<IFunction>(inArg); is<Comma>(argFunc)) {
    Comma::compress(inArg);
    return cast<IFunction>(inArg)->getArguments();
  }

  return {std::move(inArg)};
}

}