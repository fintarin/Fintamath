#pragma once

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

using ArgumentsVector = std::vector<std::reference_wrapper<const class IMathObject>>;
using ArgumentsPtrVector = std::vector<std::shared_ptr<IMathObject>>;
using ArgumentsTypesVector = std::vector<std::reference_wrapper<const std::type_info>>;

}
