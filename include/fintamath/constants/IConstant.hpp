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

  virtual std::unique_ptr<IMathObject> approximate() const noexcept;

  static std::shared_ptr<const IConstant> parseConstant(const std::string &str);

protected:
  void registerDefaultObject() const override;

private:
  static NameToConstantMap &getNameToConstantMap();
};

}
