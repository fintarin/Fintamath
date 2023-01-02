#include "fintamath/expressions/AddExpression.hpp"

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IComparable.hpp"
#include "fintamath/exceptions/Exception.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/expressions/EqvExpression.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/helpers/Caster.hpp"
#include "fintamath/helpers/Converter.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

#include <algorithm>
#include <cstdint>
#include <memory>
#include <regex>

namespace fintamath {

AddExpression::AddExpression(const AddExpression &rhs) noexcept : addPolynom(rhs.addPolynom) {
}

AddExpression::AddExpression(AddExpression &&rhs) noexcept : addPolynom(std::move(rhs.addPolynom)) {
}

AddExpression &AddExpression::operator=(const AddExpression &rhs) noexcept {
  if (&rhs != this) {
    addPolynom = rhs.addPolynom;
  }
  return *this;
}

AddExpression &AddExpression::operator=(AddExpression &&rhs) noexcept {
  if (&rhs != this) {
    std::swap(addPolynom, rhs.addPolynom);
  }
  return *this;
}

AddExpression::AddExpression(const TokenVector &tokens) {
  parse(tokens);
}

AddExpression::AddExpression(const IMathObject &rhs) {
  if (rhs.is<AddExpression>()) {
    *this = rhs.to<AddExpression>();
    return;
  }
  addPolynom.emplace_back(Element{rhs.clone(), false});
}

AddExpression::AddExpression(Polynom inAddPolynom) : addPolynom(std::move(inAddPolynom)) {
}

uint16_t AddExpression::getBaseOperatorPriority() const {
  return (uint16_t)IOperator::Priority::Addition;
}

void AddExpression::setPrecision(uint8_t precision) {
  for (auto &child : addPolynom) {
    child.setPrecision(precision);
  }
}

std::string AddExpression::toString() const {
  std::string result;

  for (const auto &var : addPolynom) {
    result += var.inverted ? '-' : '+';
    result += tryPutInBracketsIfNeg(var.info);
  }

  if (!result.empty() && result.at(0) == '+') {
    result.erase(result.begin());
  }

  result = std::regex_replace(result, std::regex(R"(\+\+|\-\-)"), "+");
  result = std::regex_replace(result, std::regex(R"(\+\-|\+\-)"), "-");

  return result;
}

void AddExpression::invert() {
  for (auto &child : addPolynom) {
    child.inverted = !child.inverted;
  }
}

const AddExpression::Polynom &AddExpression::getPolynom() const {
  return addPolynom;
}

void AddExpression::parse(const TokenVector &tokens) {
  int lastSignPosition = -1;
  for (size_t i = 0; i < tokens.size(); i++) {
    if (skipBrackets(tokens, i)) {
      i--;
      continue;
    }
    if (tokens.at(i) != "+" && tokens.at(i) != "-") {
      continue;
    }
    if (i == tokens.size() - 1) {
      throw InvalidInputException(" unexpected sign");
    }
    if (i == 0 || (isOneSymbolToken(tokens.at(i - 1)) && tokens.at(i - 1) != "%" && tokens.at(i - 1) != "!")) {
      continue;
    }
    lastSignPosition = (int)i;
  }

  if (lastSignPosition == -1) {
    throw InvalidInputException(" not an AddExpression");
  }
  auto leftExpr = IExpression::parse(TokenVector(tokens.begin(), tokens.begin() + (long)lastSignPosition));
  auto rightExpr = IExpression::parse(TokenVector(tokens.begin() + (long)lastSignPosition + 1, tokens.end()));

  if (!leftExpr || !rightExpr) {
    throw InvalidInputException(tokensToString(tokens));
  }

  addPolynom.emplace_back(Element(leftExpr->clone()));
  addPolynom.emplace_back(Element(rightExpr->clone(), tokens.at(lastSignPosition) == "-"));

  *this = AddExpression(compressTree());
}

AddExpression::Element::Element(const Element &rhs) : info(rhs.info->clone()), inverted(rhs.inverted) {
}

AddExpression::Element &AddExpression::Element::operator=(const Element &rhs) {
  if (this != &rhs) {
    info = rhs.info->clone();
    inverted = rhs.inverted;
  }
  return *this;
}

void AddExpression::Element::setPrecision(uint8_t precision) {
  if (info->instanceOf<INumber>()) {
    info = helpers::Converter::convert(*info, Real())->to<Real>().precise(precision).clone();
  }

  if (info->instanceOf<IExpression>()) {
    auto copyExpr = helpers::cast<IExpression>(info->clone());
    copyExpr->setPrecision(precision);
    info = copyExpr->clone();
  }

  if (info->instanceOf<IConstant>()) {
    info = (*helpers::cast<IConstant>(info->clone()))().simplify();
    auto a = info->toString();
    info = helpers::Converter::convert(*info, Real())->to<Real>().precise(precision).clone();
  }
}

AddExpression::Element::Element(const MathObjectPtr &info, bool inverted) : info(info->clone()), inverted(inverted) {
}

MathObjectPtr AddExpression::Element::toMathObject(bool isPrecise) const {
  auto copy = *this;
  if (copy.inverted) {
    copy.info = Neg()(*info);
    copy.simplify(isPrecise);
    return copy.info->clone();
  }
  copy.simplify(isPrecise);
  return copy.info->clone();
}

void AddExpression::Element::simplify(bool isPrecise) {
  if (info->instanceOf<IExpression>()) {
    info = info->to<IExpression>().simplify(isPrecise);
    return;
  }
  if (info->instanceOf<IConstant>()) {
    auto constant = (*helpers::cast<IConstant>(info->clone()))().simplify();
    if (!isPrecise || constant->to<INumber>().isPrecise()) {
      info = constant->clone();
      return;
    }
    info = info->simplify();
    return;
  }
  info = info->simplify();
}

AddExpression::Polynom AddExpression::compressExpression() const {
  Polynom newPolynom;
  for (auto &child : addPolynom) {
    if (child.info->is<Expression>()) {
      auto childExpr = child.info->to<Expression>();
      newPolynom.emplace_back(Element(childExpr.compress(), child.inverted));
    } else {
      newPolynom.emplace_back(child);
    }
  }
  return newPolynom;
}

std::vector<AddExpression::Element> AddExpression::Element::getAddPolynom() const {
  if (info->is<AddExpression>()) {
    Polynom result;
    auto addExpr = info->to<AddExpression>();
    for (const auto &child : addExpr.addPolynom) {
      result.emplace_back(Element{child.info->clone(), (bool)((unsigned)child.inverted ^ (unsigned)inverted)});
    }
    return result;
  }
  return {*this};
}

AddExpression::Polynom AddExpression::compressTree() const {
  Polynom newPolynom;
  Polynom vect = compressExpression();
  for (const auto &child : vect) {
    auto pushPolynom = child.getAddPolynom();
    for (auto &pushChild : pushPolynom) {
      newPolynom.emplace_back(pushChild);
    }
  }
  return newPolynom;
}

void AddExpression::addElement(const Element &elem) {
  addPolynom.emplace_back(elem);
}

MathObjectPtr AddExpression::simplify() const {
  return simplify(true);
}

MathObjectPtr AddExpression::simplify(bool isPrecise) const {
  auto exprObj = AddExpression(compressTree());

  for (auto &obj : exprObj.addPolynom) { // TODO: find a better solution
    if (obj.info->is<EqvExpression>()) {
      throw InvalidInputException(toString());
    }
  }

  if (exprObj.addPolynom.size() == 1) {
    return exprObj.addPolynom.at(0).toMathObject(isPrecise);
  }

  for (auto &obj : exprObj.addPolynom) {
    obj.simplify(isPrecise);
  }

  if (!exprObj.addPolynom.empty()) { // TODO move to IExpression
    static const Add func;
    for (size_t i = 0; i < exprObj.addPolynom.size() - 1; i++) {
      validateFunctionArgs(func, {*exprObj.addPolynom.at(i).info, *exprObj.addPolynom.at(i + 1).info});
    }
  }

  exprObj = AddExpression(exprObj.compressTree());
  exprObj.simplifyPolynom();

  if (exprObj.addPolynom.size() == 1) {
    return exprObj.addPolynom.at(0).toMathObject(isPrecise);
  }
  return exprObj.clone();
}

bool sortFunc(const AddExpression::Element &lhs, const AddExpression::Element &rhs) {
  return lhs.info->toString() < rhs.info->toString();
}

void AddExpression::sortPolynom(const Polynom &vect, Polynom &numVect, Polynom &mulVect, Polynom &literalVect,
                                Polynom &funcVect, Polynom &powVect) {
  for (const auto &child : vect) {
    if (child.info->is<MulExpression>()) {
      mulVect.emplace_back(child);
      continue;
    }
    if (child.info->is<Expression>()) {
      if (auto exprInfo = (child.info->to<Expression>()).getInfo()->clone(); exprInfo->is<Pow>()) {
        powVect.emplace_back(child);
        continue;
      }
      funcVect.emplace_back(child);
      continue;
    }
    if (child.info->instanceOf<IArithmetic>()) {
      numVect.emplace_back(child);
      continue;
    }
    if (child.info->instanceOf<ILiteral>()) {
      literalVect.emplace_back(child);
      continue;
    }
  }
}

void AddExpression::simplifyPolynom() {
  auto numVect = Polynom();
  auto powVect = Polynom();
  auto literalVect = Polynom();
  auto mulVect = Polynom();
  auto funcVect = Polynom();

  sortPolynom(addPolynom, numVect, mulVect, literalVect, funcVect, powVect);

  numVect = sumNumbers(numVect);

  simplifyMul(powVect, mulVect, literalVect, funcVect);
  addPolynom.clear();

  std::sort(funcVect.begin(), funcVect.end(), sortFunc);
  std::sort(powVect.begin(), powVect.end(), sortFunc);
  std::sort(literalVect.begin(), literalVect.end(), sortFunc);
  std::sort(mulVect.begin(), mulVect.end(), sortFunc);

  pushPolynomToPolynom<AddExpression>(funcVect, addPolynom);
  pushPolynomToPolynom<AddExpression>(powVect, addPolynom);
  pushPolynomToPolynom<AddExpression>(mulVect, addPolynom);
  pushPolynomToPolynom<AddExpression>(literalVect, addPolynom);
  if (numVect.at(0).info->toString() != "0" || addPolynom.empty()) {
    pushPolynomToPolynom<AddExpression>(numVect, addPolynom);
  }
}

AddExpression::Polynom AddExpression::sumNumbers(const Polynom &numVect) {
  Expression result;
  for (const auto &elem : numVect) {
    if (elem.inverted) {
      result.getInfo() = Sub()(*result.getInfo(), *elem.info);
    } else {
      result.getInfo() = Add()(*result.getInfo(), *elem.info);
    }
  }
  return {{result.simplify(), false}};
}

struct AddExpression::ObjectMul {
  MathObjectPtr obj;
  AddExpression counter;

