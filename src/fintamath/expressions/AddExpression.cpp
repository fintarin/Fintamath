#include "fintamath/expressions/AddExpression.hpp"
#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/exceptions/FunctionCallException.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/helpers/Converter.hpp"
#include "fintamath/helpers/Caster.hpp"
#include "fintamath/numbers/Integer.hpp"

#include <memory>

namespace fintamath{

  AddExpression::AddExpression(const AddExpression & rhs) noexcept : addPolynom(rhs.addPolynom){}

  AddExpression::AddExpression(AddExpression && rhs) noexcept : addPolynom(std::move(rhs.addPolynom)){}

  AddExpression& AddExpression::operator=(const AddExpression& rhs) noexcept{
    if(&rhs != this){
      addPolynom = rhs.addPolynom;
    }
    return *this;
  }

  AddExpression& AddExpression::operator=(AddExpression&& rhs) noexcept{
    if(&rhs != this){
      std::swap(addPolynom, rhs.addPolynom);
    }
    return *this;
  }

  AddExpression::AddExpression(const TokenVector& tokens){ 
      parse(tokens);
      *this = simplify()->to<AddExpression>();
  }

  AddExpression::AddExpression(Polynom inAddPolynom) :addPolynom(std::move(inAddPolynom)) {  
  }

  std::string AddExpression::getClassName() const {
      return "AddExpression";
  }

  std::string AddExpression::toString() const {
    std::string result;
    for(const auto & var : addPolynom){
      result += var.inverted ? '-' : '+';
      result += tryPutInBracketsIfNeg(var.info);
    }
    if(!result.empty() && result[0] == '+'){
      result.erase(result.begin());
    }
    return result;
  }

  void AddExpression::invert(){
    for(auto& child : addPolynom){
      child.inverted = !child.inverted;
    }
  }

  const AddExpression::Polynom &AddExpression::getPolynom() const {
    return addPolynom;
  }

  void AddExpression::parse(const TokenVector& tokens){
    for(size_t i = 0;i < tokens.size();i++){
      if(tokens[i] == "(" && !skipBrackets(tokens, i)){
        throw InvalidInputException(*this, " braces must be closed");
      }
      if(i == tokens.size()){
        break;
      }
      if(tokens[i] != "+" && tokens[i] != "-"){
        continue;
      }
      if(i == tokens.size() - 1){
        throw InvalidInputException(*this, " unexpected sign");
      }
      if (i == 0 || (isOneSymbolToken(tokens[i-1]) && tokens[i-1] != "%" && tokens[i-1] != "!")) {
      continue;
      }

      addPolynom.emplace_back(Element(IExpression::parse(TokenVector(tokens.begin(), tokens.begin() + (long)i))));
      addPolynom.emplace_back(Element(IExpression::parse(TokenVector(tokens.begin() + (long)i + 1, tokens.end())), tokens[i] == "-"));
      tryCompressExpression();
      tryCompressTree();
      return;
    }
    throw InvalidInputException(*this, " not an AddExpression");
  }
    
  AddExpression::Element::Element(const Element &rhs) : inverted(rhs.inverted) {
    info = rhs.info->clone();
  }

  AddExpression::Element &AddExpression::Element::operator=(const Element &rhs) {
    if (this != &rhs) {
      info = rhs.info->clone();
      inverted = rhs.inverted;
    }
    return *this;
  }

  AddExpression::Element::Element(MathObjectPtr info, bool inverted) : info(info->clone()), inverted(inverted){}

  MathObjectPtr AddExpression::tryCompressExpression() const{
    auto copyExpr = *this;
    for(auto& child : copyExpr.addPolynom){
      if(child.info->getClassName() == "Expression"){
        auto childExpr = child.info->to<Expression>();
        child.info = childExpr.tryCompress();
      }
    }
    return std::make_unique<AddExpression>(copyExpr);
  }

  std::vector<AddExpression::Element> AddExpression::Element::getAddPolynom() const {
    if(info->getClassName() == AddExpression().getClassName()){
      Polynom result;
      auto addExpr = info->to<AddExpression>();
      for(auto& child : addExpr.addPolynom){
        auto childToPush = std::move(child);
        childToPush.inverted = childToPush.inverted ^ inverted;
        result.emplace_back(childToPush);
      }
      return result;
    }
    return {*this};
  }

  MathObjectPtr AddExpression::tryCompressTree() const{
    auto copyExpr = *this;
    Polynom newPolynom;
    for(const auto& child : copyExpr.addPolynom){
      auto pushPolynom = child.getAddPolynom();
      for(auto& pushChild: pushPolynom){
        newPolynom.emplace_back(std::move(pushChild));
      }
    }
    copyExpr.addPolynom = std::move(newPolynom);
    return std::make_unique<AddExpression>(std::move(copyExpr));
  }

  void AddExpression::addElement(const Element &elem){
    addPolynom.emplace_back(elem);
  }

  MathObjectPtr AddExpression::simplify() const {

    auto exprPtr = tryCompressExpression();
    auto exprObj = helpers::cast<AddExpression>(exprPtr);

    exprPtr = exprObj->tryCompressTree();
    exprObj = helpers::cast<AddExpression>(exprPtr);

    exprObj->sumNumbers();

    return exprObj;
  }

  void AddExpression::sumNumbers(){
    MathObjectPtr sumNumResult = std::make_unique<Integer>(0);
    auto add = Add();
    auto sub = Sub();
    Polynom newAddPolynom;
    for(const auto& elem : addPolynom){
      auto tmpElem = elem.info->clone();
      auto expr = helpers::cast<Expression>(tmpElem);
      try{
        if(!expr){
          throw FunctionCallException();
        }
        if(!elem.inverted){
          sumNumResult = add(*sumNumResult, *expr->getInfo());
        }
        else{
          sumNumResult = sub(*sumNumResult, *expr->getInfo());
        }
      }catch(const FunctionCallException &){
        newAddPolynom.emplace_back(elem);
      }
    }
    if(newAddPolynom.empty() || sumNumResult->toString() != "0"){
      auto expr = std::make_unique<Expression>(*sumNumResult);
      newAddPolynom.emplace_back(Element(expr->clone(), false));
    }
    addPolynom = newAddPolynom;
  }
}