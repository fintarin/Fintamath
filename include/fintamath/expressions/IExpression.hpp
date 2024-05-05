#pragma once

#include <concepts>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/Parser.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class IExpression : public IMathObject {
  FINTAMATH_PARENT_CLASS_BODY(IExpression, IMathObject)

protected:
  enum class State : uint8_t {
    Unknown,
    PreSimplify,
    Simplify,
    Solve,
    Approximate,
  };

private:
  struct CallFunctionCached {
    ArgumentPtr value;
    std::optional<unsigned> precision;
    bool areArgsPrecise = true;
  };

public:
  using VariableSet = std::set<Variable, ToStringComparator<std::less<>>>;

public:
  virtual const std::shared_ptr<IFunction> &getFunction() const = 0;

  virtual const ArgumentPtrVector &getChildren() const = 0;

  const VariableSet &getVariables() const;

  std::unique_ptr<IMathObject> toMinimalObject() const override;

  virtual const std::shared_ptr<IFunction> &getOutputFunction() const;

  std::string toString() const override;

protected:
  virtual ArgumentPtr preSimplify(bool isTranformOverriden = true) const;

  virtual ArgumentPtr simplify(bool isTranformOverriden = true) const;

  virtual ArgumentPtr approximate(bool isTranformOverriden = true) const;

  virtual ArgumentPtr tranform(State newState) const;

  State getState() const;

  ArgumentPtr callFunction() const;

  static void preSimplifyChild(ArgumentPtr &child, bool isTranformOverriden = true);

  static void simplifyChild(ArgumentPtr &child, bool isTranformOverriden = true);

  static void approximateChild(ArgumentPtr &child, bool isTranformOverriden = true);

  static void callFunctionChild(ArgumentPtr &child);

  static void tranformChild(ArgumentPtr &child, State newState, bool isOverriden);

private:
  ArgumentPtr simplifyUndefined() const;

  static std::unique_ptr<INumber> convertToApproximated(const INumber &num);

private:
  mutable std::optional<VariableSet> variablesCached;

  mutable std::optional<CallFunctionCached> callFunctionCached;

  mutable State state = State::Unknown;
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
