#pragma once

#include <memory>
#include <unordered_map>

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

class IConstant : public IMathObject {
  FINTAMATH_INTERFACE_BODY(IConstant, IMathObject)

private:
  using NameToConstantMap = std::unordered_map<std::string, std::shared_ptr<const IConstant>>;

public:
  virtual constexpr MathObjectClass getValueClass() const noexcept = 0;

  virtual std::shared_ptr<const IMathObject> getValue() const noexcept;

  virtual std::shared_ptr<const IMathObject> approximateValue() const noexcept;

  std::shared_ptr<const IMathObject> unwrapp() const noexcept final;

  static std::shared_ptr<const IConstant> parseConstant(const std::string &str);

protected:
  void registerDefaultObject() const override;

private:
  static NameToConstantMap &getNameToConstantMap();
};

}
