#include "fintamath/constants/IConstant.hpp"

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/Tokenizer.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IConstant)

std::shared_ptr<const IMathObject> IConstant::getValue() const noexcept {
  return nullptr;
}

std::shared_ptr<const IMathObject> IConstant::approximateValue() const noexcept {
  return nullptr;
}

std::shared_ptr<const IMathObject> IConstant::unwrapp() const noexcept {
  return getValue();
}

std::shared_ptr<const IConstant> IConstant::parseConstant(const std::string &str) {
  const NameToConstantMap &nameToConstMap = getNameToConstantMap();
  const auto iter = nameToConstMap.find(str);
  return iter != nameToConstMap.end() ? iter->second : nullptr;
}

void IConstant::registerDefaultObject() const {
  std::string name = toString();
  detail::Tokenizer::registerToken(name);

  auto object = cast<IConstant>(std::shared_ptr(clone()));
  [[maybe_unused]] const auto empaceResult = getNameToConstantMap().emplace(
    std::move(name),
    std::move(object)
  );
  assert(empaceResult.second);
}

IConstant::NameToConstantMap &fintamath::IConstant::getNameToConstantMap() {
  static NameToConstantMap nameToConstantMap;
  return nameToConstantMap;
}

}
