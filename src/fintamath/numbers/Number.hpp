#pragma once

#include "fintamath/core/Comparable.hpp"
#include "fintamath/core/Incremental.hpp"
#include "fintamath/core/Multipliable.hpp"
#include "fintamath/core/Summable.hpp"

namespace fintamath {
  class Number;
  using NumberPtr = std::unique_ptr<Number>;

  class Number : virtual public Comparable,
                 virtual public Summable,
                 virtual public Multipliable,
                 virtual public Incremental {
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
