#pragma once

#include "fintamath/literals/ILiteral.hpp"

namespace fintamath {

class Boolean : public ILiteralCRTP<Boolean> {
public:
  explicit Boolean(const string &str);

  Boolean(bool val);

  string toString() const override;

  operator bool() const;

private:
  void parse(const string &str);

  string name;
};

}
