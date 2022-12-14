#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/exceptions/FunctionCallException.hpp"
#include "fintamath/expressions/AddExpression.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/helpers/Converter.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/numbers/Integer.hpp"
#include <memory>

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

  MulExpression::MulExpression(const IMathObject& rhs){
    if(rhs.is<MulExpression>()){
      *this = rhs.to<MulExpression>();
      return;
    }
    mulPolynom.emplace_back(Element{rhs.clone(), false});
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
    if(!result.empty()&& !mulPolynom.at(0).inverted){
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
  }

  MulExpression::MulExpression(Polynom inMulPolynom) : mulPolynom(std::move(inMulPolynom)) {}

  void MulExpression::parse(const TokenVector & tokens){
    int lastSignPosition = -1;
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
      lastSignPosition = (int)i;
    }
    if(lastSignPosition == -1){
      throw InvalidInputException(*this, " not a MulExpression");
    }

    mulPolynom.emplace_back(Element(IExpression::parse(TokenVector(tokens.begin(), tokens.begin() + (long)lastSignPosition))));

    mulPolynom.emplace_back(Element(IExpression::parse(TokenVector(tokens.begin() + (long)lastSignPosition + 1, tokens.end())), tokens[lastSignPosition] == "/"));

    *this = MulExpression(compressTree());
  }

  MulExpression::Element::Element(MathObjectPtr info, bool inverted) : info(info->clone()), inverted(inverted){}

  MulExpression::Polynom MulExpression::compressExpression() const {
    Polynom newPolynom;
    for(auto& child : mulPolynom){
      if(child.info->is<Expression>()){
        auto childExpr = child.info->to<Expression>();
        newPolynom.emplace_back(Element(childExpr.compress(), child.inverted));
      } else {
        newPolynom.emplace_back(child);
      }
    }
    return newPolynom;
  }

  std::vector<MulExpression::Element> MulExpression::Element::getMulPolynom() const {
    if(info->is<MulExpression>()){
      Polynom result;
      auto mulExpr = info->to<MulExpression>();
      for(auto& child : mulExpr.mulPolynom){
        result.emplace_back(Element{child.info->clone(), (bool)((unsigned)child.inverted ^ (unsigned)inverted)});
      }
      return result;
    }
    return {*this};
  }

  MathObjectPtr MulExpression::Element::toMathObject() const {
    if(inverted){
        return Pow()(*info, *std::make_unique<Integer>(-1)).simplify();
      }
      return info->simplify();
  }


  MulExpression::Polynom MulExpression::compressTree() const {
    Polynom newPolynom;
    Polynom vect = compressExpression();
    for(const auto& child : vect){
      auto pushPolynom = child.getMulPolynom();
      for(auto& pushChild: pushPolynom){
        newPolynom.emplace_back(pushChild);
      }
    }
    return newPolynom;
  }

  void MulExpression::addElement(const Element &elem){
    mulPolynom.emplace_back(elem);
  }

  MathObjectPtr MulExpression::simplify() const {
    if(mulPolynom.size() == 1){
      return mulPolynom.at(0).toMathObject();
    }

    auto exprObj = *this;

    auto a = toString();

    for(auto& obj : exprObj.mulPolynom){
      obj.info = obj.info->simplify();
    }

    exprObj.simplifyPolynom();
    
    if(exprObj.mulPolynom.size() == 1){
      return exprObj.mulPolynom.at(0).toMathObject();
    }
    return exprObj.clone();
  }

  MulExpression::Polynom MulExpression::mulNumbers(const Polynom& numVect){
    Expression result = 1;
    Mul mul;
    Div div;
    for(const auto& elem: numVect){
      if(elem.inverted){
        result = div(*result.getInfo(), *elem.info);
      } else {
        result = mul(*result.getInfo(), *elem.info);
      }
    }
    return {{result.simplify(), false}};
  }

  //TODO: перемнжение скобок: отрефакторить, мб переписать
  /*MulExpression::Polynom MulExpression::multiplicateTwoBraces(const Polynom& lhs, const Polynom& rhs){
    Polynom result;
    for(const auto& lhsElem:lhs){
      for(const auto& rhsElem: rhs){
        auto polynom = lhsElem.info->to<MulExpression>().getPolynom();
        polynom.emplace_back(Element{rhsElem.info->clone()});
        result.emplace_back(Element{std::make_unique<MulExpression>(polynom), (bool)(lhsElem.inverted ^ rhsElem.inverted)});
      }
    }
    return result;
  }*/

  /*MulExpression::Polynom convertAddPolynomToMul(const AddExpression::Polynom& polynom){
    MulExpression::Polynom result;
    for(const auto& elem : polynom){
      result.emplace_back(MulExpression::Element(elem.info->clone(), elem.inverted));
    }
    return result;
  }*/

  /*AddExpression::Polynom convertMulPolynomToAdd(const MulExpression::Polynom& polynom){
    AddExpression::Polynom result;
    for(const auto& elem : polynom){
      result.emplace_back(AddExpression::Element(elem.info->clone(), elem.inverted));
    }
    return result;
  }*/

  /*MulExpression::Polynom MulExpression::divideBraceByObj(const Polynom& lhs, const Polynom& rhs){
    Polynom result = lhs;
    for(auto& elem : result){
      auto polynom = elem.info->to<MulExpression>().getPolynom();
      polynom.emplace_back(Element{rhs.at(0).info->clone(), true});
      elem.inverted = elem.inverted ^ rhs.at(0).inverted;
      elem.info = std::make_unique<MulExpression>(polynom);
    }
    return result;
  }*/

  /*MulExpression::Polynom MulExpression::multiplicateBraces(const Polynom& addVect){
    if(addVect.empty()){
      return {};
    }
    Polynom result;
    Polynom addResult = {{std::make_unique<MulExpression>(Polynom{{std::make_unique<Expression>(1), false}})}};
    Polynom divideResult = {{std::make_unique<MulExpression>(Polynom{{std::make_unique<Expression>(1), false}})}};
    for(const auto& elem : addVect){      
      auto addPolynom = elem.info->to<AddExpression>().getPolynom();
      if(elem.inverted){
        if(addPolynom.size() != 1){
          divideResult = multiplicateTwoBraces(divideResult, convertAddPolynomToMul(addPolynom));
          continue;
        }
        addResult = divideBraceByObj(addResult, convertAddPolynomToMul(addPolynom));
        continue;
      }
      addResult = multiplicateTwoBraces(addResult, convertAddPolynomToMul(addPolynom));
    }

    auto addResultAddPolynom = convertMulPolynomToAdd(addResult);
    if(addResultAddPolynom.size() != 1 || addResultAddPolynom.at(0).info->toString() != "1" || addResultAddPolynom.at(0).inverted){
      result.emplace_back(Element{std::make_unique<AddExpression>(addResultAddPolynom), false});
    }
    
    auto divideResultDividePolynom = convertMulPolynomToAdd(divideResult);
    if(divideResultDividePolynom.size() == 1 && divideResultDividePolynom.at(0).info->toString() == "1" && !divideResultDividePolynom.at(0).inverted){
      return result;
    }
    result.emplace_back(Element{std::make_unique<AddExpression>(divideResultDividePolynom), true});
    return result;
  }*/

  bool sortFunc(const MulExpression::Element& lhs, const MulExpression::Element& rhs){
    return lhs.info->toString() < rhs.info->toString();
  }

  struct MulExpression::ObjectPow{
    MathObjectPtr obj;
    AddExpression pow;
    ObjectPow(const MathObjectPtr& obj): obj(obj->clone()){}
    ObjectPow(const ObjectPow& objPow) : pow(objPow.pow){
      obj = objPow.obj->clone();
    }

    MathObjectPtr getPowIfInteger() const{
      auto polynom = pow.getPolynom();
      if(polynom.size() != 1){
        return nullptr;
      }
      auto powValue = polynom.at(0).info->clone();
      *powValue = polynom.at(0).inverted ? *Neg()(*powValue).simplify() : *powValue;
      if(powValue->is<Integer>()){
        return powValue;
      }
      return nullptr;
    }
    MathObjectPtr getPowIfSingle() const {
      auto polynom = pow.getPolynom();
      if(polynom.size() != 1){
        return nullptr;
      }
      auto powValue = polynom.at(0).info->clone();
      *powValue = polynom.at(0).inverted ? *Neg()(*powValue).simplify() : *powValue;
      return powValue;
    }

    void simplifyPow(){
      pow = AddExpression(*pow.simplify());
    }
  };

  void MulExpression::sortPowObjects(Objects& objs, Polynom& powVect, Polynom& addVect, Polynom& literalVect){
    for(auto& obj : objs){
      obj.simplifyPow();
      if(auto numObj = obj.getPowIfInteger()){
        auto num = numObj->to<Integer>();
        if(num == 0){
          continue;
        }
        if(obj.obj->instanceOf<ILiteral>()) {
          if((num == 1) || (num == -1)){
            literalVect.emplace_back(Element(obj.obj->clone(), num == -1));
            continue;
          }
          powVect.emplace_back(Element(Pow()(*obj.obj, num).simplify()));
          continue;
        }

        auto oldNum = num;
        if(num < 0){
          num = -num;
        }
        for(Integer i = 0;i < num; i++){
          addVect.emplace_back(Element(obj.obj->clone(), oldNum < 0));
        }
        continue;
      }
      
      if(auto exprObj = obj.getPowIfSingle()){
        powVect.emplace_back(Element(Pow()(*obj.obj, *exprObj).simplify()));
      } else {
        powVect.emplace_back(Element(Pow()(*obj.obj, obj.pow).simplify()));
      }
    }
  }

  void MulExpression::simplifyPow(Polynom& powVect, Polynom& addVect, Polynom& literalVect){
    Objects objects;
    for(const auto& addObj: addVect){
      bool added = false;
      for(auto& obj: objects){
        if(obj.obj->toString() == addObj.info->toString()){
          obj.pow.addElement({std::make_unique<Integer>(1),addObj.inverted});
          added = true;
          break;
        }
      }
      if(added){
        continue;
      }
      ObjectPow obj(addObj.info);
      obj.pow.addElement({std::make_unique<Integer>(1), addObj.inverted});
      objects.emplace_back(obj);
    }

    for(const auto& litObj: literalVect){
      bool added = false;
      for(auto& obj: objects){
        if(obj.obj->toString() == litObj.info->toString()){
          obj.pow.addElement({std::make_unique<Integer>(1), litObj.inverted});
          added = true;
          break;
        }
      }
      if(added){
        continue;
      }
      ObjectPow obj(litObj.info);
      obj.pow.addElement({std::make_unique<Integer>(1), litObj.inverted});
      objects.emplace_back(obj);
    }

    for(const auto& powObj: powVect){
      bool added = false;
      auto expr = powObj.info->to<Expression>();
      
      auto leftValue = expr.getChildren().at(0)->clone();
      auto rightValue = expr.getChildren().at(1)->clone();
      for(auto& obj: objects){
        if(obj.obj->toString() == leftValue->toString()){
          obj.pow.addElement({rightValue->clone(),powObj.inverted});
          added = true;
          break;
        }
      }
      if(added){
        continue;
      }
      ObjectPow obj(leftValue);
      obj.pow.addElement({rightValue->clone(),powObj.inverted});
      objects.emplace_back(obj);
    }

    powVect.clear();
    literalVect.clear();
    addVect.clear();

    sortPowObjects(objects, powVect, addVect, literalVect);
  }

  void MulExpression::sortPolynom(const Polynom& vect, Polynom& numVect, Polynom& addVect, Polynom& literalVect, Polynom& funcVect, Polynom& powVect){
    for(const auto& child : vect){
      if(child.info->is<AddExpression>()){
        addVect.emplace_back(child);
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


  void MulExpression::simplifyPolynom(){
    auto numVect = Polynom();
    auto powVect = Polynom();
    auto literalVect = Polynom();
    auto addVect = Polynom();
    auto funcVect = Polynom();
    
    auto b = toString();

    sortPolynom(mulPolynom, numVect, addVect, literalVect, funcVect, powVect);

    Polynom tmpVect = openPowMulExpression(powVect);
    powVect.clear();

    sortPolynom(tmpVect, numVect, addVect, literalVect, funcVect, powVect);

    numVect = mulNumbers(numVect);

    simplifyPow(powVect, addVect, literalVect);    

    //TODO: перемножение скобок, потом перемножение со всем остальным
    //addVect = multiplicateBraces(addVect);

    mulPolynom.clear();

    std::sort(funcVect.begin(), funcVect.end(), sortFunc);
    std::sort(powVect.begin(), powVect.end(), sortFunc);
    std::sort(literalVect.begin(), literalVect.end(), sortFunc);
    std::sort(addVect.begin(), addVect.end(), sortFunc);


    pushPolynomToPolynom<MulExpression>(funcVect, mulPolynom);
    pushPolynomToPolynom<MulExpression>(powVect, mulPolynom);
    pushPolynomToPolynom<MulExpression>(addVect, mulPolynom);
    pushPolynomToPolynom<MulExpression>(literalVect, mulPolynom);
    if(numVect.at(0).info->toString() != "1" || mulPolynom.empty()){
      pushPolynomToPolynom<MulExpression>(mulPolynom, numVect);
      mulPolynom = numVect;
    }
  }

  MulExpression::Polynom MulExpression::openPowMulExpression(const Polynom& powVect){
    Polynom newPowVect;

    for(const auto& pow : powVect){
      auto expr = pow.info->to<Expression>();
      auto left = expr.getChildren().at(0)->clone();
      if(!left->is<MulExpression>()){
        newPowVect.emplace_back(pow);
        continue;
      }
      auto right = expr.getChildren().at(1)->clone();
      auto mulExpr = left->to<MulExpression>();
      for(const auto& child: mulExpr.mulPolynom){
        newPowVect.emplace_back(Element{Pow()(*child.info, *right).simplify(), child.inverted});
      }
    }
    return newPowVect;
  }

}
