#pragma once

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  template <typename Derived>
  class Incremental : virtual public MathObject<Derived> {
  public:
    ~Incremental() override = default;

    virtual Derived &inc() = 0;

    virtual Derived &dec() = 0;

    Derived &operator++() {
      return inc();
    }

    Derived &operator--() {
      return dec();
    }

    Derived operator++(int) {
      auto prev = Derived(this->template to<Derived>());
      inc();
      return prev;
    }

    Derived operator--(int) {
      auto prev = Derived(this->template to<Derived>());
      dec();
      return prev;
    }
  };
}
