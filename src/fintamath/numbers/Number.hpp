#pragma once

#include "fintamath/core/Comparable.hpp"
#include "fintamath/core/Incremental.hpp"
#include "fintamath/core/Multipliable.hpp"
#include "fintamath/core/Summable.hpp"

namespace fintamath {
  template <typename Derived>
  class Number : public Comparable<Derived>,
                 public Summable<Derived>,
                 public Multipliable<Derived>,
                 public Incremental<Derived> {
  public:
    ~Number() override = default;
  };
}
