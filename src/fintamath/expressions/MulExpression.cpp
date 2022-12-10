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
    *this = simplify()->to<MulExpression>();
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
    *this = simplify()->to<MulExpression>();
  }

  MathObjectPtr MulExpression::simplify() const {
    auto exprPtr = tryCompressExpression();
    auto exprObj = helpers::cast<MulExpression>(exprPtr);

    exprPtr = exprObj->tryCompressTree();
    exprObj = helpers::cast<MulExpression>(exprPtr);

    exprObj->sortPolynom();
    
    return exprObj;
  }

  MulExpression::Polynom MulExpression::mulNumbers(const Polynom& numVect){
    Expression expr = 1;
    Mul mul;
    Div div;
    for(const auto& elem: numVect){
      auto exprNum = elem.info->to<Expression>();
      if(elem.inverted){
        expr = div(*expr.getInfo(), *exprNum.getInfo());
      } else {
        expr = mul(*expr.getInfo(), *exprNum.getInfo());
      }
    }
    return {{std::make_unique<Expression>(expr), false}};

  }

  MulExpression::Polynom MulExpression::multiplicateTwoBraces(const Polynom& lhs, const Polynom& rhs){
    Polynom result;
    for(const auto& lhsElem:lhs){
      for(const auto& rhsElem: rhs){
        auto polynom = lhsElem.info->to<MulExpression>().getPolynom();
        polynom.emplace_back(Element{rhsElem.info->clone()});
        result.emplace_back(Element{std::make_unique<MulExpression>(polynom), (bool)(lhsElem.inverted ^ rhsElem.inverted)});
      }
    }
    return result;
  }

  MulExpression::Polynom convertAddPolynomToMul(const AddExpression::Polynom& polynom){
    MulExpression::Polynom result;
    for(const auto& elem : polynom){
      result.emplace_back(MulExpression::Element(elem.info->clone(), elem.inverted));
    }
    return result;
  }

  AddExpression::Polynom convertMulPolynomToAdd(const MulExpression::Polynom& polynom){
    AddExpression::Polynom result;
    for(const auto& elem : polynom){
      result.emplace_back(AddExpression::Element(elem.info->clone(), elem.inverted));
    }
    return result;
  }

  MulExpression::Polynom MulExpression::divideBraceByObj(const Polynom& lhs, const Polynom& rhs){
    Polynom result = lhs;
    for(auto& elem : result){
      auto polynom = elem.info->to<MulExpression>().getPolynom();
      polynom.emplace_back(Element{rhs.at(0).info->clone(), true});
      elem.inverted = elem.inverted ^ rhs.at(0).inverted;
      elem.info = std::make_unique<MulExpression>(polynom);
    }
    return result;
  }

  MulExpression::Polynom MulExpression::multiplicateBraces(const Polynom& addVect){
    if(addVect.empty()){
      return {};
    }
    Polynom result;
    Polynom addResult = {{std::make_unique<MulExpression>(Polynom{{std::make_unique<Expression>(1), false}}), false}} ;
    for(const auto& elem : addVect){      
      if(elem.inverted){
        auto addPolynom = elem.info->to<AddExpression>().getPolynom();
        if(addPolynom.size() == 1){
          addResult = divideBraceByObj(addResult, convertAddPolynomToMul(addPolynom));
          continue;
        }
        result.emplace_back(elem);
        continue;
      }
      auto addPolynom = elem.info->to<AddExpression>().getPolynom();
      addResult = multiplicateTwoBraces(addResult, convertAddPolynomToMul(addPolynom));
    }
    auto addResultAddPolynom = convertMulPolynomToAdd(addResult);
    result.emplace_back(Element{std::make_unique<AddExpression>(addResultAddPolynom), false});
    return result;
  }

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
      auto expr = helpers::cast<Expression>(polynom.at(0).info);
      *expr = polynom.at(0).inverted ? Neg()(*expr) : *expr;
      auto exprInfo = expr->getInfo()->clone();
      if(exprInfo->is<Integer>()){
        return exprInfo;
      }
      return nullptr;
    }
  };

  void MulExpression::sortPowObjects(const Objects& objs, Polynom& powVect, Polynom& addVect, Polynom& literalVect){
    
  }

  void MulExpression::simplifyPow(Polynom& powVect, Polynom& addVect, Polynom& literalVect){
    Objects objects;
    for(auto& addObj: addVect){
      bool added = false;
      for(auto& obj: objects){
        if(obj.obj->toString() == addObj.info->toString()){
          obj.pow.addElement({std::make_unique<Expression>(Integer(1)),addObj.inverted});
          added = true;
          break;
        }
      }
      if(added){
        continue;
      }
      ObjectPow obj(addObj.info);
      obj.pow.addElement({std::make_unique<Expression>(Integer(1)),addObj.inverted});
      objects.emplace_back(obj);
    }

    for(auto& litObj: literalVect){
      bool added = false;
      for(auto& obj: objects){
        if(obj.obj->toString() == litObj.info->toString()){
          obj.pow.addElement({std::make_unique<Expression>(Integer(1)),litObj.inverted});
          added = true;
          break;
        }
      }
      if(added){
        continue;
      }
      ObjectPow obj(litObj.info);
      obj.pow.addElement({std::make_unique<Expression>(Integer(1)),litObj.inverted});
      objects.emplace_back(obj);
    }

    for(auto& powObj: powVect){
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
  }

  void MulExpression::sortPolynom(){
    auto numVect = Polynom();
    auto powVect = Polynom();
    auto literalVect = Polynom();
    auto addVect = Polynom();
    auto funcVect = Polynom();

    for(const auto& child : mulPolynom){
      if(child.info->is<AddExpression>()){
        addVect.emplace_back(child);
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

    numVect = mulNumbers(numVect);

    addVect = multiplicateBraces(addVect);

    mulPolynom.clear();

    std::sort(funcVect.begin(), funcVect.end(), sortFunc);
    std::sort(powVect.begin(), powVect.end(), sortFunc);
    std::sort(literalVect.begin(), literalVect.end(), sortFunc);
    std::sort(addVect.begin(), addVect.end(), sortFunc);


    if(numVect.size() != 1 || numVect.at(0).info->toString() != "1"){
      pushPolynomToPolynom<MulExpression>(numVect, mulPolynom);
    }
    pushPolynomToPolynom<MulExpression>(funcVect, mulPolynom);
    pushPolynomToPolynom<MulExpression>(powVect, mulPolynom);
    pushPolynomToPolynom<MulExpression>(addVect, mulPolynom);
    pushPolynomToPolynom<MulExpression>(literalVect, mulPolynom);
  }
}
