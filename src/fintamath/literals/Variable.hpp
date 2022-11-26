#pragma once

#include "fintamath/literals/ILiteral.hpp"

namespace fintamath {
  class Variable : public ILiteralCRTP<Variable> {
  public:
    explicit Variable(const std::string &str);

    std::string toString() const override;

    std::string getClassName() const override;

  private:
    std::string name;
  };
}