#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class ILiteral : virtual public IMathObject {
public:
  ~ILiteral() override = default;

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<ILiteral, T>>>
  static void registerType() {
    Parser::registerType<T>(parserVector);
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<ILiteral, T>>>
  static void registerType(Parser::Function<unique_ptr<ILiteral>, const string &> &&parserFunc) {
    Parser::registerType<T>(parserVector, parserFunc);
  }

  static unique_ptr<ILiteral> parse(const string &str) {
    return Parser::parse(parserVector, str);
  }

private:
  static Parser::Vector<unique_ptr<ILiteral>, const string &> parserVector;
};

template <typename Derived>
class ILiteralCRTP : virtual public IMathObjectCRTP<Derived>, virtual public ILiteral {};

}