  ObjectMul(const MathObjectPtr &obj) : obj(obj->clone()) {
  }
  ObjectMul(const ObjectMul &objMul) : obj(objMul.obj->clone()), counter(objMul.counter) {
  }
  void simplifyCounter() {
    counter = AddExpression(*counter.simplify());
  }

  MathObjectPtr getCounterValue() const {
    auto polynom = counter.getPolynom();
    auto countValue = polynom.at(0).info->clone();
    return polynom.at(0).inverted ? Neg()(*countValue) : std::move(countValue);
  }
};

void AddExpression::sortMulObjects(Objects &objs, Polynom &mulVect, Polynom &literalVect, Polynom &powVect) {
  for (auto &obj : objs) {
    obj.simplifyCounter();
    auto counter = obj.getCounterValue();
    if (counter->to<IComparable>() == Integer(0)) {
      continue;
    }
    if (counter->to<IComparable>() == Integer(1) || counter->to<IComparable>() == Integer(-1)) {
      if (obj.obj->instanceOf<ILiteral>()) {
        literalVect.emplace_back(obj.obj->clone(), counter->to<IComparable>() == Integer(-1));
        continue;
      }
      if (obj.obj->is<Expression>()) {
        powVect.emplace_back(obj.obj->clone(), counter->to<IComparable>() == Integer(-1));
        continue;
      }
      if (obj.obj->is<MulExpression>()) {
        mulVect.emplace_back(obj.obj->clone(), counter->to<IComparable>() == Integer(-1));
        continue;
      }
    }
    auto a = counter->toString();
    mulVect.emplace_back(
        Element(MulExpression({MulExpression::Element(obj.obj->clone()), MulExpression::Element(counter->clone())})
                    .simplify()));
  }
}

void AddExpression::simplifyMul(Polynom &powVect, Polynom &mulVect, Polynom &literalVect, Polynom &funcVect) {
  Objects objs;
  for (const auto &mulObj : mulVect) {
    bool added = false;
    auto mulExprPolynom = mulObj.info->to<MulExpression>().getPolynom();
    if (mulExprPolynom.empty()) {
      added = true;
    }
    MathObjectPtr number = std::make_unique<Integer>(1);
    if (mulExprPolynom.at(0).info->instanceOf<INumber>()) {
      if (mulExprPolynom.at(0).inverted) {
        number = Neg()(*mulExprPolynom.at(0).info);
      } else {
        number = mulExprPolynom.at(0).info->clone();
      }
      mulExprPolynom = MulExpression::Polynom(mulExprPolynom.begin() + 1, mulExprPolynom.end());
    }

    MulExpression mulExpr(mulExprPolynom);
    for (auto &obj : objs) {
      if (obj.obj->toString() == mulExpr.toString()) {
        obj.counter.addElement(Element(number->clone(), mulObj.inverted));
        added = true;
        break;
      }
    }
    if (added) {
      continue;
    }
    ObjectMul object(mulExpr.clone());
    object.counter.addElement(Element(number->clone(), mulObj.inverted));
    objs.emplace_back(object);
  }
  for (const auto &litObj : literalVect) {
    bool added = false;
    for (auto &obj : objs) {
      if (obj.obj->toString() == litObj.info->toString()) {
        obj.counter.addElement(Element(Integer(1).clone(), litObj.inverted));
        added = true;
        break;
      }
    }
    if (added) {
      continue;
    }
    ObjectMul object(litObj.info);
    object.counter.addElement(Element(Integer(1).clone(), litObj.inverted));
    objs.emplace_back(object);
  }
  for (const auto &funcObj : funcVect) {
    bool added = false;
    for (auto &obj : objs) {
      if (obj.obj->toString() == funcObj.info->toString()) {
        obj.counter.addElement(Element(Integer(1).clone(), funcObj.inverted));
        added = true;
        break;
      }
    }
    if (added) {
      continue;
    }
    ObjectMul object(funcObj.info);
    object.counter.addElement(Element(Integer(1).clone(), funcObj.inverted));
    objs.emplace_back(object);
  }

  for (const auto &powObj : powVect) {
    bool added = false;
    for (auto &obj : objs) {
      if (obj.obj->toString() == powObj.info->toString()) {
        obj.counter.addElement(Element(Integer(1).clone(), powObj.inverted));
        added = true;
        break;
      }
    }
    if (added) {
      continue;
    }
    ObjectMul object(powObj.info);
    object.counter.addElement(Element(Integer(1).clone(), powObj.inverted));
    objs.emplace_back(object);
  }

  literalVect.clear();
  mulVect.clear();
  powVect.clear();
  funcVect.clear();

  sortMulObjects(objs, mulVect, literalVect, powVect);
}

std::vector<MathObjectPtr> AddExpression::getVariables() const {
  std::vector<MathObjectPtr> result;
  for (const auto &child : addPolynom) {
    if (child.info->is<Variable>()) {
      result.emplace_back(child.info->clone());
      continue;
    }
    if (child.info->instanceOf<IExpression>()) {
      auto addResult = child.info->to<IExpression>().getVariables();
      for (const auto &add : addResult) {
        result.emplace_back(add->clone());
      }
    }
  }
  return result;
}

MathObjectPtr AddExpression::getPowCoefficient(const MathObjectPtr &powValue) const {
  if (powValue->instanceOf<IComparable>() && powValue->to<IComparable>() == Integer(0)) {
    for (const auto &child : addPolynom) {
      if (child.info->instanceOf<INumber>()) {
        return child.toMathObject(false);
      }
    }
  }

  if (powValue->instanceOf<IComparable>() && powValue->to<IComparable>() == Integer(1)) {
    for (const auto &child : addPolynom) {
      if (child.info->is<Variable>()) {
        return child.inverted ? Integer(-1).clone() : Integer(1).clone();
      }
    }
  }

  for (const auto &child : addPolynom) {
    if (child.info->is<MulExpression>()) {
      if (auto result = child.info->to<MulExpression>().getPowCoefficient(powValue->clone())) {
        return child.inverted ? Neg()(*result) : result->clone();
      }
    }
    if (child.info->is<Expression>()) {
      if (child.info->to<Expression>().getInfo()->is<Pow>()) {
        auto rightVal = child.info->to<Expression>().getChildren().at(1)->clone();
        if (rightVal->instanceOf<IComparable>() && powValue->instanceOf<IComparable>() &&
            rightVal->to<IComparable>() == powValue->to<IComparable>()) {
          return child.inverted ? Integer(-1).clone() : Integer(1).clone();
        }
      }
    }
  }
  return Integer(0).clone();
}

MathObjectPtr AddExpression::getPow() const {
  auto maxValue = Integer(0);
  for (const auto &child : addPolynom) {
    if (child.info->is<MulExpression>()) {
      auto pow = child.info->to<MulExpression>().getPow();
      if (pow->is<Integer>() && pow->to<Integer>() > maxValue) {
        maxValue = pow->to<Integer>();
      }
    }
    if (child.info->is<Expression>()) {
      if (child.info->to<Expression>().getInfo()->is<Pow>()) {
        auto rightVal = child.info->to<Expression>().getChildren().at(1)->clone();
        if (rightVal->is<Integer>() && rightVal->to<Integer>() > maxValue) {
          maxValue = rightVal->to<Integer>();
        }
      }
    }
    if (child.info->is<Variable>()) {
      if (Integer(1) > maxValue) {
        maxValue = Integer(1);
      }
    }
  }
  return maxValue.clone();
}

}