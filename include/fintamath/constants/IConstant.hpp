#pragma once

#include <memory>
#include <unordered_map>

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

class IConstant : public IMathObject {
  FINTAMATH_INTERFACE_BODY(IConstant, IMathObject)

private:
  using NameToConstantMap = std::unordered_map<std::string, Shared<IConstant>>;

public:
  virtual constexpr MathObjectClass getValueClass() const noexcept = 0;

  virtual Shared<IMathObject> getValue() const noexcept;

  virtual Shared<IMathObject> approximateValue() const noexcept;

  Shared<IMathObject> unwrapp() const noexcept final;

  static Shared<IConstant> parseConstant(const std::string &str);

protected:
  void registerDefaultObject() const override;

private:
  static NameToConstantMap &getNameToConstantMap();
};

}
