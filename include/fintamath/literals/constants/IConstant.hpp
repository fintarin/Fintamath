#pragma once

#include <memory>

#include "fintamath/literals/ILiteral.hpp"

namespace fintamath {

class IConstant : public ILiteral {
public:
  virtual size_t getReturnType() const = 0;

  std::unique_ptr<IMathObject> operator()() const {
    return call();
  }

  template <std::derived_from<IConstant> T>
  static void registerType() {
    Parser::registerType<T>(getParser());
  }

  static std::unique_ptr<IConstant> parse(const std::string &parsedStr) {
    return Parser::parse<std::unique_ptr<IConstant>>(getParser(), parsedStr);
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::IConstant;
  }

protected:
  virtual std::unique_ptr<IMathObject> call() const = 0;

private:
  static Parser::Map<std::unique_ptr<IConstant>> &getParser();
};

template <typename Return, typename Derived>
class IConstantCRTP : public IConstant {
#define I_CONSTANT_CRTP IConstantCRTP<Return, Derived>
#include "fintamath/literals/constants/IConstantCRTP.hpp"
#undef I_CONSTANT_CRTP
};

}
