#include "fintamath/expressions/Expression.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Expression)

const Expression::ExpressionDeclaration Expression::expressionDeclaration = {
  .domainAndRangeVariants = {{
    .returnClass = nullptr,
    .childClasses = {IMathObject::getClassStatic()},
  }},
  .isVariadic = false,
};

}
