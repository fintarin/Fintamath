#pragma once

#include <concepts>
#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/core/Parser.hpp"
#include "fintamath/literals/ILiteral.hpp"

namespace fintamath {

class IConstant : public ILiteral {
  using ConstantParser = Parser<std::unique_ptr<IConstant>()>;

public:
  virtual MathObjectType getReturnType() const = 0;

  std::unique_ptr<IMathObject> operator()() const {
    return call();
  }

  static std::unique_ptr<IConstant> parse(const std::string &parsedStr) {
    return getParser().parse(parsedStr);
  }

  template <std::derived_from<IConstant> T>
  static void registerType() {
    getParser().registerType<T>();
  }

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::IConstant;
  }

protected:
  virtual std::unique_ptr<IMathObject> call() const = 0;

private:
  static ConstantParser &getParser();
};

template <typename Return, typename Derived>
class IConstantCRTP : public IConstant {
#define I_CONSTANT_CRTP IConstantCRTP<Return, Derived>
#include "fintamath/literals/constants/IConstantCRTP.hpp"
#undef I_CONSTANT_CRTP
};

}
