#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/helpers/Parser.hpp"

namespace fintamath {
  class ILiteral;
  using LiteralPtr = std::unique_ptr<ILiteral>;

  class ILiteral : virtual public IMathObject {
  public:
    ~ILiteral() override = default;

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<ILiteral, T>>>
    static void addParser() {
      helpers::addParser<T>(parserVector);
    }

    static LiteralPtr parse(const std::string &str) {
      return helpers::parse(parserVector, str);
    }

    operator Expression() {
      return {*this->clone()};
    }

  private:
    static helpers::ParserVector<LiteralPtr, std::string> parserVector;
  };

  template <typename Derived>
  class ILiteralCRTP : virtual public ILiteral, virtual public IMathObjectCRTP<Derived> {
  protected:
    bool equals(const Derived &rhs) const final {
      return toString() == rhs.toString();
    }
  };
}