#pragma once

#include <string_view>

#include "fintamath/core/FintamathExport.hpp"

namespace fintamath {

namespace detail {

class MathObjectClassData final {
public:
  using Name = std::string_view;

  using Ptr = const MathObjectClassData *;

public:
  constexpr MathObjectClassData(Name inName, Ptr inParent = nullptr) noexcept
      : name(inName),
        parent(inParent) {
  }

  constexpr MathObjectClassData(const MathObjectClassData &) noexcept = delete;

  constexpr MathObjectClassData(MathObjectClassData &&) noexcept = delete;

  constexpr MathObjectClassData &operator=(const MathObjectClassData &) noexcept = delete;

  constexpr MathObjectClassData &operator=(MathObjectClassData &&) noexcept = delete;

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
