#pragma once

#include <memory>

#include "fintamath/literals/ILiteral.hpp"

namespace fintamath {

class IConstant;
using ConstantPtr = std::unique_ptr<IConstant>;

class IConstant : virtual public ILiteral {
public:
  virtual const std::type_info &getReturnType() const = 0;

  MathObjectPtr operator()() const {
    return call();
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IConstant, T>>>
  static void registerType() {
    Parser::registerType<T>(parserMap);
  }

  static ConstantPtr parse(const std::string &parsedStr) {
    return Parser::parse<ConstantPtr>(parserMap, parsedStr);
  }

protected:
  virtual MathObjectPtr call() const = 0;

private:
  static Parser::Map<ConstantPtr> parserMap;
};

template <typename Return, typename Derived>
class IConstantCRTP : virtual public ILiteralCRTP<Derived>, virtual public IConstant {
  const std::type_info &getReturnType() const final {
    return typeid(Return);
  }
};

}
