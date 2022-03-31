#pragma once

#include <memory>
#include <vector>

#include "fintamath/nodes/expressions/Expression.hpp"

namespace fintamath {
  class Variable : public Node {
  public:
    explicit Variable(const std::string &strVariable);
    std::string toString() const override;

    Expression operator+(const Node &rhs) const;
    Expression operator-(const Node &rhs) const;
    Expression operator*(const Node &rhs) const;
    Expression operator/(const Node &rhs) const;
    bool operator==(const Node &rhs) const;
    bool operator!=(const Node &rhs) const;

    std::unique_ptr<Object> clone() const override;

    bool equals(const Object &rhs) const override;

  private:
    std::string name;
  };

  namespace types {
    bool isVariable(const std::string &str);
  }
}