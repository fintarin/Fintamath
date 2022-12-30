#pragma once

#include "fintamath/literals/ILiteral.hpp"

namespace fintamath {
  class Boolean : public ILiteralCRTP<Boolean> {
  public:
    explicit Boolean(const std::string &str);

    Boolean(bool val);

    std::string toString() const override;

    operator bool() const;

  private:
    void parse(const std::string &str);

    std::string name;
  };
}
