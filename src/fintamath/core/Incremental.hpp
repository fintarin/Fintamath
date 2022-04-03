#pragma once

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  template <typename ObjectType>
  class Incremental : virtual public MathObject<ObjectType> {
  public:
    ~Incremental() override = default;

    virtual ObjectType &inc() = 0;

    virtual ObjectType &dec() = 0;

    ObjectType &operator++() {
      return inc();
    }

    ObjectType &operator--() {
      return dec();
    }

    ObjectType operator++(int) {
      auto prev = ObjectType(this->template to<ObjectType>());
      inc();
      return prev;
    }

    ObjectType operator--(int) {
      auto prev = ObjectType(this->template to<ObjectType>());
      dec();
      return prev;
    }
  };
}
