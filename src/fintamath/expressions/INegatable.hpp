#pragma once

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

class INegatable : virtual public IMathObject {
public:
  virtual void negate() = 0;
};

template <typename Derived>
class INegatableCRTP : virtual public INegatable, IMathObjectCRTP<Derived> {};
}