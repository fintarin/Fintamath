#pragma once

#include <compare>
#include <cstddef>
#include <optional>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include "fintamath/config/Config.hpp"

namespace fintamath {

namespace detail {

class MathObjectClassImpl final {
public:
  using Name = std::string_view;

  using Ptr = const MathObjectClassImpl *;

public:
  constexpr MathObjectClassImpl(const Name inName, const Ptr inParent = nullptr) noexcept
      : name(inName),
        parent(inParent) {
  }

  constexpr MathObjectClassImpl(const MathObjectClassImpl &) noexcept = delete;

  constexpr MathObjectClassImpl(MathObjectClassImpl &&) noexcept = delete;

  constexpr MathObjectClassImpl &operator=(const MathObjectClassImpl &) noexcept = delete;

  constexpr MathObjectClassImpl &operator=(MathObjectClassImpl &&) noexcept = delete;

  constexpr Name getName() const noexcept {
    return name;
  }

  constexpr Ptr getParent() const noexcept {
    return parent;
  }

private:
  Name name;

  Ptr parent;

  [[maybe_unused]] inline static const Config config;
};

}

using MathObjectClass = detail::MathObjectClassImpl::Ptr;

}
