#pragma once

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

std::unique_ptr<INumber> abs(const INumber &rhs);

std::unique_ptr<INumber> sqrt(const INumber &rhs);

std::unique_ptr<INumber> pow(const INumber &lhs, const INumber &rhs);

}
