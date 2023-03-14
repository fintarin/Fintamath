#pragma once

#include <memory>

#include "fintamath/literals/ILiteral.hpp"

namespace fintamath {

class IConstant : virtual public ILiteral {
public:
  virtual const std::type_info &getReturnType() const = 0;

  unique_ptr<IMathObject> operator()() const {
    return call();
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IConstant, T>>>
  static void registerType() {
    Parser::registerType<T>(parserMap);
  }

  static unique_ptr<IConstant> parse(const string &parsedStr) {
    return Parser::parse<unique_ptr<IConstant>>(parserMap, parsedStr);
  }

protected:
  virtual unique_ptr<IMathObject> call() const = 0;

private:
  static Parser::Map<unique_ptr<IConstant>> parserMap;
};

template <typename Return, typename Derived>
class IConstantCRTP : virtual public ILiteralCRTP<Derived>, virtual public IConstant {
  const std::type_info &getReturnType() const final {
    return typeid(Return);
  }
};

}
