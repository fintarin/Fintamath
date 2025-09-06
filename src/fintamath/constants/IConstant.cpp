#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/MathObjectUtils.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IConstant)

std::string IConstant::toString() const noexcept {
  return std::string(getClassStatic()->getName());
}

std::shared_ptr<IConstant> IConstant::parseConstant(const std::string &str) {
  NameToConstantMap &nameToConstantMap = getNameToConstantMap();
  auto parsedConstantIter = nameToConstantMap.find(str);
  return parsedConstantIter != nameToConstantMap.end() ? parsedConstantIter->second : nullptr;
}

void IConstant::registerDefaultObject() const {
  std::string name = toString();
  auto object = cast<IConstant>(std::shared_ptr(clone()));
  const auto empaceResult = getNameToConstantMap().emplace(std::move(name), std::move(object));
  assert(empaceResult.second);
}

IConstant::NameToConstantMap &fintamath::IConstant::getNameToConstantMap() {
  static NameToConstantMap nameToConstantMap;
  return nameToConstantMap;
}

}
