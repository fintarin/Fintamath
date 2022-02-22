#pragma once

#include "fintamath/math_objects/nodes/expressions/Expression.hpp"
#include "fintamath/math_objects/relations/Relation.hpp"
#include "fintamath/math_objects/nodes/expressions/Expression.hpp"

namespace fintamath {
  class RelationParser final {
  public:
    RelationParser() = delete;

    static std::unique_ptr<Expression> parse(const std::string_view &str);
  };
}
