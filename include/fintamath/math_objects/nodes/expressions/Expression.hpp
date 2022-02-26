#pragma once

#include "fintamath/math_objects/nodes/collections/Set.hpp"
#include "fintamath/math_objects/relations/Relation.hpp"

namespace fintamath {
  class Expression : public Node {
  public:
    Expression() = default;
    explicit Expression(const std::string_view &str);
    explicit Expression(Set set, std::shared_ptr<Relation> relation);
    std::string toString() const override;

  private:
    std::shared_ptr<Relation> relation;
    Set set;
  };
}
