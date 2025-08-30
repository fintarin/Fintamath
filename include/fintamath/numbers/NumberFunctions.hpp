#pragma once

#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

Shared<INumber> operator+(const Shared<INumber> &lhs, const Shared<INumber> &rhs);

}
