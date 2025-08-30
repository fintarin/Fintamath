#include "fintamath/expressions/ExpressionBase.hpp"

#include <utility>

namespace fintamath {

ExpressionBase::ExpressionBase(Children inChildren) : children(std::move(inChildren)) {
}

const std::vector<std::shared_ptr<MathObject>> &ExpressionBase::getChildren() const noexcept {
  return children;
}

}
