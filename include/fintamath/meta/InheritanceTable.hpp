#pragma once

#include <map>
#include <memory>
#include <queue>

#include "fintamath/meta/TypeInfo.hpp"

namespace fintamath {

class IMathObject;

class InheritanceTable {
public:
  template <
      typename Base, typename Derived,
      typename = std::enable_if_t<std::is_base_of_v<IMathObject, Base> && std::is_base_of_v<IMathObject, Derived>>>
  static void add() {
    table.insert({typeid(Base), typeid(Derived)});
  }

  static bool isBaseOf(const std::type_info &baseType, const std::type_info &derivedType);

private:
  static bool isBaseOf(std::queue<TypeInfo> &baseTypes, const TypeInfo &derivedType);

private:
  static std::multimap<TypeInfo, TypeInfo> table;
};

}
