#include "fintamath/math_objects/nodes/expressions/Expression.hpp"

#include <stdexcept>

#include "fintamath/math_objects/nodes/collections/CollectionParser.hpp"
#include "fintamath/math_objects/nodes/terms/TermParser.hpp"
#include "fintamath/math_objects/relations/RelationParser.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryDivide.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryMinus.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryPlus.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/unary_arithmetic_operators/UnaryMinus.hpp"

namespace fintamath {
  static std::string_view deleteOpenAndCloseBracket(const std::string_view &str) {
    if (str[0] != '(') {
      return str;
    }
    int leftBracket = 0;
    int rightBracket = 0;
    int position = 0;
    while (position < str.size()) {
      if (str[position] == '(') {
        leftBracket++;
      }
      if (str[position] == ')') {
        rightBracket++;
      }
      if (leftBracket == rightBracket) {
        break;
      }
      position++;
    }
    if (position == str.size()) {
      throw std::invalid_argument("");
    }
    if (position == str.size() - 1) {
      return str.substr(1, str.size() - 2);
    }
    return str;
  }

  Expression::Expression(const std::string_view &str) {
    auto oldString = str;
    auto newString = deleteOpenAndCloseBracket(str);
    while (oldString != newString) {
      oldString = newString;
      newString = deleteOpenAndCloseBracket(newString);
    }
    if (auto parsResult = RelationParser::parse(newString); parsResult) {
      *this = *parsResult;
      return;
    }
    if (auto parsResult = TermParser::parse(newString); parsResult) {
      std::shared_ptr<MathObject> node = parsResult->clone();
      set = Set{std::dynamic_pointer_cast<Node>(node)};
      relation = nullptr;
      return;
    }
    if (auto parsResult = CollectionParser::parse(newString); parsResult) {
      std::shared_ptr<MathObject> node = parsResult->clone();
      set = Set{std::dynamic_pointer_cast<Node>(node)};
      relation = nullptr;
      return;
    }
    throw std::invalid_argument("");
  }

  std::shared_ptr<Relation> Expression::getRelation() const {
    return relation;
  }

  std::shared_ptr<Operator> Expression::getOperator() const {
    return std::dynamic_pointer_cast<Operator>(relation);
  }

  Set Expression::getSet() const {
    return set;
  }

  void Expression::setRelation(const std::shared_ptr<Relation> &rel) {
    std::shared_ptr<MathObject> newRel = rel->clone();
    relation = std::dynamic_pointer_cast<Relation>(newRel);
  }

  void Expression::setSet(const Set &operSet) {
    set = operSet;
  }
  void putInBrackets(std::string &str) {
    str.insert(str.begin(), '(');
    str.insert(str.end(), ')');
  }

  std::string Expression::toString() const {
    if (relation == nullptr) {
      return set.at(0)->toString();
    }
    if (auto rel = std::dynamic_pointer_cast<BinaryArithmeticOperator>(relation); rel) {
      auto leftHalf = set.at(0)->toString();
      auto rightHalf = set.at(1)->toString();
      if (auto leftExpression = std::dynamic_pointer_cast<Expression>(set.at(0)); leftExpression) {
        if (auto oper = leftExpression->getOperator(); oper && oper->getPriority() > rel->getPriority()) {
          putInBrackets(leftHalf);
        }
      }
      if (auto rightExpression = std::dynamic_pointer_cast<Expression>(set.at(1)); rightExpression) {
        if (auto oper = rightExpression->getOperator(); oper) {
          if (oper->getPriority() > rel->getPriority()) {
            putInBrackets(rightHalf);
          } else if (oper->getPriority() == rel->getPriority() && !rel->isAssociative()) {
            putInBrackets(rightHalf);
          } else if (auto unaryOperator = std::dynamic_pointer_cast<UnaryArithmeticOperator>(oper); unaryOperator) {
            putInBrackets(rightHalf);
          }
        }
      }
      return leftHalf + rel->toString() + rightHalf;
    }
    if (auto rel = std::dynamic_pointer_cast<UnaryArithmeticOperator>(relation); rel) {
      auto result = set.at(0)->toString();
      if (auto expression = std::dynamic_pointer_cast<Expression>(set.at(0)); expression) {
        if (auto oper = expression->getOperator(); oper && oper->getPriority() == rel->getPriority()) {
          putInBrackets(result);
        } else if (!rel->isAssociative() && (expression->getRelation()->toString() == BinaryPlus().toString() ||
                                             expression->getRelation()->toString() == BinaryMinus().toString())) {
          putInBrackets(result);
        }
      }
      return rel->toString() + result;
    }
    throw std::invalid_argument("");
  }

  Expression::Expression(Set set, std::shared_ptr<Relation> relation)
      : set(std::move(set)), relation(std::move(relation)) {
  }

  std::unique_ptr<MathObject> Expression::clone() const {
    return std::make_unique<Expression>(*this);
  }

  std::shared_ptr<Node> Expression::calculate() const {
    auto copySet = set;
    for (int i = 0; i < copySet.size(); i++) {
      if (auto expr = std::dynamic_pointer_cast<Expression>(copySet.at(i)); expr) {
        copySet.at(i) = expr->calculate();
      }
    }
    if (relation == nullptr) {
      return set.at(0);
    }
    return (*relation)(copySet);
  }
}