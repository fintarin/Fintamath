#include "fintamath/expressions/IExpression.hpp"

#include <utility>

namespace fintamath {

IExpression::IExpression(Children inChildren) : children(std::move(inChildren)) {
}

const std::vector<std::shared_ptr<IMathObject>> &IExpression::getChildren() const noexcept {
  return children;
}

}
