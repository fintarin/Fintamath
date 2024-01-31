#pragma once

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

class ILiteral : public IMathObject {
public:
  template <std::derived_from<ILiteral> T>
  static void registerType() {
    Parser::registerType<T>(getParser());
  }

  template <std::derived_from<ILiteral> T>
  static void registerType(Parser::Function<std::unique_ptr<ILiteral>, const std::string &> &&parserFunc) {
    Parser::registerType<T>(getParser(), std::move(parserFunc));
  }

  static std::unique_ptr<ILiteral> parse(const std::string &str) {
    return Parser::parse(getParser(), str);
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::ILiteral;
  }

private:
  static Parser::Vector<std::unique_ptr<ILiteral>, const std::string &> &getParser();
};

template <typename Derived>
class ILiteralCRTP : public ILiteral {
#define I_LITERAL_CRTP ILiteralCRTP<Derived>
#include "fintamath/literals/ILiteralCRTP.hpp"
#undef I_LITERAL_CRTP
};

}