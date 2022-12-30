#pragma once

#include <memory>

#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

class IConstant;
using ConstantPtr = std::unique_ptr<IConstant>;

class IConstant : virtual public ILiteral {
public:
  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IConstant, T>>>
  static void addParser() {
    helpers::addParser<T>(parserMap);
  }

  static ConstantPtr parse(const std::string &parsedStr) {
    return helpers::parse<ConstantPtr>(parserMap, parsedStr, [](const ConstantPtr &) { return true; });
  }

  Expression operator()() const {
    return getValue();
  }

protected:
  virtual Expression getValue() const = 0;

private:
  static helpers::ParserMap<ConstantPtr> parserMap;
};

template <typename Derived>
class IConstantCRTP : virtual public IConstant, virtual public ILiteralCRTP<Derived> {};

}
