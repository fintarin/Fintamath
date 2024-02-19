#pragma once

#include <memory>

#include "fintamath/core/MathObjectType.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

class DerivativeExpression final : public IBinaryExpressionCRTP<DerivativeExpression> {
public:
  explicit DerivativeExpression(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild);

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::DerivativeExpression, "DerivativeExpression"};
  }

protected:
  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr derivativeSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr exprSimplify(const std::shared_ptr<const IExpression> &expr, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr addSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr mulSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr divSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr powSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr logSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr sinSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr cosSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr tanSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr cotSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr secSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr cscSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr asinSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr acosSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr atanSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr acotSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr asecSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr acscSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr sinhSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr coshSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr tanhSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr cothSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr sechSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr cschSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr asinhSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr acoshSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr atanhSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr asechSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);

  static ArgumentPtr acschSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var);
};

}
