#pragma once

#include <compare>
#include <cstddef>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include <boost/container_hash/hash.hpp>

#include "fintamath/config/Config.hpp"

namespace fintamath {

class MathObjectClass;

size_t hash_value(MathObjectClass rhs) noexcept;

}

template <>
struct std::hash<fintamath::MathObjectClass> {
  size_t operator()(const fintamath::MathObjectClass &rhs) const noexcept {
    return boost::hash<fintamath::MathObjectClass>{}(rhs);
  }
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
  constexpr MathObjectClass(const Name inName) : name(inName) {
  }

  constexpr Name getName() const {
    return name;
  }

  constexpr bool operator==(const MathObjectClass rhs) const {
    return name == rhs.name;
  }

  std::strong_ordering operator<=>(MathObjectClass rhs) const;

  std::optional<MathObjectClass> getParent() const;

  const Children &getChildren(bool recursive = false) const;

  template <typename Parent, std::derived_from<Parent> Child>
  static void bindTypes();

private:
  Id getId() const;

  static ClassToIdMap &getClassToIdMap();

  static ChildToParentMap &getChildToParentMap();

  static ParentToChildrenMap &getParentToChildrenMap();

  static ParentToChildrenMap &getParentToRecursiveChildrenMap();

private:
  Name name;

  inline static Id maxId = 0;

  [[maybe_unused]] inline static const detail::Config config;
};

template <typename Parent, std::derived_from<Parent> Child>
void MathObjectClass::bindTypes() {
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

inline size_t hash_value(const MathObjectClass rhs) noexcept {
  return boost::hash<MathObjectClass::Name>{}(rhs.getName());
}

}
