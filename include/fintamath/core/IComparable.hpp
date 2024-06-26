#pragma once

#include <compare>
#include <concepts>
#include <memory>
#include <string>
#include <utility>

#include <fmt/core.h>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/Parser.hpp"

namespace fintamath {

class IComparable : public IArithmetic {
  FINTAMATH_PARENT_CLASS_BODY(IComparable, IArithmetic)

public:
  friend std::strong_ordering operator<=>(const IComparable &lhs, const IComparable &rhs) {
    return lhs.compareAbstract(rhs);
  }

protected:
  virtual std::strong_ordering compareAbstract(const IComparable &rhs) const = 0;
};

template <typename Derived>
class IComparableCRTP : public IComparable {
#define I_COMPARABLE_CRTP IComparableCRTP<Derived>
#include "fintamath/core/IComparableCRTP.hpp"
#undef I_COMPARABLE_CRTP
};

template <std::derived_from<IComparable> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
std::strong_ordering operator<=>(const Lhs &lhs, const Rhs &rhs) {
  return lhs <=> Lhs(rhs);
}

}
