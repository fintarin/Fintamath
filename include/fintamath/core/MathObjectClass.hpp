#pragma once

#include <string_view>

namespace fintamath {

namespace detail {

class MathObjectClassData final {
public:
  using Name = std::string_view;

  using Ptr = const MathObjectClassData *;

public:
  consteval MathObjectClassData(Name inName, Ptr inParent = nullptr) noexcept
      : name(inName),
        parent(inParent) {
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

private:
  Name name;

  Ptr parent;
};

}

using MathObjectClass = detail::MathObjectClassData::Ptr;

}
