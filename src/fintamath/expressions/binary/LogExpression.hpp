#pragma once

#include <memory>
#include <string>

#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class LogExpression final : public IBinaryExpressionCRTP<LogExpression> {
public:
  explicit LogExpression(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild);

  std::string toString() const override;

  std::shared_ptr<IFunction> getOutputFunction() const override;

  static MathObjectType getTypeStatic() {
    return MathObjectType::LogExpression;
  }

protected:
  ArgumentPtr approximateSimplify() const override;

  ArgumentPtr setPrecision(unsigned precision, const Integer &maxInt) const override;

  SimplifyFunctionVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr constSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr equalSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr powSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);
};

}