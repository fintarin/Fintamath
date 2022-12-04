#include "fintamath/expressions/AddExpression.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/helpers/Converter.hpp"

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

  void AddExpression::tryCompressExpression(){
    for(auto& child : addPolynom){
      if(child.info->getClassName() == "Expression"){
        auto childExpr = child.info->to<Expression>();
        child.info = childExpr.tryCompress();
      }
    }
  }

  std::vector<AddExpression::Element> AddExpression::Element::getAddPolynom() const {
    if(info->getClassName() == AddExpression().getClassName()){
      std::vector<Element> result;
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

  void AddExpression::tryCompressTree(){
    std::vector<Element> newPolynom;
    for(const auto& child : addPolynom){
      auto pushPolynom = child.getAddPolynom();
      for(auto& pushChild: pushPolynom){
        newPolynom.emplace_back(std::move(pushChild));
      }
    }
    addPolynom = newPolynom;
  }

  void AddExpression::addElement(MathObjectPtr elem, bool inverted){
    addPolynom.emplace_back(Element(elem->clone(), inverted));
  }

  void AddExpression::baseSimplify(){
    tryCompressExpression();
    tryCompressTree();
  }
}