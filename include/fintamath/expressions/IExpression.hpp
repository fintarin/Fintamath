#pragma once

#include <concepts>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/Parser.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class IExpression : public IMathObject {
  FINTAMATH_PARENT_CLASS_BODY(IExpression)

public:
  virtual const std::shared_ptr<IFunction> &getFunction() const = 0;

  virtual const ArgumentPtrVector &getChildren() const = 0;

  virtual void setChildren(const ArgumentPtrVector &childVect) = 0;

  std::vector<Variable> getVariables() const;

  virtual void setVariables(const std::vector<std::pair<Variable, ArgumentPtr>> &varsToVals);

  std::unique_ptr<IMathObject> toMinimalObject() const final;

  virtual const std::shared_ptr<IFunction> &getOutputFunction() const;

protected:
  virtual ArgumentPtr simplify() const;

  virtual ArgumentPtr preSimplify() const;

  virtual ArgumentPtr postSimplify() const;

  virtual ArgumentPtr approximate() const;

  virtual ArgumentPtr setPrecision(unsigned precision, const Integer &maxInt) const;

  static void simplifyChild(ArgumentPtr &child);

  static void preSimplifyChild(ArgumentPtr &child);

  static void postSimplifyChild(ArgumentPtr &child);

  static void approximateChild(ArgumentPtr &child);

  static void setPrecisionChild(ArgumentPtr &child, unsigned precision, const Integer &maxInt);

  static ArgumentPtr callFunction(const IFunction &func, const ArgumentPtrVector &argPtrs);

private:
  static std::unique_ptr<INumber> convertToApproximated(const INumber &num);

  static std::unique_ptr<INumber> convertToApproximated(const INumber &num, unsigned precision, const Integer &maxInt);

  static ArgumentPtrVector convertToApproximatedNumbers(const ArgumentPtrVector &args);
};

template <typename Derived>
class IExpressionBaseCRTP : public IExpression {
#define I_EXPRESSION_BASE_CRTP IExpressionBaseCRTP<Derived>
#include "fintamath/expressions/IExpressionBaseCRTP.hpp"
#undef I_EXPRESSION_BASE_CRTP
};

template <typename Derived>
class IExpressionCRTP : public IExpressionBaseCRTP<Derived> {
#define I_EXPRESSION_CRTP IExpressionCRTP<Derived>
#include "fintamath/expressions/IExpressionCRTP.hpp"
#undef I_EXPRESSION_CRTP
};

}
