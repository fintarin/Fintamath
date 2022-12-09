#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/exceptions/FunctionCallException.hpp"
#include "fintamath/expressions/AddExpression.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {
  std::string MulExpression::getClassName() const {
    return "MulExpression";
  }

  const MulExpression::Polynom &MulExpression::getPolynom() const {
    return mulPolynom;
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

  std::string MulExpression::tryPutInBrackets(const MathObjectPtr& obj) {
    if(obj->is<AddExpression>()){
      return "(" + obj->toString() + ")";
    }
    return tryPutInBracketsIfNeg(obj);
  }

  std::string MulExpression::toString() const{
    std::string result;
    if(!mulPolynom.empty() && mulPolynom.at(0).inverted){
      result += '1';
    }
    for(const auto & var : mulPolynom){
      result += var.inverted ? '/' : '*';
      result += tryPutInBrackets(var.info);
    }
    if(!result.empty()){
      result.erase(result.begin());
    }
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
    *this = simplify()->to<MulExpression>();
  }

  MulExpression::MulExpression(Polynom inMulPolynom) : mulPolynom(std::move(inMulPolynom)) {
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
      tryCompressExpression();
      tryCompressTree();
      return;
    }
    throw InvalidInputException(*this, " not a MulExpression");
  }

  MulExpression::Element::Element(MathObjectPtr info, bool inverted) : info(info->clone()), inverted(inverted){}

  MathObjectPtr MulExpression::tryCompressExpression() const {
    auto copyExpr = *this;
    for(auto& child : copyExpr.mulPolynom){
      if(child.info->getClassName() == Expression().getClassName()){
        auto childExpr = child.info->to<Expression>();
        child.info = childExpr.tryCompress();
      }
    }
    return std::make_unique<MulExpression>(copyExpr);
  }

  std::vector<MulExpression::Element> MulExpression::Element::getMulPolynom() const {
    if(info->getClassName() == MulExpression().getClassName()){
      Polynom result;
      auto mulExpr = info->to<MulExpression>();
      for(auto& child : mulExpr.mulPolynom){
        auto childToPush = std::move(child);
        childToPush.inverted = childToPush.inverted ^ inverted;
        result.emplace_back(childToPush);
      }
      return result;
    }
    return {*this};
  }

  MathObjectPtr MulExpression::tryCompressTree() const {
    auto copyExpr = *this;
    Polynom newPolynom;
    for(const auto& child : mulPolynom){
      auto pushPolynom = child.getMulPolynom();
      for(auto& pushChild: pushPolynom){
        newPolynom.emplace_back(std::move(pushChild));
      }
    }
    copyExpr.mulPolynom = newPolynom;
    return std::make_unique<MulExpression>(std::move(copyExpr));
  }

  void MulExpression::addElement(const Element &elem){
    mulPolynom.emplace_back(elem);
  }

  MathObjectPtr MulExpression::simplify() const {
    auto exprPtr = tryCompressExpression();
    auto exprObj = helpers::cast<MulExpression>(exprPtr);

    exprPtr = exprObj->tryCompressTree();
    exprObj = helpers::cast<MulExpression>(exprPtr);

    exprObj->mulNumbers();
    
    return exprObj;
  }

  void MulExpression::mulNumbers(){
    Expression mulNumResult = Integer(1);
    auto mul = Mul();
    auto div = Div();
    Polynom newMulPolynom;
    for(const auto& elem : mulPolynom){
      auto tmpElem = elem.info->clone();
      auto expr = helpers::cast<Expression>(tmpElem);
      try{
        if(!expr){
          throw FunctionCallException();
        }
        if(!elem.inverted){
          mulNumResult = mul(mulNumResult, *expr->getInfo());
        }
        else{
          mulNumResult = div(mulNumResult, *expr->getInfo());
        }
      }catch(const FunctionCallException &){
        newMulPolynom.emplace_back(elem);
      }
    }
    if(newMulPolynom.empty() || mulNumResult.toString() != "1"){
      newMulPolynom.emplace_back(Element(mulNumResult.clone(), false));
    }
    mulPolynom = newMulPolynom;
  }


}
