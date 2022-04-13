#pragma once

#include "fintamath/core/Comparable.hpp"
#include "fintamath/core/Incremental.hpp"
#include "fintamath/core/Multipliable.hpp"
#include "fintamath/core/Summable.hpp"

namespace fintamath {
  template <typename Derived>
  class Number : virtual public ComparableImpl<Derived>,
                 virtual public SummableImpl<Derived>,
                 virtual public MultipliableImpl<Derived>,
                 virtual public IncrementalImpl<Derived> {
  public:
    ~Number() override = default;
  };
}
