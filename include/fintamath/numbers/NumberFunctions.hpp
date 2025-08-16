#pragma once

#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

std::unique_ptr<INumber> operator+(const INumber &lhs, const INumber &rhs);

}
