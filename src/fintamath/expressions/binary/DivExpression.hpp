#pragma once

#include "fintamath/expressions/IBinaryExpression.hpp"
#include "fintamath/expressions/IInvertableExpression.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class DivExpression : public IBinaryExpressionCRTP<DivExpression>, public IInvertableExpression {
public:
  explicit DivExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild);

  ArgumentPtr invert() const override;

  std::string toString() const override;

protected:
  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

private:
  ArgumentPtr globalSimplify() const;

  ArgumentPtr divSimplify() const;

  ArgumentPtr mulSimplify() const;

  ArgumentPtr sumSimplify() const;
};

}