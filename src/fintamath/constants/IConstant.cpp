#include "fintamath/constants/IConstant.hpp"

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/Tokenizer.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IConstant)

std::shared_ptr<const IConstant> IConstant::parseConstant(const std::string &str) {
  const NameToConstantMap &nameToConstantMap = getNameToConstantMap();
  const auto parsedConstantIter = nameToConstantMap.find(str);
  return parsedConstantIter != nameToConstantMap.end() ? parsedConstantIter->second : nullptr;
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
