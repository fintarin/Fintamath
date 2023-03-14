#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/parser/Parser.hpp"
#include "fintamath/parser/Tokenizer.hpp"

namespace fintamath {

class IExpression : virtual public IMathObject {
public:
  virtual shared_ptr<IFunction> getFunction() const = 0;

  virtual ArgumentsPtrVector getChildren() const = 0;

  // TODO: make this protected
  // virtual void setPrecision(uint8_t precision) = 0;

  virtual ArgumentsPtrVector getVariables() const;

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IExpression, T>>>
  static void registerType() {
    Parser::registerType<T>(parserVector);
  }

  static unique_ptr<IExpression> parse(const string &str) {
    return Parser::parse(parserVector, str);
  }

protected:
  static void compressChild(shared_ptr<IMathObject> &child);

  static void simplifyChild(shared_ptr<IMathObject> &child);

  // static void setMathObjectPrecision(shared_ptr<IMathObject> &obj, uint8_t precision);

  virtual shared_ptr<IMathObject> simplify() = 0;

private:
  static Parser::Vector<unique_ptr<IExpression>, const string &> parserVector;
};

template <typename Derived>
class IExpressionCRTP : virtual public IMathObjectCRTP<Derived>, virtual public IExpression {};

}
