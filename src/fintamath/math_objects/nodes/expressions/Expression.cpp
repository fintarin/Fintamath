#include "fintamath/math_objects/nodes/expressions/Expression.hpp"

#include <stdexcept>
#include <utility>

namespace fintamath {
  Expression::Expression(const std::string_view &str) {
    throw std::invalid_argument("Expression invalid argument");
  }

  std::string Expression::toString() const {
    return "expression";
  }
  Expression::Expression(const Set &set, const std::shared_ptr<Relation> &relation)
      : set(set), relation(relation){
  }

}