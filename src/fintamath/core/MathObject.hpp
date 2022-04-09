#pragma once

#include "fintamath/core/MathObjectBase.hpp"

namespace fintamath {
  template <typename Derived>
  class MathObject : public MathObjectBase {
  public:
    ~MathObject() override = default;

    virtual bool equals(const Derived &rhs) const = 0;

    bool equals(const MathObjectBase &rhs) const final {
      if (!rhs.is<Derived>()) {
        return false;
      }
      return equals(rhs.to<Derived>());
    }

    std::unique_ptr<MathObjectBase> clone() const final {
      return std::make_unique<Derived>(to<Derived>());
    }
  };
}
