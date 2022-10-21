#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/helpers/Parser.hpp"

namespace fintamath {
  class ILiteral;
  using LiteralPtr = std::unique_ptr<ILiteral>;

  class ILiteral : virtual public IMathObject {
  public:
    ~ILiteral() override = default;

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<ILiteral, T>>>
    static bool addParser() {
      return helpers::addParser<T>(parserMap);
    }

    static bool addParser(const helpers::ParserStringFunction<LiteralPtr> &parserFunc) {
      return helpers::addParser(parserMap, parserFunc);
    }

    static LiteralPtr parse(const std::string &str) {
      return helpers::parse(parserMap, str);
    }

  private:
    static helpers::ParserVector<LiteralPtr> parserMap;
  };

  template <typename Derived>
  class ILiteralCRTP : virtual public ILiteral, virtual public IMathObjectCRTP<Derived> {
  public:
    ~ILiteralCRTP() override = default;

  protected:
    bool equals(const Derived &rhs) const final {
      return toString() == rhs.toString();
    }
  };
}