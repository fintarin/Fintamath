#pragma once

#include <memory>
#include <string>
#include <vector>

#include "fintamath/core/MathObjectTypes.hpp"

namespace fintamath {

class IMathObject;

using ArgumentRef = std::reference_wrapper<const IMathObject>;
using ArgumentPtr = std::shared_ptr<const IMathObject>;

using ArgumentRefVector = std::vector<ArgumentRef>;
using ArgumentPtrVector = std::vector<ArgumentPtr>;

using ArgumentTypeVector = std::vector<MathObjectType>;

}
