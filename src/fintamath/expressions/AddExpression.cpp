#include "fintamath/expressions/AddExpression.hpp"
#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/exceptions/Exception.hpp"
#include "fintamath/exceptions/FunctionCallException.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/helpers/Converter.hpp"
#include "fintamath/helpers/Caster.hpp"
#include "fintamath/literals/ILiteral.hpp"
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
      auto a = toString();
      *this = simplifyResultToAddExpression();
  }

  AddExpression::AddExpression(Polynom inAddPolynom) :addPolynom(std::move(inAddPolynom)) {  
    *this = simplifyResultToAddExpression();
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
    int lastSignPosition = -1;
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
      lastSignPosition = (int)i;
    }

    if(lastSignPosition == -1){
      throw InvalidInputException(*this, " not an AddExpression");
    }

    addPolynom.emplace_back(Element(IExpression::parse(TokenVector(tokens.begin(), tokens.begin() + (long)lastSignPosition))));
    addPolynom.emplace_back(Element(IExpression::parse(TokenVector(tokens.begin() + (long)lastSignPosition + 1, tokens.end())), tokens[lastSignPosition] == "-"));

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
      if(child.info->is<Expression>()){
        auto childExpr = child.info->to<Expression>();
        child.info = childExpr.tryCompress();
      }
    }
    return std::make_unique<AddExpression>(copyExpr);
  }

  std::vector<AddExpression::Element> AddExpression::Element::getAddPolynom() const {
    if(info->is<AddExpression>()){
      Polynom result;
      auto addExpr = info->to<AddExpression>();
      for(const auto& child : addExpr.addPolynom){
        result.emplace_back(Element{child.info->clone(), (bool)(child.inverted^inverted)});
      }
      return result;
    }
    return {*this};
  }

  MathObjectPtr AddExpression::compressTree() const{
    auto copyExpr = *this;
    Polynom newPolynom;
    for(const auto& child : copyExpr.addPolynom){
      auto pushPolynom = child.getAddPolynom();
      for(auto& pushChild: pushPolynom){
        newPolynom.emplace_back(pushChild);
      }
    }
    copyExpr.addPolynom = newPolynom;
    return std::make_unique<AddExpression>(copyExpr);
  }

  void AddExpression::addElement(const Element &elem){
    addPolynom.emplace_back(elem);
    *this = simplifyResultToAddExpression();
  }


  MathObjectPtr AddExpression::simplify() const {
    if(addPolynom.size() == 1){
      if(addPolynom.at(0).inverted){
        return std::make_unique<Expression>(Neg()(*addPolynom.at(0).info));
      }
      return addPolynom.at(0).info->clone();
    }
    
    auto exprPtr = tryCompressExpression();
    auto exprObj = helpers::cast<AddExpression>(exprPtr);

    auto b = exprObj->toString();

    for(auto& obj : exprObj->addPolynom){
      obj.info = obj.info->simplify();
    }

    exprPtr = exprObj->compressTree();
    exprObj = helpers::cast<AddExpression>(exprPtr);

    b = exprObj->toString();
    exprObj->sort();
    b = exprObj->toString();

    exprPtr = exprObj->compressTree();
    exprObj = helpers::cast<AddExpression>(exprPtr);

    if(exprObj->addPolynom.size() == 1){
      if(exprObj->addPolynom.at(0).inverted){
        return std::make_unique<Expression>(Neg()(*exprObj->addPolynom.at(0).info));
      }
      return exprObj->addPolynom.at(0).info->clone();
    }
    return exprObj;
  }

  bool sortFunc(const AddExpression::Element& lhs, const AddExpression::Element& rhs){
    return lhs.info->toString() < rhs.info->toString();
  }

  void AddExpression::sort(){
    auto numVect = Polynom();
    auto powVect = Polynom();
    auto literalVect = Polynom();
    auto mulVect = Polynom();
    auto funcVect = Polynom();

    for(const auto& child : addPolynom){
      if(child.info->is<MulExpression>()){
        mulVect.emplace_back(child);
        continue;
      }
      if(!child.info->is<Expression>()){
        throw InvalidInputException(*this, "argument must be an expression: " + child.info->toString());
      }
      auto exprInfo = (child.info->to<Expression>()).getInfo()->clone();
      if(exprInfo->instanceOf<IArithmetic>()){
        numVect.emplace_back(child);
      } else if (exprInfo->is<Pow>()){
        powVect.emplace_back(child);
      } else if (exprInfo->instanceOf<ILiteral>()){
        literalVect.emplace_back(child);
      } else if (exprInfo->instanceOf<IFunction>()){
        funcVect.emplace_back(child);
      } else {
        throw InvalidInputException(*this, "undefined expression type: " + exprInfo->getClassName());
      }
    }

    numVect = sumNumbers(numVect);

    addPolynom.clear();

    std::sort(funcVect.begin(), funcVect.end(), sortFunc);
    std::sort(powVect.begin(), powVect.end(), sortFunc);
    std::sort(literalVect.begin(), literalVect.end(), sortFunc);
    std::sort(mulVect.begin(), mulVect.end(), sortFunc);

    pushPolynomToPolynom<AddExpression>(funcVect, addPolynom);
    pushPolynomToPolynom<AddExpression>(powVect, addPolynom);
    pushPolynomToPolynom<AddExpression>(mulVect, addPolynom);
    pushPolynomToPolynom<AddExpression>(literalVect, addPolynom);
    if(numVect.at(0).info->toString() != "0" || addPolynom.empty()){
      pushPolynomToPolynom<AddExpression>(numVect, addPolynom);
    }
  }

  AddExpression::Polynom AddExpression::sumNumbers(const Polynom& numVect){
    Expression expr = 0;
    Add add;
    Sub sub;
    for(const auto& elem: numVect){
      auto exprNum = elem.info->to<Expression>();
      if(elem.inverted){
        expr = sub(*expr.getInfo(), *exprNum.getInfo());
      } else {
        expr = add(*expr.getInfo(), *exprNum.getInfo());
      }
    }
    return {{std::make_unique<Expression>(expr), false}};
  }

  AddExpression AddExpression::simplifyResultToAddExpression() const{
    AddExpression addExpr;
    auto info = simplify();
    if(info->is<AddExpression>()){
      addExpr = info->to<AddExpression>();
      return addExpr;
    }
    addExpr.addPolynom.emplace_back(Element(info->clone(), false));
    return addExpr;
  }
}