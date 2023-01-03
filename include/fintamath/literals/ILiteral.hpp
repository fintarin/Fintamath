#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class ILiteral;
using LiteralPtr = std::unique_ptr<ILiteral>;

class ILiteral : virtual public IMathObject {
public:
  ~ILiteral() override = default;

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<ILiteral, T>>>
  static void addParser() {
    Parser::addParser<T>(parserVector);
  }

  static void addParser(const Parser::Function<LiteralPtr, std::string> &parserFunc) {
    Parser::addParser(parserVector, parserFunc);
  }

  static LiteralPtr parse(const std::string &str) {
    return Parser::parse(parserVector, str);
  }

private:
  static Parser::ParserVector<LiteralPtr, std::string> parserVector;
};

template <typename Derived>
class ILiteralCRTP : virtual public ILiteral, virtual public IMathObjectCRTP<Derived> {};

}