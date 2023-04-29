#pragma once

#include <functional>
#include <string>
#include <typeinfo>
#include <vector>

namespace fintamath {

class IMathObject;

using ArgumentRef = std::reference_wrapper<const IMathObject>;
using ArgumentPtr = std::shared_ptr<const IMathObject>;

using ArgumentsRefVector = std::vector<ArgumentRef>;
using ArgumentsPtrVector = std::vector<ArgumentPtr>;
using ArgumentsTypesVector = std::vector<std::reference_wrapper<const std::type_info>>;

}
