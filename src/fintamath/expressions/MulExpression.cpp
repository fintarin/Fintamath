#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/expressions/Expression.hpp"

namespace fintamath {
  std::string MulExpression::getClassName() const {
    return "MulExpression";
  }

  MulExpression::MulExpression(const MulExpression & rhs) noexcept : mulPolynom(rhs.mulPolynom){}

  MulExpression::MulExpression(MulExpression && rhs) noexcept : mulPolynom(std::move(rhs.mulPolynom)){}

  MulExpression& MulExpression::operator=(const MulExpression& rhs) noexcept{
    if(&rhs != this){
      mulPolynom = rhs.mulPolynom;
    }
    return *this;
  }

  MulExpression& MulExpression::operator=(MulExpression&& rhs) noexcept{
    if(&rhs != this){
      std::swap(mulPolynom, rhs.mulPolynom);
    }
    return *this;
  }

  std::string MulExpression::toString() const{
    std::string result;
    result.push_back('(');
    for(const auto & var : mulPolynom){
      result += var.info->toString();
      result += var.inverted ? '/' : '*';
    }
    result.pop_back();
    result.push_back(')');
    return result;
  }

  MulExpression::Element::Element(const Element &rhs) : inverted(rhs.inverted) {
    info = rhs.info->clone();
  }

  MulExpression::Element &MulExpression::Element::operator=(const Element &rhs) {
    if (this != &rhs) {
      info = rhs.info->clone();
      inverted = rhs.inverted;
    }
    return *this;
  }

  MulExpression::MulExpression(const TokenVector& tokens){
    parse(tokens);
  }

  void MulExpression::parse(const TokenVector & tokens){
    for(size_t i = 0;i < tokens.size();i++){
      if(tokens[i] == "(" && !skipBrackets(tokens, i)){
        throw InvalidInputException(*this, " braces must be closed");
      }
      if(i == tokens.size()){
        break;
      }
      if(tokens[i] != "*" && tokens[i] != "/"){
        continue;
        }
      if(i == tokens.size() - 1){
        throw InvalidInputException(*this, " unexpected sign");
      }

      mulPolynom.emplace_back(Element(IExpression::parse(TokenVector(tokens.begin(), tokens.begin() + (long)i))));
      mulPolynom.emplace_back(Element(IExpression::parse(TokenVector(tokens.begin() + (long)i + 1, tokens.end())), tokens[i] == "/"));
      tryCompress();
      return;
    }
    throw InvalidInputException(*this, " not a MulExpression");
  }

  MulExpression::Element::Element(MathObjectPtr info, bool inverted) : info(info->clone()), inverted(inverted){}

  void MulExpression::tryCompress(){
    for(auto& child : mulPolynom){
      if(child.info->getClassName() == "Expression"){
        auto childExpr = child.info->to<Expression>();
        child.info = childExpr.tryCompress();
      }
    }
  }
}
