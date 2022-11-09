#pragma once

#include <memory>

#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {
  class IConstant;
  using ConstantPtr = std::unique_ptr<IConstant>;

  class IConstant : virtual public ILiteral {
  public:
    virtual Rational getValue(int64_t precision) const = 0;

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<IConstant, T>>>
    static void addParser() {
      helpers::addParser<T>(parserMap);
    }

    static ConstantPtr parse(const std::string &parsedStr) {
      return helpers::parse<ConstantPtr>(parserMap, parsedStr, [](const ConstantPtr &) { return true; });
    }

  private:
    static helpers::ParserMap<ConstantPtr> parserMap;
  };

  template <typename Derived>
  class IConstantCRTP : virtual public IConstant, virtual public ILiteralCRTP<Derived> {};
}
