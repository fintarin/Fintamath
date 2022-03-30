#pragma once

#include <memory>
#include <vector>

#include "fintamath/math_objects/nodes/Node.hpp"

namespace fintamath {
  class Expression : public Node {
  public:
    struct Elem {
      std::shared_ptr<MathObject> info;
      std::shared_ptr<Elem> left;
      std::shared_ptr<Elem> right;
    };

    Expression() = default;
    explicit Expression(const std::string &strExpr);

    std::string toString() const override;

    std::string solve();

  private:
    std::shared_ptr<Elem> root;

    void makeExpression(const std::vector<std::string> &tokensVect);
  };
}