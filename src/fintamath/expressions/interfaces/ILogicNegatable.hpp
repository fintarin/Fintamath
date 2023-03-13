#pragma once

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

class ILogicNegatable : virtual public IMathObject {
public:
  virtual void logicNegate() = 0;
};

}
