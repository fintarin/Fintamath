#pragma once

#include <concepts>
#include <memory>
#include <string>
#include <utility>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/core/Parser.hpp"

namespace fintamath {

class ILiteral : public IMathObject {
  using LiteralParser = Parser<std::unique_ptr<ILiteral>()>;

public:
  static std::unique_ptr<ILiteral> parse(const std::string &str) {
    return getParser().parse(str);
  }

  template <std::derived_from<ILiteral> T>
  static void registerType() {
    getParser().registerType<T>();
  }

  static void registerType(LiteralParser::StringConstructor constructor) {
    getParser().registerType(std::move(constructor));
  }

  static constexpr MathObjectType getTypeStatic() {
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