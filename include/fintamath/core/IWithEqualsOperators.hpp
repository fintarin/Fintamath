#pragma once

#include "fintamath/core/CoreConcepts.hpp"

namespace fintamath {

template <typename Derived>
class IWithEqualsOperators {
public:
  virtual ~IWithEqualsOperators() = default;

  friend bool operator==(const Derived &lhs, const Derived &rhs) {
    if (&lhs == &rhs) {
      return true;
    }

    const auto &lhsParent = static_cast<const IWithEqualsOperators<Derived> &>(lhs);
    return lhsParent.equals(rhs);
  }

protected:
  virtual bool equals(const Derived &rhs) const = 0;
};

template <typename Lhs, detail::ConvertibleToAndNotSameAs<Lhs> Rhs>
  requires(std::is_base_of_v<IWithEqualsOperators<Lhs>, Lhs>)
bool operator==(const Lhs &lhs, const Rhs &rhs) {
  return lhs == Lhs(rhs);
}

}
