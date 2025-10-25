#pragma once

#include <unordered_map>

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

class IConstant : public IMathObject {
  FINTAMATH_INTERFACE_BODY(IConstant, IMathObject)

public:
  virtual constexpr MathObjectClass getValueClass() const noexcept = 0;

  virtual SharedPtr<IMathObject> getValue() const noexcept;

  virtual SharedPtr<IMathObject> approximateValue() const noexcept;

  SharedPtr<IMathObject> unwrappSelf() const noexcept final;

  static SharedPtr<IConstant> parseConstant(const std::string &str);

protected:
  bool equals(const SharedRef<IMathObject> &self, const SharedRef<IMathObject> &rhs) const noexcept override;

  void registerDefaultObject() const override;

private:
  using NameToConstantMap = std::unordered_map<std::string, SharedRef<IConstant>>;

private:
  static NameToConstantMap &getNameToConstantMap();
};

}
