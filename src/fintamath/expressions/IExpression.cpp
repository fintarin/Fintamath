#include "fintamath/expressions/IExpression.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

bool IExpression::skipBrackets(const TokenVector &tokens, size_t &inOutIndex) {
  if (inOutIndex >= tokens.size() || tokens.at(inOutIndex) != "(") {
    return false;
  }

  int64_t brackets = 0;

  for (size_t i = inOutIndex; i < tokens.size(); i++) {
    if (tokens[i] == "(") {
      brackets++;
    } else if (tokens[i] == ")") {
      brackets--;
    }

    if (brackets == 0) {
      inOutIndex = i + 1;
      return true;
    }
    if (brackets < 0) {
      throw InvalidInputException(Tokenizer::tokensToString(tokens));
    }
  }

  throw InvalidInputException(Tokenizer::tokensToString(tokens));
}

TokenVector IExpression::cutBraces(const TokenVector &tokens) {
  if (tokens.empty()) {
    return tokens;
  }
  auto newTokens = tokens;
  if (newTokens.front() == "(" && newTokens.back() == ")") {
    newTokens.erase(newTokens.begin());
    newTokens.erase(newTokens.end() - 1);
  }
  return newTokens;
}

std::string IExpression::tryPutInBracketsIfNeg(const MathObjectPtr &obj) {
  if (!obj->instanceOf<Expression>()) {
    return obj->toString();
  }

  const auto &exprObj = obj->to<Expression>();

  if (exprObj.getInfo()->instanceOf<Neg>()) {
    return "(" + exprObj.toString() + ")";
  }

  return obj->toString();
}

void IExpression::validateFunctionArgs(const IFunction &func, const ArgumentsVector &args) const {
  ArgumentsVector nonMatchingArgs = func.getNonMatchingArgs(args);

  for (const auto &arg : nonMatchingArgs) {
    if (!arg.get().instanceOf<Variable>() && !arg.get().instanceOf<IConstant>() &&
        !arg.get().instanceOf<IExpression>()) {
      throw InvalidInputException(toString());
    }
  }
}

std::vector<MathObjectPtr> IExpression::getVariables() const {
  return {};
}

}
