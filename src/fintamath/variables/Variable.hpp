#pragma once

#include <memory>
#include <vector>

#include "fintamath/expressions/Expression.hpp"

namespace fintamath {
  class Variable : public Object {
  public:
    explicit Variable(const std::string &strVariable);
    std::string toString() const override;

    Expression operator+(const Object &rhs) const;
    Expression operator-(const Object &rhs) const;
    Expression operator*(const Object &rhs) const;
    Expression operator/(const Object &rhs) const;
    bool operator==(const Object &rhs) const;
    bool operator!=(const Object &rhs) const;

    std::unique_ptr<Object> clone() const override;

    bool equals(const Object &rhs) const override;

  private:
    std::string name;
  };

  namespace types {
    bool isVariable(const std::string &str);
  }
}