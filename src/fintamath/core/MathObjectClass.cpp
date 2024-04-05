#include "fintamath/core/MathObjectClass.hpp"

namespace fintamath {

std::strong_ordering MathObjectClass::operator<=>(const MathObjectClass rhs) const noexcept {
  const Id lhsId = getId();
  const Id rhsId = rhs.getId();

  return lhsId != 0 && rhsId != 0
             ? lhsId <=> rhsId
             : name <=> rhs.name;
}

std::optional<MathObjectClass> MathObjectClass::getParent() const noexcept {
  const auto iter = getChildToParentMap().find(name);
  return iter != getChildToParentMap().end() ? iter->second : std::optional<MathObjectClass>{};
}

const MathObjectClass::Children &MathObjectClass::getChildren(const bool recursive) const noexcept {
  if (recursive) {
    return getParentToRecursiveChildrenMap()[name];
  }

  return getParentToChildrenMap()[name];
}

MathObjectClass::Id MathObjectClass::getId() const noexcept {
  const auto classToId = getClassToIdMap().find(*this);
  return classToId != getClassToIdMap().end() ? classToId->second : 0;
}

MathObjectClass::ClassToIdMap &MathObjectClass::getClassToIdMap() noexcept {
  static ClassToIdMap map;
  return map;
}

MathObjectClass::ChildToParentMap &MathObjectClass::getChildToParentMap() noexcept {
  static ChildToParentMap map;
  return map;
}

MathObjectClass::ParentToChildrenMap &MathObjectClass::getParentToChildrenMap() noexcept {
  static ParentToChildrenMap map;
  return map;
}

MathObjectClass::ParentToChildrenMap &MathObjectClass::getParentToRecursiveChildrenMap() noexcept {
  static ParentToChildrenMap map;
  return map;
}

}
