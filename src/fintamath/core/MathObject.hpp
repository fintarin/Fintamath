#pragma once

#include "fintamath/core/MathObjectBase.hpp"

namespace fintamath {
  template <typename ObjectType>
  class MathObject : public MathObjectBase {
  public:
    ~MathObject() override = default;

    virtual bool equals(const ObjectType &rhs) const = 0;

    bool equals(const MathObjectBase &rhs) const override {
      if (!rhs.is<ObjectType>()) {
        return false;
      }
      return equals(rhs.to<ObjectType>());
    }
  };
}
