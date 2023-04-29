#include "fintamath/expressions/ExpressionUtils.hpp"

#include "fintamath/core/IComparable.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

bool skipBrackets(const TokenVector &tokens, size_t &openBracketIndex) {
  if (openBracketIndex >= tokens.size() || tokens.at(openBracketIndex) != "(") {
    return false;
  }

  int64_t brackets = 0;

  for (size_t i = openBracketIndex; i < tokens.size(); i++) {
    if (tokens[i] == "(") {
      brackets++;
    }
    else if (tokens[i] == ")") {
      brackets--;
    }

    if (brackets == 0) {
      openBracketIndex = i + 1;
      return true;
    }
    if (brackets < 0) {
      throw InvalidInputException(Tokenizer::tokensToString(tokens));
    }
  }

  throw InvalidInputException(Tokenizer::tokensToString(tokens));
}

TokenVector cutBrackets(const TokenVector &tokens) {
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

std::map<size_t, ArgumentPtr> findBinaryOperators(const TokenVector &tokens) {
  std::map<size_t, ArgumentPtr> operators;

  bool isPrevTokenOper = false;

  for (size_t i = 0; i < tokens.size(); i++) {
    if (skipBrackets(tokens, i)) {
      isPrevTokenOper = false;
      i--;
    }
    else if (std::shared_ptr<IOperator> oper = IOperator::parse(tokens.at(i));
             oper && oper->getFunctionType() == IFunction::Type::Binary) {
      if (!isPrevTokenOper) {
        operators.insert({i, oper});
        isPrevTokenOper = true;
      }
    }
    else {
      isPrevTokenOper = false;
    }
  }

  return operators;
}

std::string putInBrackets(const std::string &str) {
  return '(' + str + ')';
}

std::string putInSpaces(const std::string &str) {
  return ' ' + str + ' ';
}

std::string binaryOperatorToString(const IOperator &oper, const ArgumentsPtrVector &values) {
  std::string result;

  std::string operStr = oper.toString();
  IOperator::Priority operPriority = oper.getOperatorPriority();
  bool operIsAssociative = oper.isAssociative();

  if (operPriority != IOperator::Priority::Multiplication && operPriority != IOperator::Priority::Exponentiation) {
    operStr = ' ' + operStr + ' ';
  }

  for (size_t i = 0; i < values.size(); i++) {
    const ArgumentPtr &child = values[i];

    bool shouldPutInBrackets = false;

    if (const auto childExpr = cast<IExpression>(child)) {
      if (const auto childOper = cast<IOperator>(childExpr->getFunction())) {
        if (IOperator::Priority priority = childOper->getOperatorPriority();
            priority > operPriority ||
            (priority == operPriority && !operIsAssociative && (*childOper != oper || i > 0))) {
          shouldPutInBrackets = true;
        }
      }
    }

    if (shouldPutInBrackets) {
      result += putInBrackets(child->toString());
    }
    else {
      result += child->toString();
    }

    result += operStr;
  }

  result = result.substr(0, result.length() - operStr.length());

  return result;
}

std::string postfixUnaryOperatorToString(const IOperator &oper, const ArgumentPtr &lhs) {
  std::string result = lhs->toString();

  if (const auto child = cast<IExpression>(lhs)) {
    if (const auto childOper = cast<IOperator>(child->getFunction())) {
      if (IOperator::Priority priority = childOper->getOperatorPriority();
          priority != IOperator::Priority::PostfixUnary) {
        return putInBrackets(result) + oper.toString();
      }
    }
  }

  if (const auto comp = cast<IComparable>(lhs); comp && *comp < ZERO) {
    return putInBrackets(result) + oper.toString();
  }

  return result + oper.toString();
}

bool hasVariables(const std::shared_ptr<const IExpression> &expr, const std::shared_ptr<const Variable> &var) {
  for (const auto &child : expr->getChildren()) {
    if (const auto childExpr = cast<IExpression>(child); childExpr && hasVariables(childExpr, var)) {
      return true;
    }

    if (const auto childVar = cast<Variable>(child); childVar && *childVar == *var) {
      return true;
    }
  }

  return false;
}

}