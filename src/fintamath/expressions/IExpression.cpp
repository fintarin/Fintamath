#include "fintamath/expressions/IExpression.hpp"

#include <utility>

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IExpression)

IExpression::IExpression(Children inChildren) : children(std::move(inChildren)) {
}

const std::vector<std::shared_ptr<IMathObject>> &IExpression::getChildren() const noexcept {
  return children;
}

}
