#include "fintamath/meta/InheritanceTable.hpp"

namespace fintamath {

bool InheritanceTable::isBaseOf(const std::type_info &baseType, const std::type_info &derivedType) {
  if (baseType == derivedType) {
    return true;
  }

  std::queue<TypeInfo> derivedTypes({TypeInfo(baseType)});
  bool res = isBaseOf(derivedTypes, TypeInfo(derivedType));

  return res;
}

bool InheritanceTable::isBaseOf(std::queue<TypeInfo> &baseTypes, const TypeInfo &derivedType) {
  if (baseTypes.empty()) {
    return false;
  }

  auto it = table.lower_bound(baseTypes.front());
  auto end = table.upper_bound(baseTypes.front());

  while (it != end) {
    if (it->second == derivedType) {
      return true;
    }

    baseTypes.push(it->second);

    it++;
  }

  baseTypes.pop();

  return isBaseOf(baseTypes, derivedType);
}

}
