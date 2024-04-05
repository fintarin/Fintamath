#pragma once

#include <compare>
#include <cstddef>
#include <optional>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include "fintamath/config/Config.hpp"

namespace fintamath {

class MathObjectClass;

}

template <>
struct std::hash<fintamath::MathObjectClass> {
  size_t operator()(const fintamath::MathObjectClass &rhs) const noexcept;
};

namespace fintamath {

class MathObjectClass final {
public:
  using Name = std::string_view;

  using Id = size_t;

  using Children = std::unordered_set<MathObjectClass>;

private:
  using ClassToIdMap = std::unordered_map<MathObjectClass, Id>;

  using ChildToParentMap = std::unordered_map<MathObjectClass, MathObjectClass>;

  using ParentToChildrenMap = std::unordered_map<MathObjectClass, Children>;

public:
  constexpr MathObjectClass(const Name inName) noexcept : name(inName) {
  }

  constexpr Name getName() const noexcept {
    return name;
  }

  constexpr bool operator==(const MathObjectClass rhs) const noexcept {
    return name == rhs.name;
  }

  std::strong_ordering operator<=>(MathObjectClass rhs) const noexcept;

  std::optional<MathObjectClass> getParent() const noexcept;

  const Children &getChildren(bool recursive = false) const noexcept;

  template <typename Parent, std::derived_from<Parent> Child>
  static void bindTypes() noexcept;

private:
  Id getId() const noexcept;

  static ClassToIdMap &getClassToIdMap() noexcept;

  static ChildToParentMap &getChildToParentMap() noexcept;

  static ParentToChildrenMap &getParentToChildrenMap() noexcept;

  static ParentToChildrenMap &getParentToRecursiveChildrenMap() noexcept;

private:
  Name name;

  inline static Id maxId = 0;

  [[maybe_unused]] inline static const detail::Config config;
};

template <typename Parent, std::derived_from<Parent> Child>
void MathObjectClass::bindTypes() noexcept {
  MathObjectClass parent = Parent::getClassStatic();
  MathObjectClass child = Child::getClassStatic();

  getClassToIdMap()[parent] = ++maxId;
  getClassToIdMap()[child] = ++maxId;

  getChildToParentMap().insert_or_assign(child, parent);
  getParentToChildrenMap()[parent].emplace(child);

  for (std::optional superParent = child.getParent(); superParent; superParent = superParent->getParent()) {
    Children &superParentChildren = getParentToRecursiveChildrenMap()[*superParent];
    superParentChildren.emplace(child);
    superParentChildren.insert(child.getChildren().begin(), child.getChildren().end());
  }
}

}

inline size_t std::hash<fintamath::MathObjectClass>::operator()(const fintamath::MathObjectClass &rhs) const noexcept {
  return std::hash<fintamath::MathObjectClass::Name>{}(rhs.getName());
}
