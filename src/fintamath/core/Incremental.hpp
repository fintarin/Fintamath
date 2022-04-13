#pragma once

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  template <typename Derived>
  class Incremental : virtual public MathObjectImpl<Derived> {
  public:
    ~Incremental() override = default;

    Derived &operator++() {
      return increase();
    }

    Derived &operator--() {
      return decrease();
    }

    Derived operator++(int) {
      auto prev = Derived(this->template to<Derived>());
      increase();
      return prev;
    }

    Derived operator--(int) {
      auto prev = Derived(this->template to<Derived>());
      decrease();
      return prev;
    }

  protected:
    virtual Derived &increase() = 0;

    virtual Derived &decrease() = 0;
  };
}
