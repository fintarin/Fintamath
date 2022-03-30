#pragma once

#include <memory>
#include <vector>

#include "fintamath/nodes/Node.hpp"

namespace fintamath {
  class Expression : public Node {
  public:
    struct Elem {
      std::shared_ptr<Object> info;
      std::shared_ptr<Elem> left;
      std::shared_ptr<Elem> right;

      std::shared_ptr<Elem> clone();
    };

    Expression() = default;
    explicit Expression(const std::string &strExpr);

    std::string toString() const override;

    std::string solve();

    std::shared_ptr<Object> clone() const override;

  private:
    std::shared_ptr<Elem> root;

    void makeExpression(const std::vector<std::string> &tokensVect);
  };
}