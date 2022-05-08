#pragma once

#include "fintamath/literals/Literal.hpp"

namespace fintamath {
  class Variable : public LiteralImpl<Variable> {
  public:
    explicit Variable(const std::string &str);

    std::string toString() const override;

  private:
    void parse(const std::string &str);

    std::string name;
  };
}