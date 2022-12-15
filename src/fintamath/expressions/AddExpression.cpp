#include "fintamath/expressions/AddExpression.hpp"
#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/exceptions/Exception.hpp"
#include "fintamath/exceptions/FunctionCallException.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/helpers/Converter.hpp"
#include "fintamath/helpers/Caster.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

#include <cstdint>
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
  }

  AddExpression::AddExpression(const IMathObject& rhs){
    if(rhs.is<AddExpression>()){
      *this = rhs.to<AddExpression>();
      return;
    }
    addPolynom.emplace_back(Element{rhs.clone(), false});
  }

  AddExpression::AddExpression(Polynom inAddPolynom) :addPolynom(std::move(inAddPolynom)) {}

  std::string AddExpression::getClassName() const {
      return "AddExpression";
  }

  uint16_t AddExpression::getInfoPriority(){
    return (uint16_t)IOperator::Priority::Addition;
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
    auto leftExpr = IExpression::parse(TokenVector(tokens.begin(), tokens.begin() + (long)lastSignPosition));
    auto rightExpr = IExpression::parse(TokenVector(tokens.begin() + (long)lastSignPosition + 1, tokens.end()));

    if(!leftExpr || !rightExpr){
      throw InvalidInputException(*this, tokensToString(tokens));
    }

    addPolynom.emplace_back(Element(leftExpr->clone()));
    addPolynom.emplace_back(Element(rightExpr->clone(), tokens[lastSignPosition] == "-"));

    *this = AddExpression(compressTree());
  }
    
  AddExpression::Element::Element(const Element &rhs) : info(rhs.info->clone()), inverted(rhs.inverted) {}

  AddExpression::Element &AddExpression::Element::operator=(const Element &rhs) {
    if (this != &rhs) {
      info = rhs.info->clone();
      inverted = rhs.inverted;
    }
    return *this;
  }

  AddExpression::Element::Element(MathObjectPtr info, bool inverted) : info(info->clone()), inverted(inverted){}

  MathObjectPtr AddExpression::Element::toMathObject() const {
    if(inverted){
      return Neg()(*info->clone()).simplify();
    }
    return info->simplify();
  }

  AddExpression::Polynom AddExpression::compressExpression() const{
    Polynom newPolynom;
    for(auto& child : addPolynom){
      if(child.info->is<Expression>()){
        auto childExpr = child.info->to<Expression>();
        newPolynom.emplace_back(Element(childExpr.compress(), child.inverted));
      } else {
        newPolynom.emplace_back(child);
      }
    }
    return newPolynom;
  }

  std::vector<AddExpression::Element> AddExpression::Element::getAddPolynom() const {
    if(info->is<AddExpression>()){
      Polynom result;
      auto addExpr = info->to<AddExpression>();
      for(const auto& child : addExpr.addPolynom){
        result.emplace_back(Element{child.info->clone(), (bool)((unsigned)child.inverted ^ (unsigned)inverted)});
      }
      return result;
    }
    return {*this};
  }

  AddExpression::Polynom AddExpression::compressTree() const{
    Polynom newPolynom;
    Polynom vect = compressExpression();
    for(const auto& child : vect){
      auto pushPolynom = child.getAddPolynom();
      for(auto& pushChild: pushPolynom){
        newPolynom.emplace_back(pushChild);
      }
    }
    return newPolynom;
  }

  void AddExpression::addElement(const Element &elem){
    addPolynom.emplace_back(elem);
  }


  MathObjectPtr AddExpression::simplify() const {
    if(addPolynom.size() == 1){
      return addPolynom.at(0).toMathObject();
    }

    auto exprObj = *this;

    auto b = exprObj.toString();
    for(auto& obj : exprObj.addPolynom){
      obj.info = obj.info->simplify();
      auto a = obj.info->toString();
      auto c = a;
    }

    b = exprObj.toString();
    exprObj = AddExpression(exprObj.compressTree());

    exprObj.simplifyPolynom();

    if(exprObj.addPolynom.size() == 1){
      return exprObj.addPolynom.at(0).toMathObject();
    }
    return exprObj.clone();
  }

  bool sortFunc(const AddExpression::Element& lhs, const AddExpression::Element& rhs){
    return lhs.info->toString() < rhs.info->toString();
  }

  void AddExpression::sortPolynom(const Polynom& vect, Polynom& numVect, Polynom& mulVect, Polynom& literalVect, Polynom& funcVect, Polynom& powVect){
    for(const auto& child : vect){
      if(child.info->is<MulExpression>()){
        mulVect.emplace_back(child);
        continue;
      }
      if(child.info->is<Expression>()){
        if (auto exprInfo = (child.info->to<Expression>()).getInfo()->clone(); exprInfo->is<Pow>()){
          powVect.emplace_back(child);
          continue;
        } 
        funcVect.emplace_back(child);
        continue;
      }
      if(child.info->instanceOf<IArithmetic>()){
        numVect.emplace_back(child);
        continue;
      }
      if (child.info->instanceOf<ILiteral>()){
        literalVect.emplace_back(child);
        continue;
      }
    }
  }

  void AddExpression::simplifyPolynom(){
    auto numVect = Polynom();
    auto powVect = Polynom();
    auto literalVect = Polynom();
    auto mulVect = Polynom();
    auto funcVect = Polynom();

    sortPolynom(addPolynom, numVect, mulVect, literalVect, funcVect, powVect);

    numVect = sumNumbers(numVect);

    //TODO: pow simplify ??
    
    simplifyMul(mulVect, literalVect, powVect);
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
    Expression result = 0;
    Add add;
    Sub sub;
    for(const auto& elem: numVect){
      if(elem.inverted){
        result = sub(*result.getInfo(), *elem.info);
      } else {
        result = add(*result.getInfo(), *elem.info);
      }
    }
    return {{result.simplify(), false}};
  }

  struct AddExpression::ObjectMul{
    MathObjectPtr obj;
    AddExpression counter;

    ObjectMul(const MathObjectPtr& obj): obj(obj->clone()){}
    ObjectMul(const ObjectMul& objMul) : obj(objMul.obj->clone()), counter(objMul.counter){} 
    void simplifyCounter(){
      counter = AddExpression(*counter.simplify());
    }

    MathObjectPtr getCounterValue() const {
      auto polynom = counter.getPolynom();
      auto countValue = polynom.at(0).info->clone();
      *countValue = polynom.at(0).inverted ? *Neg()(*countValue).simplify() : *countValue;
      return countValue;
    }
  };

  void AddExpression::sortMulObjects(Objects& objs, Polynom& mulVect, Polynom& literalVect, Polynom& powVect){
    for(auto& obj : objs){
      obj.simplifyCounter();
      auto counter = obj.getCounterValue();
      if(counter->to<IComparable>() == Integer(0)){
        continue;
      }
      if(counter->to<IComparable>() == Integer(1) || counter->to<IComparable>() == Integer(-1)){
        if(obj.obj->instanceOf<ILiteral>()){
          literalVect.emplace_back(obj.obj->clone(), counter->to<IComparable>() == Integer(-1));
          continue;
        }
        if(obj.obj->is<Expression>()){
          powVect.emplace_back(obj.obj->clone(), counter->to<IComparable>() == Integer(-1));
          continue;
        }
        if(obj.obj->is<MulExpression>()){
          mulVect.emplace_back(obj.obj->clone(), counter->to<IComparable>() == Integer(-1));
          continue;
        }
      }
      mulVect.emplace_back(Element(Mul()(*obj.obj, *counter).simplify()));
    }
  }

  void AddExpression::simplifyMul(Polynom& mulVect, Polynom& literalVect, Polynom& powVect){
    Objects objs;
    for(const auto& mulObj: mulVect){
      bool added = false;
      auto mulExprPolynom = mulObj.info->to<MulExpression>().getPolynom();
      if(mulExprPolynom.empty()){
        added = true;
      }
      MathObjectPtr number = std::make_unique<Integer>(1);
      if(mulExprPolynom.at(0).info->instanceOf<INumber>()){
        if(mulExprPolynom.at(0).inverted){
          number = Neg()(*mulExprPolynom.at(0).info).simplify();
        } else {
          number = mulExprPolynom.at(0).info->clone();
        }
        mulExprPolynom  = MulExpression::Polynom(mulExprPolynom.begin() + 1, mulExprPolynom.end());
      }
      
      MulExpression mulExpr(mulExprPolynom);
      for(auto& obj: objs){
        if(obj.obj->toString() == mulExpr.toString()){
          obj.counter.addElement(Element(Integer(1).clone() , mulObj.inverted));
          added = true;
          break;
        }
      }
      if(added){
        continue;
      }
      ObjectMul object(mulExpr.clone());
      object.counter.addElement(Element(Integer(1).clone(), mulObj.inverted));
      objs.emplace_back(object);
    }
    for(const auto& litObj: literalVect){
      bool added = false;
      for(auto& obj: objs){
        if(obj.obj->toString() == litObj.info->toString()){
          obj.counter.addElement(Element(Integer(1).clone(), litObj.inverted));
          added = true;
          break;
        }
      }
      if(added){
        continue;
      }
      ObjectMul object(litObj.info);
      object.counter.addElement(Element(Integer(1).clone(), litObj.inverted));
      objs.emplace_back(object);
    }

    for(const auto& powObj: powVect){
      bool added = false;
      for(auto& obj: objs){
        if(obj.obj->toString() == powObj.info->toString()){
          obj.counter.addElement(Element(Integer(1).clone(), powObj.inverted));
          added = true;
          break;
        }
      }
      if(added){
        continue;
      }
      ObjectMul object(powObj.info);
      object.counter.addElement(Element(Integer(1).clone(), powObj.inverted));
      objs.emplace_back(object);
    }

    literalVect.clear();
    mulVect.clear();
    powVect.clear();

    sortMulObjects(objs, mulVect, literalVect, powVect);
  }


}