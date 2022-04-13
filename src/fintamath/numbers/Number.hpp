#pragma once

#include "fintamath/core/Comparable.hpp"
#include "fintamath/core/Incremental.hpp"
#include "fintamath/core/Multipliable.hpp"
#include "fintamath/core/Summable.hpp"

namespace fintamath {
  class Number : public virtual Comparable,
                 public virtual Summable,
                 public virtual Multipliable,
                 public virtual Incremental {
  public:
    ~Number() override = default;
  };

  template <typename Derived>
  class NumberImpl : public Number,
                     public ComparableImpl<Derived>,
                     public SummableImpl<Derived>,
                     public MultipliableImpl<Derived>,
                     public IncrementalImpl<Derived> {
  public:
    ~NumberImpl() override = default;
  };
}
