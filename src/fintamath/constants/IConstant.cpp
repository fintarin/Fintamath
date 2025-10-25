#include "fintamath/constants/IConstant.hpp"

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/Tokenizer.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IConstant)

SharedPtr<IMathObject> IConstant::getValue() const noexcept {
  return nullptr;
}

SharedPtr<IMathObject> IConstant::approximateValue() const noexcept {
  return nullptr;
}

SharedPtr<IMathObject> IConstant::unwrappSelf() const noexcept {
  return getValue();
}

SharedPtr<IConstant> IConstant::parseConstant(const std::string &str) {
  const NameToConstantMap &nameToConstMap = getNameToConstantMap();
  const auto iter = nameToConstMap.find(str);
  return iter != nameToConstMap.end() ? iter->second : SharedPtr<IConstant>{};
}

bool IConstant::equals(const SharedRef<IMathObject> & /*self*/, const SharedRef<IMathObject> &rhs) const noexcept {
  return getClass() == rhs->getClass();
}

void IConstant::registerDefaultObject() const {
  std::string name = toString();
  detail::Tokenizer::registerToken(name);

  auto self = cast<IConstant>(SharedPtr<IMathObject>(cloneSelf()));

  [[maybe_unused]] const auto emplaceRes = getNameToConstantMap().emplace(
    std::move(name),
    std::move(self).toRef()
  );
  assert(emplaceRes.second);
}

IConstant::NameToConstantMap &IConstant::getNameToConstantMap() {
  static NameToConstantMap nameToConstantMap;
  return nameToConstantMap;
}

}
