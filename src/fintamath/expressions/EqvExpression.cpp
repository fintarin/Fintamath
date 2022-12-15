#include "fintamath/expressions/EqvExpression.hpp"

namespace fintamath {
  EqvExpression::EqvExpression(const TokenVector &tokens) {
    parse(tokens);
    *this = simplify()->to<EqvExpression>();
  }

  EqvExpression::EqvExpression(const EqvExpression &rhs) noexcept {
    leftExpr = rhs.leftExpr->clone();
    rightExpr = rhs.rightExpr->clone();
    oper = rhs.oper->clone();
  }

  EqvExpression::EqvExpression(EqvExpression &&rhs) noexcept {
    leftExpr = rhs.leftExpr->clone();
    rightExpr = rhs.rightExpr->clone();
    oper = rhs.oper->clone();
  }

  EqvExpression &EqvExpression::operator=(const EqvExpression &rhs) noexcept {
    if (&rhs != this) {
      leftExpr = rhs.leftExpr->clone();
      rightExpr = rhs.rightExpr->clone();
      oper = rhs.oper->clone();
    }
    return *this;
  }

  EqvExpression &EqvExpression::operator=(EqvExpression &&rhs) noexcept {
    if (&rhs != this) {
      std::swap(leftExpr, rhs.leftExpr);
      std::swap(rightExpr, rhs.rightExpr);
      std::swap(oper, rhs.oper);
    }
    return *this;
  }

  std::string EqvExpression::toString() const {
    return leftExpr->toString() + oper->toString() + rightExpr->toString();
  }

  std::string EqvExpression::getClassName() const {
    return "EqvExpression";
  }

  MathObjectPtr EqvExpression::simplify() const {
    return IMathObject::simplify();
  }

  void EqvExpression::parse(const TokenVector &tokens) {
    bool eqvOpers = false;
    for (size_t i = 0; i < tokens.size(); i++) {
      if (tokens[i] == "<" || tokens[i] == "<=" || tokens[i] == "=" || tokens[i] == ">=" || tokens[i] == ">") {
        if (eqvOpers) {
          throw InvalidInputException(*this, " number of comparison operators exceeded");
        }
        eqvOpers = true;
      }
    }

    for (size_t i = 0; i < tokens.size(); i++) {
      if (tokens[i] == "(" && !skipBrackets(tokens, i)) {
        throw InvalidInputException(*this, " braces must be closed");
      }
      if (i == tokens.size()) {
        break;
      }
      if (tokens[i] != "<" && tokens[i] != "<=" && tokens[i] != "=" && tokens[i] != ">=" && tokens[i] != ">") {
        continue;
      }
      if (i == tokens.size() - 1) {
        throw InvalidInputException(*this, " unexpected sign");
      }
      if (i == 0 || (isOneSymbolToken(tokens[i - 1]) && tokens[i - 1] != "%" && tokens[i - 1] != "!")) {
        continue;
      }

      leftExpr = IExpression::parse(TokenVector(tokens.begin(), tokens.begin() + (long)i));
      rightExpr = IExpression::parse(TokenVector(tokens.begin() + (long)i + 1, tokens.end()));
      oper = IOperator::parse(tokens[i]);
      return;
    }
    throw InvalidInputException(*this, " not an EqvExpression");
  }

  uint16_t getInfoPriority() {
    return (uint16_t)IOperator::Priority::Comparison;
  }

  void EqvExpression::setPrecision(uint8_t precision) {
    // TODO: implement it
  }

}