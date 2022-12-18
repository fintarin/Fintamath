#include "fintamath/expressions/EqvExpression.hpp"
#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {
  EqvExpression::EqvExpression(const TokenVector &tokens) {
    parse(tokens);
  }

  EqvExpression::EqvExpression(const IMathObject &oper, const IMathObject &lhs, const IMathObject &rhs) {
    if(!oper.instanceOf<IOperator>() || oper.to<IOperator>().getOperatorPriority() != IOperator::Priority::Comparison){
      throw UndefinedBinaryOpearatorException(oper.toString(), lhs.toString(), rhs.toString());
    }
    if(lhs.is<EqvExpression>() || rhs.is<EqvExpression>()) {
      throw UndefinedBinaryOpearatorException(oper.toString(), lhs.toString(), rhs.toString());
    }

    this->oper = oper.clone();
    leftExpr = lhs.clone();
    rightExpr = rhs.clone();
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
    return simplify(true);
  }

  MathObjectPtr EqvExpression::simplify(bool isPrecise) const{
    auto cloneExpr = *this;
    AddExpression addExpr;
    addExpr.addElement(AddExpression::Element(cloneExpr.leftExpr->clone()));
    addExpr.addElement(AddExpression::Element(cloneExpr.rightExpr->clone(), true));
    cloneExpr.leftExpr = addExpr.simplify();
    cloneExpr.rightExpr = Integer(0).clone();

    if(cloneExpr.leftExpr->instanceOf<IComparable>()){
      auto b = oper->to<IOperator>()(*cloneExpr.leftExpr, *cloneExpr.rightExpr);
      return b.simplify();
    }
    return cloneExpr.clone();
  }

  bool EqvExpression::getResult() const {
    auto b = oper->to<IOperator>()(*leftExpr, *rightExpr);
    
  }

  uint16_t EqvExpression::getInfoPriority() {
    return (uint16_t)IOperator::Priority::Comparison;
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

      leftExpr = IExpression::parse(TokenVector(tokens.begin(), tokens.begin() + (long)i));
      rightExpr = IExpression::parse(TokenVector(tokens.begin() + (long)i + 1, tokens.end()));
      oper = IOperator::parse(tokens[i]);
      return;
    }
    throw InvalidInputException(*this, " not an EqvExpression");
  }

  void EqvExpression::setPrecision(uint8_t precision) {
    // TODO: implement it
  }

}