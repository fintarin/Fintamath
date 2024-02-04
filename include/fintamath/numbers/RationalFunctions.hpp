#pragma once

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

Integer floor(const Rational &rhs);

Integer ceil(const Rational &rhs);

Rational abs(const Rational &rhs);

}
