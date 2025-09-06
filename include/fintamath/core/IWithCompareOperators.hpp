#pragma once

#include <compare>

#include "fintamath/core/CoreUtils.hpp"

namespace fintamath {

template <typename Derived>
class IWithCompareOperators {

public:
  virtual ~IWithCompareOperators() = default;

  friend std::strong_ordering operator<=>(const Derived &lhs, const Derived &rhs) {
    const auto &lhsParent = static_cast<const IWithCompareOperators<Derived> &>(lhs);
    return lhsParent.compare(rhs);
  }

protected:
  virtual std::strong_ordering compare(const Derived &rhs) const = 0;
};

template <typename Lhs, detail::ConvertibleToAndNotSameAs<Lhs> Rhs>
  requires(std::is_base_of_v<IWithCompareOperators<Lhs>, Lhs>)
std::strong_ordering operator<=>(const Lhs &lhs, const Rhs &rhs) {
  return lhs <=> Lhs(rhs);
}

}
