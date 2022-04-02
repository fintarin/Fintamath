#pragma once

#include "fintamath/core/Comparable.hpp"
#include "fintamath/core/Incremental.hpp"
#include "fintamath/core/Multipliable.hpp"
#include "fintamath/core/Summable.hpp"

namespace fintamath {
  template <typename ObjectType>
  class Number : public Comparable<ObjectType>,
                 public Summable<ObjectType>,
                 public Multipliable<ObjectType>,
                 public Incremental<ObjectType> {
  public:
    ~Number() override = default;
  };
}
