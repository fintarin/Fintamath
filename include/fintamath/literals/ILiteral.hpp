#pragma once

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

class ILiteral : public IMathObject {
  using LiteralParser = Parser<std::unique_ptr<ILiteral>>;

public:
  template <std::derived_from<ILiteral> T>
  static void registerConstructor() {
    getParser().registerConstructor<T>();
  }

  static void registerConstructor(LiteralParser::Constructor constructor) {
    getParser().registerConstructor(std::move(constructor));
  }

  static std::unique_ptr<ILiteral> parse(const std::string &str) {
    return getParser().parse(str);
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::ILiteral;
  }

private:
  static LiteralParser &getParser();
};

template <typename Derived>
class ILiteralCRTP : public ILiteral {
#define I_LITERAL_CRTP ILiteralCRTP<Derived>
#include "fintamath/literals/ILiteralCRTP.hpp"
#undef I_LITERAL_CRTP
};

}