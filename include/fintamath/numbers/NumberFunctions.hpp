#pragma once

#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

NumberPtr abs(const INumber &rhs);

NumberPtr pow(const INumber &lhs, const INumber &rhs);

}
