#pragma once

#include "fintamath/math_objects/nodes/collections/Set.hpp"
#include "fintamath/math_objects/relations/Relation.hpp"
#include "fintamath/math_objects/relations/operators/Operator.hpp"

namespace fintamath {
  class Expression : public Node {
  public:
    Expression() = default;
    explicit Expression(const std::string_view &str);
    explicit Expression(Set set, std::shared_ptr<Relation> relation);
    Expression(const Expression& expr);
    Expression(Expression&& expr) noexcept;

    Expression& operator=(Expression&& expr) noexcept;
    Expression& operator=(const Expression& expr);

    std::string toString() const override;
    std::shared_ptr<Relation> getRelation() const;
    void setRelation(const std::shared_ptr<Relation> &rel);
    Set getSet() const;
    void setSet(const Set &operSet);

    std::unique_ptr<MathObject> clone() const override;
    std::shared_ptr<Node> calculate() const;
  private:
    std::shared_ptr<Relation> relation;
    Set set;
    std::shared_ptr<Operator> getOperator() const;
  };
}
