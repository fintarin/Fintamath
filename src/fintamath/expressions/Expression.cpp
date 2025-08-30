#include "fintamath/expressions/Expression.hpp"

namespace fintamath {

const Expression::ExpressionBaseDeclaration &Expression::getDeclaration() const noexcept {
  static const ExpressionBaseDeclaration declaration = [] {
    ExpressionBaseDeclaration outDeclaration;
    outDeclaration.returnClass = nullptr;
    outDeclaration.childClasses = {MathObject::getClassStatic()};
    outDeclaration.isVariadic = false;
    return outDeclaration;
  }();
  return declaration;
}

}
