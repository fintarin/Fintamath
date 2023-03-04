#pragma once

#include <memory>
#include <vector>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/parser/Parser.hpp"
#include "fintamath/parser/Tokenizer.hpp"

namespace fintamath {

class IExpression;
using ExpressionPtr = std::unique_ptr<IExpression>;

class IExpression : virtual public IMathObject {
public:
  virtual const IFunction *getFunction() const = 0;

  virtual void setPrecision(uint8_t precision) = 0;

  // TODO: add this
  // virtual void toMinimalObject() = 0;

  // TODO: remove this and move simplify(false) logic to setPrecision
  virtual MathObjectPtr simplify(bool isPrecise) const = 0;

  MathObjectPtr toMinimalObject() const final;

  // TODO: remove this and prevent Expression in Expression situations
  virtual void compress() {
  }

  // TODO: remove this and implement in Expression using IExpression::Iterator
  virtual void validate() const = 0;

  // TODO: make this non virtual using IExpression::Iterator
  virtual std::vector<MathObjectPtr> getVariables() const {
    return {};
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IExpression, T>>>
  static void registerType() {
    Parser::registerType<T>(parserVector);
  }

  static ExpressionPtr parse(const std::string &str) {
    return Parser::parse(parserVector, str);
  }

protected:
  // TODO: remove this and implement in Expression using IExpression::Iterator
  void validateArgs(const IFunction &func, const ArgumentsVector &args) const;

  static std::string putInBrackets(const std::string &str);

  static std::string binaryOperatorToString(const IOperator &oper, const ArgumentsPtrVector &values);

  static std::string postfixUnaryOperatorToString(const IOperator &oper, const MathObjectPtr &lhs);

  static void simplifyExpr(MathObjectPtr &obj);

  static void setMathObjectPrecision(MathObjectPtr &obj, uint8_t precision);

  virtual IMathObject *simplify() = 0;

private:
  static Parser::Vector<ExpressionPtr, const std::string &> parserVector;
};

template <typename Derived>
class IExpressionCRTP : virtual public IMathObjectCRTP<Derived>, virtual public IExpression {};

}
