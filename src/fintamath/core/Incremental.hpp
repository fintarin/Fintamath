#pragma once

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  class Incremental;
  using IncrementalPtr = std::unique_ptr<Incremental>;

  class Incremental : virtual public MathObject {
  public:
    ~Incremental() override = default;

    friend Incremental &operator++(Incremental &rhs);

    friend Incremental &operator--(Incremental &rhs);

    friend IncrementalPtr operator++(Incremental &lhs, int);

    friend IncrementalPtr operator--(Incremental &lhs, int);

  protected:
    virtual Incremental &increaseAbstract() = 0;

    virtual Incremental &decreaseAbstract() = 0;
  };

  inline Incremental &operator++(Incremental &rhs) {
    return rhs.increaseAbstract();
  }

  inline Incremental &operator--(Incremental &rhs) {
    return rhs.decreaseAbstract();
  }

  inline IncrementalPtr operator++(Incremental &lhs, int) {
    IncrementalPtr tmp(dynamic_cast<Incremental *>(lhs.clone().release()));
    lhs.increaseAbstract();
    return tmp;
  }

  inline IncrementalPtr operator--(Incremental &lhs, int) {
    IncrementalPtr tmp(dynamic_cast<Incremental *>(lhs.clone().release()));
    lhs.decreaseAbstract();
    return tmp;
  }

  template <typename Derived>
  class IncrementalImpl : virtual public MathObjectImpl<Derived>, virtual public Incremental {
  public:
    ~IncrementalImpl() override = default;

    Derived &operator++() {
      return increase();
    }

    Derived &operator--() {
      return decrease();
    }

    Derived operator++(int) {
      auto tmp = Derived(to<Derived>());
      increase();
      return tmp;
    }

    Derived operator--(int) {
      auto tmp = Derived(to<Derived>());
      decrease();
      return tmp;
    }

  protected:
    virtual Derived &increase() = 0;

    virtual Derived &decrease() = 0;

    Incremental &increaseAbstract() final {
      increase();
      return *this;
    }

    Incremental &decreaseAbstract() final {
      decrease();
      return *this;
    }
  };
}
