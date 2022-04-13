#pragma once

#include "fintamath/core/Arithmetic.hpp"
#include "fintamath/core/Comparable.hpp"
#include "fintamath/core/Incremental.hpp"

namespace fintamath {
  class Number;
  using NumberPtr = std::unique_ptr<Number>;

  class Number : virtual public Comparable, virtual public Arithmetic, virtual public Incremental {
  public:
    ~Number() override = default;
  };

  template <typename Derived>
  class NumberImpl : public Number,
                     public ComparableImpl<Derived>,
                     public ArithmeticImpl<Derived>,
                     public IncrementalImpl<Derived> {
  public:
    ~NumberImpl() override = default;
  };
}
