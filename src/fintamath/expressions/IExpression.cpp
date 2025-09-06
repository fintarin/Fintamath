#include "fintamath/expressions/IExpression.hpp"

#include <utility>

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IExpression)

IExpression::IExpression(Children inChildren) : children(std::move(inChildren)) {
}

const IExpression::Children &IExpression::getChildren() const noexcept {
  return children;
}

}
