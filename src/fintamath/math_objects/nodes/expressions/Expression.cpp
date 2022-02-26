#include "fintamath/math_objects/nodes/expressions/Expression.hpp"

#include <stdexcept>
#include <utility>

namespace fintamath {
  Expression::Expression(const std::string_view & /*str*/) {
    throw std::invalid_argument("Expression invalid input");
  }

  std::string Expression::toString() const {
    return "expression";
  }
  Expression::Expression(Set set, std::shared_ptr<Relation> relation)
      : set(std::move(set)), relation(std::move(relation)) {
  }

}