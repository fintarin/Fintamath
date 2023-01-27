#pragma once

#include <memory>
#include <vector>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/parser/Parser.hpp"
#include "fintamath/parser/Tokenizer.hpp"

namespace fintamath {

class IFunction;

using ArgumentsVector = std::vector<std::reference_wrapper<const class IMathObject>>;

class IExpression;
using ExpressionPtr = std::unique_ptr<IExpression>;

class IExpression : virtual public IMathObject {
public:
  virtual uint16_t getBaseOperatorPriority() const = 0;

  virtual void setPrecision(uint8_t precision) = 0;

  virtual MathObjectPtr simplify(bool isPrecise) const = 0;

  virtual void compress() {
  }

  MathObjectPtr simplify() const override {
    return simplify(false);
  }

  virtual std::vector<MathObjectPtr> getVariables() const {
    return {};
  }

protected:
  static std::string tryPutInBracketsIfNeg(const MathObjectPtr &obj); // TODO: move to NegExpression

  // TODO: move to Expression
  void validateFunctionArgs(const IFunction &func, const ArgumentsVector &args) const;
};

template <typename Derived>
class IExpressionCRTP : virtual public IExpression, virtual public IMathObjectCRTP<Derived> {};

}
