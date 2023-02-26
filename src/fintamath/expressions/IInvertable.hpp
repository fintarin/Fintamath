#pragma once

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

class IInvertable : virtual public IMathObject {
public:
  virtual void invert() = 0;
};
}