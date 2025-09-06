#pragma once

#include <array>
#include <cassert>
#include <string_view>

namespace fintamath {

namespace detail {

class MathObjectClassData final {
  static constexpr size_t parentsMaxSize = 5;

public:
  using Name = std::string_view;

  using Ptr = const MathObjectClassData *;

  using Parents = std::array<Ptr, parentsMaxSize>;

public:
  constexpr MathObjectClassData(Name inName, std::nullptr_t inParent) noexcept
      : name(inName),
        parent(inParent),
        parentsSize(0) {}

  constexpr MathObjectClassData(Name inName, Ptr inParent) noexcept
      : name(inName),
        parent(inParent), 
        parentsSize(parent->parentsSize) {

    assert(parentsSize < parentsMaxSize);

    for (size_t i = 0; i < parentsSize; i++) {
      parents[i] = parent->parents[i];
    }

    parents[parentsSize] = parent;
    parentsSize++;
  }

  MathObjectClassData(const MathObjectClassData &) noexcept = delete;

  MathObjectClassData(MathObjectClassData &&) noexcept = delete;

  MathObjectClassData &operator=(const MathObjectClassData &) noexcept = delete;

  MathObjectClassData &operator=(MathObjectClassData &&) noexcept = delete;

  constexpr Name getName() const noexcept {
    return name;
  }

  constexpr Ptr getParent() const noexcept {
    return parent;
  }

  constexpr bool is(const Ptr to) const noexcept {
    assert(to);
    return this == to || (parentsSize > to->parentsSize && parents[to->parentsSize] == to);
  }

private:
  static constexpr Parents getEmptyParents() {
    Parents emptyParents;
    emptyParents.fill(nullptr);
    return emptyParents;
  }

private:
  Parents parents = getEmptyParents();

  Name name;

  Ptr parent;

  size_t parentsSize;
};

}

using MathObjectClass = detail::MathObjectClassData::Ptr;

}
