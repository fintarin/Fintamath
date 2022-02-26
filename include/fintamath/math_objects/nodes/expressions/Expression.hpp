#pragma once

#include "fintamath/math_objects/nodes/collections/Set.hpp"
#include "fintamath/math_objects/relations/Relation.hpp"
#include "fintamath/math_objects/relations/operators/Operator.hpp"

namespace fintamath {
  class Expression : public Node {
  public:
    Expression() = default;
    explicit Expression(const std::string_view &str);
    explicit Expression(const Set &set, const std::shared_ptr<Relation> &relation);
    std::string toString() const override;
    std::shared_ptr<Relation> getRelation();
    void setRelation(const std::shared_ptr<Relation>&rel);
    Set getSet();
    void setSet(const Set& operSet);
  private:
    std::shared_ptr<Relation> relation;
    Set set;
    std::shared_ptr<Operator> getOperator();
  };
}
